#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "compilalinb.h"

int main(void){
  FILE *myfp;
  //funcp func;

  if ((myfp = fopen ("teste0.linb", "r")) == NULL) {
    perror ("nao conseguiu abrir arquivo!");
    exit(1);
  }
  
  funcp func = CompilaLinB(myfp);
  
  assert(func != NULL);
  assert((*func)() == 1);
  printf("OK");
  
  return 0;
}
