/* Contributors :
 * - xyzzy @ kaskus.co.id
 */

#include <stdio.h>

typedef enum
{
    Senin,
    Selasa,
    Rabu,
    Kamis,
    Jumat,
    Sabtu,
    Minggu

} Hari;

static const char *hari[8] =
{
    "INVALID",
    "Senin",
    "Selasa",
    "Rabu",
    "Kamis",
    "Jumat",
    "Sabtu",
    "Minggu"
};

const char **p_hari = hari + 1;


static const char *nama_hari(Hari h)
{
    return (h < 0 || h > 6) ? p_hari[-1] : p_hari[h];
}


int main (void)
{
    printf( "%s\n", nama_hari(Senin) );
    printf( "%s\n", nama_hari(Minggu) );

    /* For invalid Hari values */
    printf( "%s\n", nama_hari(100) );
    printf( "%s\n", nama_hari(-1234340) );

    return 0;
}
