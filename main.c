#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "compilalinb.h"

int main(void){
  FILE *myfp;

  if ((myfp = fopen ("teste0.linb", "r")) == NULL) {
    perror ("nao conseguiu abrir arquivo!");
    exit(1);
  }
  
  unsigned char codigo[1000];
  funcp func = CompilaLinB(myfp, codigo);

  printf("\nCodigo:");
  for (int i = 0; i < 10; i++){
    printf("\n%02x", codigo[i]);  
  }
  
  //assert(func != NULL);
  //assert((*func)() == 1);
  //printf("OK");
  
  return 0;
}
