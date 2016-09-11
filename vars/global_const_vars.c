#include <stdio.h>
#include <stdlib.h>

/* Initialized global const variables */
int const A = 10;
int const* const B = &A;
int const* const* const C = &B;


int main (void)
{
    printf( "A : %d << %p \n", A, (void *) &A );
    printf( "B : %d << %p << %p \n", *B, (void *) B, (void *) &B );
    printf( "C : %d << %p << %p << %p \n", **C, (void *) *C, (void *) C, (void *) &C );
    puts( "////////////////////////////////////////////////////////////////" );


    /*
     * Compilers: GCC en CLANG.
     * Apakah A, B, dan C bisa diubah scr programmatically / dari dalam program ?
     * (Silahkan dicoba)
     */

    // Your codes here :
    // ...


    puts( "////////////////////////////////////////////////////////////////" );
    printf( "A : %d << %p \n", A, (void *) &A );
    printf( "B : %d << %p << %p \n", *B, (void *) B, (void *) &B );
    printf( "C : %d << %p << %p << %p \n", **C, (void *) *C, (void *) C, (void *) &C );

    return 0;
}

/*
Ex OUTPUT :
-----------

    A : 10 << 0x4006c8
    B : 10 << 0x4006c8 << 0x4006d0
    C : 10 << 0x4006c8 << 0x4006d0 << 0x4006d8
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    A : 10 << 0x4006c8
    B : 10 << 0x4006c8 << 0x4006d0
    C : 10 << 0x4006c8 << 0x4006d0 << 0x4006d8



READELF / OBJDUMP :
-------------------

    Symbol table :
      Address   Size   Type      Bind      Vis        Ndx   Name
      0x4006c8    4    OBJECT    GLOBAL    DEFAULT    15    A
      0x4006d0    8    OBJECT    GLOBAL    DEFAULT    15    B
      0x4006d8    8    OBJECT    GLOBAL    DEFAULT    15    C

    Hex dump of section '.rodata' :
      4006c0 01000200 00000000 0a000000 00000000  ................
      4006d0 c8064000 00000000 d0064000 00000000  ..@.......@.....
      4006e0 41203a20 2564203c 3c202570 200a0042  A : %d << %p ..B
      4006f0 203a2025 64203c3c 20257020 3c3c2025   : %d << %p << %
      400700 70200a00 43203a20 2564203c 3c202570  p ..C : %d << %p
      400710 203c3c20 2570203c 3c202570 200a0000   << %p << %p ...
      400720 2f2f2f2f 2f2f2f2f 2f2f2f2f 2f2f2f2f  ////////////////
      400730 2f2f2f2f 2f2f2f2f 2f2f2f2f 2f2f2f2f  ////////////////
      400740 2f2f2f2f 2f2f2f2f 2f2f2f2f 2f2f2f2f  ////////////////
      400750 2f2f2f2f 2f2f2f2f 2f2f2f2f 2f2f2f2f  ////////////////
      400760 00


    A    0x4006c8    4 BYTE    [0a000000]             0x0a
    B    0x4006d0    8 BYTE    [c8064000 00000000]    0x4006c8
    C    0x4006d8    8 BYTE    [d0064000 00000000]    0x4006d0
*/



/*
KESIMPULAN :

    Jika value dari suatu variable disimpan pada `.rodata` segment
    atau `.data.rel.ro` segment, maka value dari variable tsb
    tidak dapat diubah secara programmatically atau dari dalam program.

    Mencoba mengubah value dari suatu variable yang value-nya disimpan
    pada segment memori yang "Read-Only", dapat menyebabkan program crash,
    `segmentation fault`, dsb.
*/

