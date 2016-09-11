#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

_Bool is_ascii_pcs (const char *s)
{
    //if (str == NULL)
    //    return false;

    while( *s )
    {
        if( *s < 32 || *(s++) > 126 )
            return false;
    }

    return true;
}

int main (void)
{
    const char *str = "Hello\x20World";

    printf( "{%s} is %san 'ASCII printable characters' string.",
             str,
             is_ascii_pcs(str) ? "" : "not " );

    return 0;
}
