#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

_Static_assert( (sizeof(size_t) == 8  ) , "Invalid `size_t` type size");
_Static_assert( (sizeof(long)   == 8  ) , "Invalid `long` type size");

#define NOL 0UL
#define ONE 1UL
#define TEN 10UL

#define SIZE_T_MAX (~(size_t)0)
#define BSI 8UL

char *readline (size_t *len, _Bool *is_eof, _Bool (*func)(char *) )
{
    size_t cbs = BSI;

    char *buf = malloc( cbs );
    char c;

    size_t r, i = NOL;

    while ( 1 )
    {
        r = read( 0, &c, ONE );

        if ( r == SIZE_T_MAX ) // r == -1
        {
            free( buf );
            return NULL;
        }

        if ( r == NOL || c == '\n' )
        {
            if ( is_eof )
                *is_eof = (r == NOL);

            break;
        }

        if ( func && !func( &c ) )
        {
            free( buf );
            while( (r = read(0, &c, ONE)) == ONE && c != '\n' ); //Drain

            return NULL;
        }

        buf[i++] = c;

        if ( i == cbs )
        {
            cbs += BSI;
            buf = realloc ( buf, cbs );
        }
    }

    buf[i] = '\0';

    if ( len != NULL )
        *len = i;

    return buf;
}


#define IS_ASCIIP(c) (c > 31 && c < 127)

_Bool accept (char *c)
{
    return IS_ASCIIP( *c );
}


int main (void)
{
    size_t len;
    _Bool is_eof;

    char *str = readline( &len, &is_eof, accept );

    if (str != NULL)
    {
        if ( is_eof )
            puts( "" );
        printf( "[%s] => %lu chars\n", str, len );

        for( size_t i = NOL; i<len; i++ )
            printf( "- char #%-3lu: %c\n", i, str[i] );

        free(str);
    }
    else
        puts( "NULL" );

    return 0;
}

/*

@see also:
- fgets <= stdio.h
- getline <= posix - stdio.h
- readline <= GNU Readline - readline/readline.h

*/
