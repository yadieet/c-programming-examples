#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

_Static_assert( (sizeof(time_t) == 8 ) , "Invalid `time_t` type size");

#define get_epoch_seconds(a) time_t a = time(NULL)
#define init_utc_time(a,b) struct tm b; gmtime_r(a, &b)
#define init_local_time(a,b) struct tm b; localtime_r(a, &b)
#define utc_time_default_format "%04d/%02d/%02d %02d:%02d:%02d UTC"
#define utc_time_iso_format "%04d-%02d-%02dT%02d:%02d:%02d+00:00"
#define local_time_indonesian_format "%A, %d %B %Y - %H:%M:%S %Z" // (UTC%z)"


static void get_utc_time_string (time_t *t, char *result)
{
    init_utc_time( t, tm );
    snprintf( result, 24, utc_time_default_format,
              1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
              tm.tm_hour, tm.tm_min, tm.tm_sec );
}

static void get_utc_time_iso_string (time_t *t, char *result)
{
    init_utc_time( t, tm );
    snprintf( result, 26, utc_time_iso_format,
              1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
              tm.tm_hour, tm.tm_min, tm.tm_sec );
}

static void get_indonesian_local_time_string (time_t *t, char *result, size_t max)
{
    //setlocale( LC_ALL, "" );
    setlocale( LC_TIME, "id_ID" );

    init_local_time( t, tm );
    strftime(result, max, local_time_indonesian_format, &tm);
}


int main (void)
{
    #define len 64
    char string_buf[len];

    get_epoch_seconds(t);

    printf( "%ld seconds since the Epoch\n", t );

    get_utc_time_string( &t, string_buf );
    puts( string_buf );
    get_utc_time_iso_string( &t, string_buf );
    puts( string_buf );
    get_indonesian_local_time_string( &t, string_buf, len );
    puts( string_buf );

    return 0;
}

#undef get_epoch_seconds
#undef init_utc_time
#undef init_local_time
#undef utc_time_default_format
#undef utc_time_iso_format
#undef local_time_indonesian_format

/*
 *    C11: int timespec_get(struct timespec *ts, int base);
 *    *) GCC & Clang currently not yet supported
 *
 *    struct tm *gmtime(const time_t *timep);
 *    struct tm *gmtime_r(const time_t *timep, struct tm *result);
 *
 *    C11:
 *    struct tm *gmtime_s(const time_t *    restrict timer, struct tm *    restrict result);
 *    *) GCC & Clang currently not yet supported
 *
 *    struct tm *localtime(const time_t *timep);
 *    struct tm *localtime_r(const time_t *timep, struct tm *result);
 *
 *    C11:
 *    struct tm *localtime_s(const time_t * restrict timer, struct tm * restrict result);
 *    *) GCC & Clang currently not yet supported
 *
 */
