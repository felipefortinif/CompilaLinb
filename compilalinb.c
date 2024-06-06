//Felipe Fortini Franco 2220501 3WC
//Rodrigo Lorente Kauer 

#include <stdlib.h>
#include <string.h>
#include "compilalinb.h"


static void error (const char *msg, int line) {
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
}

int escrevePrologo(unsigned char codigo[], int i){
  codigo[i++] = 0x55;codigo[i++] = 0x48;codigo[i++] = 0x89;codigo[i++] = 0xe5; 
  return i;
}

int escreveFim(unsigned char codigo[], int i){
  codigo[i++] = 0xc9;codigo[i++] = 0xc3;
  return i;
}

///////////////////////////////////////////////////// FUNCAO PRINCIPAL

funcp CompilaLinB (FILE *f, unsigned char codigo[]) {
  int line = 1;
  int  c;
  int i = 0;
  
  
  i = escrevePrologo(codigo, i);

  while ((c = fgetc(f)) != EOF) {
    switch (c) {
      case 'r': { /* retorno */
        char c0;
        if (fscanf(f, "et%c", &c0) != 1)
          error("comando invalido", line);
        i = escreveFim(codigo, i);
        printf("ret\n");
        break;
      }
      case 'v': 
      case 'p': {  /* atribuicao */
        int idx0, idx1, idx2;
        char var0 = c, var1, var2, op;
        if (fscanf(f, "%d <= %c%d %c %c%d", &idx0, &var1, &idx1,
                   &op, &var2, &idx2) != 6)
            error("comando invalido", line);
          printf("%c%d = %c%d %c %c%d\n",
                var0, idx0, var1, idx1, op, var2, idx2);
        break;
      }
      case 'i': { /* desvio */
        char var0;
        int idx0, num;
        if (fscanf(f, "f %c%d %d", &var0, &idx0, &num) != 3)
            error("comando invalido", line);
          printf("if %c%d %d\n", var0, idx0, num);
        break;
      }
      default: error("comando desconhecido", line);
    }
    line ++;
    fscanf(f, " ");
  }
  
  return (funcp)codigo;
}
