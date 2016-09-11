#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[])
{

    if( argc > 1 )
    {
        puts( "Main argv parameter arguments :" );

        for( int i=1; i<argc; i++ )
            printf( "- {%s}\n", argv[i] );

        puts("");
    }

    puts( "Hello Friends !!" );

    return 0;
}
