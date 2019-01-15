#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "clock.h"
#pragma pack(1)

void *basic_memset(void *s, int c, size_t n,double *cyc)
{
    size_t cnt = 0;
    unsigned char *schar = s;

    start_comp_counter();
    while (cnt < n){
        *schar++ = (unsigned char) c;
        cnt++;
    }
    *cyc = get_comp_counter();
    
    return s;
}

int main(int argc, char const *argv[])
{
    size_t space = sizeof(char) * 65537;
    void* basic_space = malloc(space);
    int basic_fill = 0xff;
    double cyc;
    basic_memset(basic_space, basic_fill, space, &cyc);
    float CPE = cyc / 65537;
    printf("CPE = %f\n", CPE);
    return 0;
}