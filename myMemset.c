#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "clock.h"

void *my_memset(void *s, int cs, size_t n,double *cyc) {
    
    uint8_t *schar = (uint8_t *) s;
    uint64_t check = 0x07;

    start_comp_counter();
    while (n-- && ((uint64_t) schar & check)) {
        
        *(schar++) = (uint8_t) cs;
    }

    uint64_t *slong = (uint64_t *)((void *) schar);
    
    while((n/8) > 0){
        
        *slong++ = (uint64_t) cs;
        n -= 8;
    }

    schar = (uint8_t *)((void *) slong);

    while(n--){

        *schar++ = (uint8_t) cs;
    }
    *cyc = get_comp_counter();
    return s;   
}

int main(int argc, char const *argv[])
{
    size_t space = sizeof(char) * 65537;
    void* my_space = malloc(sizeof(char)*65537);
    unsigned long my_fill = ~0;
    double cyc ;
    my_memset(my_space, my_fill, space, &cyc);
    double CPE = cyc / 65537;
    printf("CPE = %f\n", CPE);
    free(my_space);
    return 0;
}