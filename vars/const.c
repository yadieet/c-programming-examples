#include <stdio.h>
#include <stdlib.h>


void func_0 (int const i)
{
    printf( "func_0  : %d\n", i );

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only parameter ‘i’ */
    //i = 0;

    //////////////////////////////////////////////////////////////
}

void func_1a (int const* i)
{
    printf( "func_1a : %d >> ", *i );

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘*i’ */
    //*i = 0;

    //////////////////////////////////////////////////////////////

                                {
                                    int const* bkup = i;
                                    int x = 20; int const* y = &x;
    i =                             y;
                                    printf( "%d\n", *i );
                                    i = bkup;
                                }

    //////////////////////////////////////////////////////////////
}

void func_1b (int * const i)
{
    printf( "func_1b : %d >> ", *i );

    //////////////////////////////////////////////////////////////

                                {
                                    int bkup = *i;
    *i =                            10;
                                    printf( "%d\n", *i );
                                    *i = bkup;
                                }

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only parameter ‘i’ */
    //i = NULL;

    //////////////////////////////////////////////////////////////
}

void func_1c (int const* const i)
{
    printf( "func_1c : %d\n", *i );

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘*i’ */
    //*i = 0;

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only parameter ‘i’ */
    //i = NULL;

    //////////////////////////////////////////////////////////////
}

void func_2a (int const* * i)
{
    printf( "func_2a : %d >> ", **i );

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘**i’ */
    //**i = 0;

    //////////////////////////////////////////////////////////////

                                {
                                    int const* bkup = *i;
                                    int x = 20; int const* y = &x;
    *i =                            y;
                                    printf( "%d >> ", **i );
                                    *i = bkup;
                                }

    //////////////////////////////////////////////////////////////

                                {
                                    int const* * bkup = i;
                                    int x = 30; int const* y = &x; int const* * z = &y;
    i =                             z;
                                    printf( "%d\n", **i );
                                    i = bkup;
                                }

    //////////////////////////////////////////////////////////////
}

void func_2b (int ** const i)
{
    printf( "func_2b : %d >> ", **i );

    //////////////////////////////////////////////////////////////

                                {
                                    int bkup = **i;
    **i =                           10;
                                    printf( "%d >> ", **i );
                                    **i = bkup;
                                }

    //////////////////////////////////////////////////////////////

                                {
                                    int * bkup = *i;
                                    int x = 20; int * y = &x;
    *i =                            y;
                                    printf( "%d\n", **i );
                                    *i = bkup;
                                }

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only parameter ‘i’ */
    //i = NULL;

    //////////////////////////////////////////////////////////////
}

void func_2c (int * const* i)
{
    printf( "func_2c : %d >> ", **i );

    //////////////////////////////////////////////////////////////

                                {
                                    int bkup = **i;
    **i =                           10;
                                    printf( "%d >> ", **i );
                                    **i = bkup;
                                }

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘*i’ */
    //*i = NULL;

    //////////////////////////////////////////////////////////////

                                {
                                    int * const* bkup = i;
                                    int x = 30; int * y = &x; int * const* z = &y;
    i =                             z;
                                    printf( "%d\n", **i );
                                    i = bkup;
                                }

    //////////////////////////////////////////////////////////////
}

void func_2d (int const* const* i)
{
    printf( "func_2d : %d >> ", **i );

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘**i’ */
    //**i = 0;

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘*i’ */
    //*i = NULL;

    //////////////////////////////////////////////////////////////

                                {
                                    int const* const* bkup = i;
                                    int x = 30; int const* y = &x; int const* const* z = &y;
    i =                             z;
                                    printf( "%d\n", **i );
                                    i = bkup;
                                }

    //////////////////////////////////////////////////////////////
}

void func_2e (int const* * const i)
{
    printf( "func_2e : %d >> ", **i );

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘**i’ */
    //**i = 0;

    //////////////////////////////////////////////////////////////

                                {
                                    int const* bkup = *i;
                                    int x = 20; int const* y = &x;
    *i =                            y;
                                    printf( "%d\n", **i );
                                    *i = bkup;
                                }

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only parameter ‘i’ */
    //i = NULL;

    //////////////////////////////////////////////////////////////
}

void func_2f (int * const* const i)
{
    printf( "func_2f : %d >> ", **i );

    //////////////////////////////////////////////////////////////

                                {
                                    int bkup = **i;
    **i =                           10;
                                    printf( "%d\n", **i );
                                    **i = bkup;
                                }

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘*i’ */
    //*i = NULL;

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only parameter ‘i’ */
    //i = NULL;

    //////////////////////////////////////////////////////////////
}

void func_2g (int const* const* const i)
{
    printf( "func_2g : %d\n", **i );

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘**i’ */
    //**i = 0;

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only location ‘*i’ */
    //*i = NULL;

    //////////////////////////////////////////////////////////////

    /* gcc compile error: assignment of read-only parameter ‘i’ */
    //i = NULL;

    //////////////////////////////////////////////////////////////
}





//You may ignore the main function, just focus on above functions.
int main (void)
{
    int a = 5;
    int * b = &a;
    int * * c = &b;


    func_0(   a );
    func_0(  *b );
    func_0( **c );
    puts("");

    func_1a( &a );
    func_1a(  b );
    func_1a( *c );
    puts("");

    func_1b( &a );
    func_1b(  b );
    func_1b( *c );
    puts("");

    func_1c( &a );
    func_1c(  b );
    func_1c( *c );
    puts("");

    func_2a( (int const* *) &b );
    func_2a( (int const* *)  c );
    puts("");

    func_2b( &b );
    func_2b(  c );
    puts("");

    func_2c( &b );
    func_2c(  c );
    puts("");

    func_2d( (int const* const*) &b );
    func_2d( (int const* const*)  c );
    puts("");

    func_2e( (int const* * const) &b );
    func_2e( (int const* * const)  c );
    puts("");

    func_2f( &b );
    func_2f(  c );
    puts("");

    func_2g( (int const* const* const) &b );
    func_2g( (int const* const* const)  c );
    puts("");

    return 0;
}


/*

int const i
   // i =

int const* i
   // *i =
       i =

int * const i
      *i =
   //  i =

int const* const i
   // *i =
   //  i =

int const* * i
   // **i =
       *i =
        i =

int ** const i
      **i =
       *i =
   //   i =

int * const* i
      **i =
   //  *i =
        i =

int const* const* i
   // **i =
   //  *i =
        i =

int const* * const i
   // **i =
       *i =
   //   i =

int * const* const i
      **i =
   //  *i =
   //   i =

int const* const* const i
   // **i =
   //  *i =
   //   i =

*/
