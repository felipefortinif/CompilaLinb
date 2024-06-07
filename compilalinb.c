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

int atribuicao(unsigned char codigo[], int i, char c, int idx0, char var1, int idx1, char op, char var2, int idx2){
  // Primeiro faz o mov do primeiro operador para o valor que vai receber. Depois faz o 
  // add/sub/imul do segundo operador ao valor que vai receber.
  
  // mov do primeiro operador para o valor que vai receber
  switch(var1) {// quando o primeiro operador eh uma constante
    case '$': {
      unsigned char byte1, byte2, byte3, byte4;
      byte1 = (idx1 >> 24) & 0xFF;
      byte2 = (idx1 >> 16) & 0xFF;
      byte3 = (idx1 >> 8) & 0xFF;
      byte4 = idx1 & 0xFF;

      switch(c){
        case 'v':{
          switch(idx0){
            case 1:{
              codigo[i++] = 0xb8; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
            }
            case 2:{
              codigo[i++] = 0xba; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
            }
            case 3:{
              codigo[i++] = 0xb9; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
            }
            case 4:{
              codigo[i++] = 0x41; codigo[i++] = 0xb8; codigo[i++] = byte4; 
              codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1;                
            }
          }
        }
        case 'p':{
          switch(idx0){
            case 1:{
              codigo[i++] = 0xbf; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
            }
            case 2:{
              codigo[i++] = 0xbe; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
            }
          }
        }
      }
    }
    // quando o primeiro operador eh varp
    case 'p':
    case 'v':{
      switch(c){// pega o valor que vai receber
        case 'v':{// valor que vai receber eh var
          if (var1 == 'v'){// primeiro operador eh var
            switch(idx0){
              case 1:{// valor que vai receber eh v1
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;

                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc0;
                  }
                  case 2:{
                    codigo[i++] = 0xd0;
                  }
                  case 3:{
                    codigo[i++] = 0xc8;
                  }
                  case 4:{
                    codigo[i++] = 0xc0;
                  }
                }
              }
              case 2:{// valor que vai receber eh v2
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;
                
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc2;
                  }
                  case 2:{
                    codigo[i++] = 0xd2;
                  }
                  case 3:{
                    codigo[i++] = 0xca;
                  }
                  case 4:{
                    codigo[i++] = 0xc2;
                  }
                }
              }
              case 3:{// valor que vai receber eh v3
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;
                
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc1;
                  }
                  case 2:{
                    codigo[i++] = 0xd1;
                  }
                  case 3:{
                    codigo[i++] = 0xc9;
                  }
                  case 4:{
                    codigo[i++] = 0xc1;
                  }
                }
              }
              case 4:{// valor que vai receber eh v4
                if(idx1 == 4){
                  codigo[i++] = 0x45;
                }
                else{
                  codigo[i++] = 0x41;
                }
                codigo[i++] = 0x89;
                
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc0;
                  }
                  case 2:{
                    codigo[i++] = 0xd0;
                  }
                  case 3:{
                    codigo[i++] = 0xc8;
                  }
                  case 4:{
                    codigo[i++] = 0xc0;
                  }
                }
              }
            } 
          }
          else if(var1 == 'p'){// primeiro operador eh param
            switch(idx0){
              case 1:{// valor que vai receber eh v1
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xf8;
                  }
                  case 2:{
                    codigo[i++] = 0xf0;
                  }
                }
              }
              case 2:{// valor que vai receber eh v2
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xfa;
                  }
                  case 2:{
                    codigo[i++] = 0xf2;
                  }
                }
              }
              case 3:{// valor que vai receber eh v3
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xf9;
                  }
                  case 2:{
                    codigo[i++] = 0xf1;
                  }
                }
              }
              case 4:{// valor que vai receber eh v4
                codigo[i++] = 0x41; codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xf8;
                  }
                  case 2:{
                    codigo[i++] = 0xf0;
                  }
                }
              }
            } 
          }
        }
        case 'p':{// valor que vai receber eh param
          if (var1 == 'v'){// primeiro operador eh var
            switch(idx0){
              case 1:{// valor que vai receber eh p1
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;

                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc7;
                  }
                  case 2:{
                    codigo[i++] = 0xd7;
                  }
                  case 3:{
                    codigo[i++] = 0xcf;
                  }
                  case 4:{
                    codigo[i++] = 0xc7;
                  }
                }
              }
              case 2:{// valor que vai receber eh p2
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;
                
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc6;
                  }
                  case 2:{
                    codigo[i++] = 0xd6;
                  }
                  case 3:{
                    codigo[i++] = 0xce;
                  }
                  case 4:{
                    codigo[i++] = 0xc6;
                  }
                }
              }
            } 
          }
          else if(var1 == 'p'){// primeiro operador eh param
            switch(idx0){
              case 1:{// valor que vai receber eh p1
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xff;
                  }
                  case 2:{
                    codigo[i++] = 0xf7;
                  }
                }
              }
              case 2:{// valor que vai receber eh p2
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xfe;
                  }
                  case 2:{
                    codigo[i++] = 0xf6;
                  }
                }
              }
            } 
          }
        }
      }
    }
  }

  // add/sub/imul do segundo operador para o valor que vai receber


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
      case 'p': {  /* atribuicao param*/
        int idx0, idx1, idx2;
        char var0 = c, var1, var2, op;
        if (fscanf(f, "%d <= %c%d %c %c%d", &idx0, &var1, &idx1,
                   &op, &var2, &idx2) != 6)
            error("comando invalido", line);
          printf("%c%d = %c%d %c %c%d\n",
                var0, idx0, var1, idx1, op, var2, idx2);
        i = atribuicao(codigo, i, c, idx0, var1, idx1, op, var2, idx2);
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
