/* Contributors :
 * - xyzzy @ kaskus.co.id
 */

#include <stdio.h>
#include <stdlib.h>


int main (int argc, char **argv)
{
    /*
     * https://www.gnu.org/software/libc/manual/html_node/Program-Arguments.html
     *
     * Since a null pointer always follows the last element,
     * which means argv[argc] == null pointer,
     * so we can write like these code below.
     *
     * @see also : pointer arithmetic
     */

    // argv[0] ignored
    while( *(++argv) )
    {
        printf( "ARGV : {%s}\n", *argv );
    }
    puts("");


    puts( "Hello Friends !!" );

    return 0;
}

    /*
    // argv[0] NOT ignored
    do
    {
        printf( "- {%s}\n", *argv );
    }
    while( *(++argv) );
    puts("");
    */
