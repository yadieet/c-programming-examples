#include <stdio.h>

//const int na = 2;
//const int nb = 4;

#define na 3
#define nb 5

int main(void)
{

    int arr[na][nb];
    {
        int a, b;
        int v = 1;

        for( a=0; a<na; a++ )
        {
            for( b=0; b<nb; b++, v+=2 )
                arr[a][b] = v;
        }

        for( a=0; a<na; a++ )
        {
            printf("#%d : { ", a);

            for( b=0; b<nb; b++ )
                printf("%2d  ", arr[a][b]);

            printf("}\n");
        }
    }

    return 0;
}
