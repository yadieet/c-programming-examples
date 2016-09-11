/*
 * Copyright (C) 2016 Yadieet SA <yadieet@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


 /**
 * Number-to-words or number-to-text converter utility for Bahasa Indonesia or Indonesian Rupiah (IDR) currency.
 * -- Using GMP Library (GNU Multiple Precision Arithmetic Library) <https://gmplib.org/>
 *
 * Based on its java version :
 * => https://github.com/yadieet/corejava-tes/blob/master/yadieet/Terbilang.java
 *
 * Created by Yadieet SA <yadieet@gmail.com>.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "gmp.h"

#define ws 8UL

_Static_assert( sizeof(long)      == ws , "Invalid `long` type size");
_Static_assert( sizeof(mp_limb_t) == ws , "Unsupported platform/system");

static const char * const value_level_string[] =
{
    NULL,
    "puluh ",
    "ratus ",
    "ribu, ",
    "juta, ",
    "milyar, ",
    "triliun, ",
    "quadriliun, ",
    "quintiliun, ",
    "sektiliun, ",
    "septiliun, ",
    "oktiliun, ",
    "noniliun, ",
    "desiliun, "
};

static const char * const under_twenty_string[] =
{
    NULL,
    "satu ",
    "dua ",
    "tiga ",
    "empat ",
    "lima ",
    "enam ",
    "tujuh ",
    "delapan ",
    "sembilan ",
    "sepuluh ",
    "sebelas ",
    "dua belas ",
    "tiga belas ",
    "empat belas ",
    "lima belas ",
    "enam belas ",
    "tujuh belas ",
    "delapan belas ",
    "sembilan belas "
};

static mpz_t MAX_VALUE;
static mpz_t value_level[14];


static void letsGo (mpz_t val, FILE * stream)
{
    if ( mpz_cmp(val, value_level[0]) == -1 )
    {
        fprintf( stream, "%s", under_twenty_string[mpz_get_ui( val )] );
        return;
    }

    /////////////////////////////////////////////////

    mpz_t temp1;
    {
    unsigned int i = 14u;
    while( mpz_cmp(val, value_level[--i]) < 0 );

    mpz_t temp0;
    mpz_init( temp0 );
    mpz_init( temp1 );
    mpz_tdiv_qr( temp0, temp1, val, value_level[i] );

    /////////////////////////////////////////////////

    if ( mpz_cmp(temp0, value_level[0]) == -1 )
    {
        unsigned long x = mpz_get_ui( temp0 );
        if ( x == 1UL && (i == 2u || i == 3u) ) //No comment!
            fprintf( stream, "se" );
        else
            fprintf( stream, "%s", under_twenty_string[x] );
    }
    else
        letsGo( temp0, stream );

    mpz_clear( temp0 );

    /////////////////////////////////////////////////

    fprintf( stream, "%s", value_level_string[i] );
    }
    /////////////////////////////////////////////////

    if ( mpz_sgn(temp1) == 0 )
    {
        mpz_clear( temp1 );
        return;
    }

    letsGo( temp1, stream );
    mpz_clear( temp1 );
}

#define MPZ_IMPORT_SET(a,b,c) mpz_init( a ); mpz_import( a, 2, -1, ws, 0, 0, (const unsigned long[]) {b, c} )


int main (int argc, char *argv[])
{
    if ( argc < 2 )
    {
        puts(
"YSA Terbilang v2.0\n\
Number-To-Text / Number-To-Words  converter utility\n\
for Bahasa Indonesia or Indonesian Rupiah (IDR) currency.\n\
(https://github.com/yadieet/c-programming-examples)\n\n\
  Usage  : ysa-terbilang [number] <rupiah>\n\
  Example: $ ysa-terbilang 999999999999999999999999999999999999 rupiah\n\n\
Copyright © 2016 Yadieet SA.\n\
This program is licensed under GPLv3 license" );

        return 0;
    }

    _Bool rupiah = false;
    if ( argc > 2 && *(int *)argv[2] == 1768977778 && *(int *)(argv[2]+3) == 6840681 )
        rupiah = true;

    MPZ_IMPORT_SET( MAX_VALUE, 12919594847110692863UL, 54210108624275221UL );

    const char *strval = argv[1];
    mpz_t  val;
    if ( mpz_init_set_str( val, strval, 10 ) != 0 || mpz_sgn( val ) == -1 || mpz_cmp( val, MAX_VALUE ) > 0 )
    {
        mpz_clear( val );
        //mpz_clear( MAX_VALUE );
        puts( "Invalid argument. Input value must be an integer >= 0 and <= 999999999999999999999999999999999999" );
        return 1;
    }

    //ULM = 18446744073709551615
    mpz_init_set_ui ( value_level[0],  20UL );
    mpz_init_set_ui ( value_level[1],  10UL );
    mpz_init_set_ui ( value_level[2],  100UL );
    mpz_init_set_ui ( value_level[3],  1000UL );
    mpz_init_set_ui ( value_level[4],  1000000UL );
    mpz_init_set_ui ( value_level[5],  1000000000UL );
    mpz_init_set_ui ( value_level[6],  1000000000000UL );
    mpz_init_set_ui ( value_level[7],  1000000000000000UL );
    mpz_init_set_ui ( value_level[8],  1000000000000000000UL );
    MPZ_IMPORT_SET  ( value_level[9],  3875820019684212736UL, 54UL );
    MPZ_IMPORT_SET  ( value_level[10], 2003764205206896640UL, 54210UL );
    MPZ_IMPORT_SET  ( value_level[11], 11515845246265065472UL, 54210108UL );
    MPZ_IMPORT_SET  ( value_level[12], 5076944270305263616UL, 54210108624UL );
    MPZ_IMPORT_SET  ( value_level[13], 4089650035136921600UL, 54210108624275UL );

    if ( mpz_sgn(val) != 0 )
    {
        char output[582];
        FILE * stream = fmemopen (output, sizeof output, "w");
        letsGo( val, stream );
        fclose( stream );

        output[0] = toupper(output[0]);

        size_t len = strlen( output );
        if ( output[len-2] == ',' )
            output[--len-1] = ' ';

        if ( rupiah )
            *(long *)&output[len] = 13062616518784370L;
        else
            *(int *)&output[--len] = 1680146478;

        puts( output );
    }
    else if ( rupiah )
        puts( "Nol rupiah." );
    else
        puts( "Nol." );

    mpz_clear( val );

    //mpz_clear( MAX_VALUE );
    //for( int i=0; i<14; i++ )
    //    mpz_clear( value_level[i] );

    return 0;
}


/*

Compiling, ex :
────♦ $ gcc -Wall -Wextra -std=c11 -pedantic -o "ysa-terbilang" "ysa-terbilang.c" -lgmp


Example output :
────♦ $ ./ysa-terbilang 999999999999999999999999999999999999 rupiah

Sembilan ratus sembilan puluh sembilan desiliun,
sembilan ratus sembilan puluh sembilan noniliun,
sembilan ratus sembilan puluh sembilan oktiliun,
sembilan ratus sembilan puluh sembilan septiliun,
sembilan ratus sembilan puluh sembilan sektiliun,
sembilan ratus sembilan puluh sembilan quintiliun,
sembilan ratus sembilan puluh sembilan quadriliun,
sembilan ratus sembilan puluh sembilan triliun,
sembilan ratus sembilan puluh sembilan milyar,
sembilan ratus sembilan puluh sembilan juta,
sembilan ratus sembilan puluh sembilan ribu,
sembilan ratus sembilan puluh sembilan rupiah.


For checking/comparing result :
=> http://www.calculatorsoup.com/calculators/conversions/numberstowords.php

*/
