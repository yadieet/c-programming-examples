#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

_Static_assert( (sizeof(struct timespec) == 16 ) , "Invalid `struct timespec` type size");

#define get_time_instant(a) struct timespec a; clock_gettime(CLOCK_REALTIME, &a)
#define init_utc_time(a,b) struct tm b; gmtime_r(a, &b)
#define utc_time_with_nanos_default_format "%04d/%02d/%02d %02d:%02d:%02d.%09ld UTC"
#define utc_time_with_nanos_iso_format "%04d-%02d-%02dT%02d:%02d:%02d,%09ld+00:00"


static void get_utc_time_string (struct timespec *timespec, char *result)
{
    init_utc_time( &timespec->tv_sec, tm );
    snprintf( result, 34, utc_time_with_nanos_default_format,
              1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
              tm.tm_hour, tm.tm_min, tm.tm_sec, timespec->tv_nsec );
}

static void get_utc_time_iso_string (struct timespec *timespec, char *result)
{
    init_utc_time( &timespec->tv_sec, tm );
    snprintf( result, 36, utc_time_with_nanos_iso_format,
              1900+tm.tm_year, tm.tm_mon+1, tm.tm_mday,
              tm.tm_hour, tm.tm_min, tm.tm_sec, timespec->tv_nsec );
}


int main (void)
{
    #define len 64
    char string_buf[len];

    get_time_instant(ts);

    printf( "%ld.%09ld seconds since the Epoch\n", ts.tv_sec, ts.tv_nsec );

    get_utc_time_string( &ts, string_buf );
    puts( string_buf );
    get_utc_time_iso_string( &ts, string_buf );
    puts( string_buf );

    return 0;
}

#undef get_time_instant
#undef init_utc_time
#undef utc_time_with_nanos_default_format
#undef utc_time_with_nanos_iso_format

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
