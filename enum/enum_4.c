#include <stdio.h>

enum Hari
{
    Senin  = 0,
    Selasa = 1,
    Rabu   = 2,
    Kamis  = 4,
    Jumat  = 8,
    Sabtu  = 16,
    Minggu = 32,
};

#define HARI_MAX Minggu

#define is_invalid_hari_value(x) (x > HARI_MAX || (x & (x - 1)))

void foo (enum Hari hari)
{
    if ( is_invalid_hari_value(hari) )
    {
        printf( "%d ", hari);
        return;
    }

    printf( "\n\n => hari : %d\n\n", hari);
}


int main (void)
{
    for( int i=-129; i<130; i++ )
        foo( i );

    return 0;
}
