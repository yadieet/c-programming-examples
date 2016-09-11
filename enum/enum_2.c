#include <stdio.h>

enum Hari {Senin, Selasa, Rabu, Kamis, Jumat, Sabtu, Minggu};
const char *const nama_hari[] =
    {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};

int main (void)
{
    enum Hari H1 = Minggu;
    enum Hari H2 = Rabu;

    printf( "Hari H1 : %d (%s)\n", H1, nama_hari[H1] );
    printf( "Hari H2 : %d (%s)\n", H2, nama_hari[H2] );

    return 0;
}
