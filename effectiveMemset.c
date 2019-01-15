#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "clock.h"
#pragma pack(1)
void* effective_memset(void *s, unsigned long cs, size_t n,double *cyc) {
  /* align to K */
  size_t K = sizeof(unsigned long);
  size_t cnt = 0;
  unsigned char *schar = s;
  double a = 0;
  double b = 0;
  double c = 0;
  start_comp_counter();
  while (cnt < n) {
    if ((size_t)schar % K == 0) {
      break;
    }
    *schar++ = (unsigned char)cs;
    cnt++;
  }
  a = get_comp_counter();
  /* set K chars one time */
  unsigned long *slong = (unsigned long *)schar;
  size_t rest = n - cnt;
  size_t loop = rest / K;
  size_t tail = rest % K;
  start_comp_counter();
  for (size_t i = 0; i < loop; i++) {
    *slong++ = cs;
  }
  b = get_comp_counter();
  /* pad the tail part */
  schar = (unsigned char *)slong;
  start_comp_counter();
  for (size_t i = 0; i < tail; i++) {
    *schar++ = (unsigned char)cs;
  }
  c = get_comp_counter();

  *cyc = a + b + c;
  int *bbbbb = (int*)s;
  //printf("%d\n",bbbbb[0]);
  return s;
}
int main(int argc, char const *argv[])
{
    size_t space = sizeof(char) * 65537;
    void* effective_space = malloc(sizeof(char)*65537);
    unsigned long effective_fill = ~0;
    double cyc ;
    effective_memset(effective_space+1, effective_fill, space, &cyc);
    float CPE = cyc / 65537;
    printf("CPE = %f\n", CPE);

    return 0;
}