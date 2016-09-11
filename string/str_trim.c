#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Static_assert( (sizeof(size_t) == 8  ) , "Invalid `size_t` type size");
_Static_assert( (sizeof(long)   == 8  ) , "Invalid `long` type size");

#define NOL 0UL
#define ONE 1UL
#define TEN 10UL
#define SPASI ' '

char *str_trim (const char *str, const size_t len, size_t *new_len)
{
    //if ( len == NOL ) //No need to trim
    //    return NULL;

    size_t a;
    size_t b = len;

    for( a=NOL; str[a] == SPASI; a++ );

    if ( a == b )
    {
        a = NOL;
        b = NOL;
    }
    else
    {
        for( --b; str[b] == SPASI; b-- );

        b -= a - ONE;
    }

    //if ( a == NOL && b == len ) //No need to trim
    //    return NULL;

    if ( new_len )
        *new_len = b;

    char *new_str = malloc( b + ONE );
    size_t i;

    str += a;
    for( i=NOL; i<b; i++ )
        new_str[i] = str[i];
    new_str[i] = '\0';

    return new_str;
}


int main (void)
{
    char *strs[] = {
        "",
        "    ",
        "  a",
        " a ",
        "a  ",
        "abc",
        "   ab c",
        "a bc   ",
        "    a  b c    ",
        "       a b   c        d   e     fgh    ",
        //...
        NULL
    };

    char *str;
    char *new_str;
    size_t i = NOL;

    while( (str = strs[i++]) )
    {
        new_str = str_trim( str, strlen(str), NULL );
        printf( "[%s]\n", new_str );
        free( new_str );
    };

    return 0;
}
