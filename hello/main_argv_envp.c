/* Contributors :
 * - xyzzy @ kaskus.co.id
 */

#include <stdio.h>
#include <stdlib.h>


/* https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html
 * In Unix systems you can also define `main` using three arguments.
 *
 * The third argument envp gives the program’s environment;
 * it is the same as the value of environ.
 */
int main (int argc, char **argv, char **envp)
{

    while( *(++argv) )
    {
        printf( "ARGV : {%s}\n", *argv );
    }
    puts("");

    do
    {
        printf( "ENVP : {%s}\n", *envp );
    }
    while( *(++envp) );
    puts("");


    puts( "Hello Friends !!" );

    return 0;
}
