#include <stdio.h>

enum Hari {Senin=3, Selasa, Rabu, Kamis, Jumat, Sabtu, Minggu};
const char *const nama_hari[] =
    {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

#define HARI_MIN Senin
#define HARI_MAX Minggu


int main (void)
{
    for( int i=HARI_MIN; i<=HARI_MAX; i++ )
        printf( "%s(%d) ", nama_hari[i-HARI_MIN], i );
    puts("\n");

    enum Hari H1 = Minggu;
    enum Hari H2 = Rabu;

    printf( "Hari H1 : %d (%s)\n", H1, nama_hari[H1-HARI_MIN] );
    printf( "Hari H2 : %d (%s)\n", H2, nama_hari[H2-HARI_MIN] );

    return 0;
}
