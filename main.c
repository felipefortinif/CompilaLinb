#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "compilalinb.h"

int main(void){
  FILE *myfp;

  if ((myfp = fopen ("teste4.linb", "r")) == NULL) {
    perror ("nao conseguiu abrir arquivo!");
    exit(1);
  }
  
  unsigned char codigo[1000];
  
  funcp func = compilaLinB(myfp, codigo);

  printf("\nCodigo:");
  for (int i = 0; i < 35; i++){
    printf("\n%02x", codigo[i]);  
  }
  printf("\n");
  
  assert(func != NULL);
  assert((*func)(6) == 	91);
  printf("\nOK\n");
  
  return 0;
}
