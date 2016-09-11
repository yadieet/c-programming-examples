#include <stdio.h>

enum HELLO
{
    QWER,
    FGHJ,
    ASDF,
    UIOP,
    XCVB,
};

enum HELLO get_foo_hello ()
{
    return ASDF;
}

int main (void)
{
    enum HELLO ahello = XCVB;
    printf( "ahello : %d\n", ahello );

    ahello = get_foo_hello();
    printf( "ahello : %d\n", ahello );

    puts( (ahello == ASDF) ? "TRUE" : "FALSE" );

    return 0;
}
