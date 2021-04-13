#include <stdio.h>
#include <stdlib.h>

int main(){
        int i;
        const int ci = 123;

        /* declare a pointer to a const.. */
        const int *cpi;

        /* ordinary pointer to a non-const */
        int *ncpi;

        cpi = &ci;
        ncpi = &i;

        /*
         * this is allowed
         */
        cpi = ncpi;

        /*
         * this needs a cast
         * because it is usually a big mistake,
         * see what it permits below.
         */
        ncpi = (int *)cpi;

        /*
         * now to get undefined behaviour...
         * modify a const through a pointer
         */
        *ncpi = 0;

        exit(EXIT_SUCCESS);
}
