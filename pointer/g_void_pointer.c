#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/** VOID POINTER IN ACTION **/

enum GV_PTR_TYPE
{
    INT,
    CHAR,
    STRING,
    BYTE,
    INT_ARR,
    STRING_ARR
};


void printout (void * ptr, enum GV_PTR_TYPE type, ...)
{
    switch( type )
    {
        case INT:
            printf( "INT     : %d\n", *(int *) ptr );
            break;

        case CHAR:
            printf( "CHAR    : %c\n", *(char *) ptr );
            break;

        case STRING:
            printf( "STR     : %s\n", (char *) ptr );
            break;

        case BYTE:
            printf( "BYTE    : %#02x\n", *(unsigned char *) ptr );
            break;

        case INT_ARR:
            {
                int *arr = ptr;
                va_list ap; va_start(ap,type);
                int n = va_arg(ap,int);
                va_end(ap);

                printf( "INT ARR : {" );
                for( int i=0; i<n; i++ )
                    printf( " %d", arr[i] );
                puts(" }");
            }
            break;

        case STRING_ARR:
            {
                char **arr = ptr;
                va_list ap; va_start(ap,type);
                int n = va_arg(ap,int);
                va_end(ap);

                puts( "STR ARR : " );
                if (n > 0)
                {
                    for ( int i=0; i<n; i++ )
                        printf( "          %s\n", arr[i] );
                }
                else
                {
                    while ( *arr )
                        printf( "          %s\n", *(arr++) );
                }
            }
            break;

        default:
            puts( "Type of GV_PTR is unknown." );
    };
}


int main (void)
{
    void * GV_PTR = NULL;

    {
        int  a = 10;
        int *z = &a;

        GV_PTR = z;
        printout( GV_PTR, INT );
        GV_PTR = NULL;

    }{
        char *z = "Hello World";

        GV_PTR  = z;
        printout( GV_PTR, STRING );
        GV_PTR  = NULL;

    }{
        char  a = 'T';
        char *z = &a;

        GV_PTR  = z;
        printout( GV_PTR, CHAR );
        GV_PTR  = NULL;

    }{
        unsigned char  a = 255;
        unsigned char *z = &a;

        GV_PTR = z;
        printout( GV_PTR, BYTE );
        GV_PTR = NULL;

    }{
        int a[] = { 0,1,2,3,4,5 };
        int *z = a;

        GV_PTR = z; //GV_PTR = a;
        printout( GV_PTR, INT_ARR, 6 ); //sizeof(a) / sizeof(int) );

    }{
        char *a[] = { "This was a triumph..",
                      "I'm making a note here.. [HUGE SUCCESS]",
                      "It's hard to overstate my satisfaction." };
        char **z = a;

        GV_PTR = z; //GV_PTR = a;
        printout( GV_PTR, STRING_ARR, 3 );

    }{
        char *a[] = { "Now these points of data make a beautiful line.",
                      "And we're out of beta, we're releasing on time.",
                      "So I'm glad I got burned..",
                      "Think of all the things we learned,",
                      "For the people who are still alive.",
                      NULL };
        char **z = a;

        GV_PTR = z; //GV_PTR = a;
        printout( GV_PTR, STRING_ARR, 0 );

    }

    return 0;
}


/*
 * KESIMPULAN : Pointer is POINTER.
 */
