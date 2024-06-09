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
   switch(var1) {
    case '$': {// quando o primeiro operador eh uma constante
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
              break;
            }
            case 2:{
              codigo[i++] = 0xba; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
              break;
            }
            case 3:{
              codigo[i++] = 0xb9; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
              break;
            }
            case 4:{
              codigo[i++] = 0x41; codigo[i++] = 0xb8; codigo[i++] = byte4; 
              codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1;   
              break;             
            }
          }
          break;
        }
        case 'p':{
          switch(idx0){
            case 1:{
              codigo[i++] = 0xbf; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
              break;
            }
            case 2:{
              codigo[i++] = 0xbe; codigo[i++] = byte4; codigo[i++] = byte3; 
              codigo[i++] = byte2; codigo[i++] = byte1;
              break;
            }
          }
          break;
        }
      }
      break;
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
                    codigo[i++] = 0xc0; break;
                  }
                  case 2:{
                    codigo[i++] = 0xd0; break;
                  }
                  case 3:{
                    codigo[i++] = 0xc8; break;
                  }
                  case 4:{
                    codigo[i++] = 0xc0; break;
                  }
                }
                break;
              }
              case 2:{// valor que vai receber eh v2
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;
                
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc2; break;
                  }
                  case 2:{
                    codigo[i++] = 0xd2; break;
                  }
                  case 3:{
                    codigo[i++] = 0xca; break;
                  }
                  case 4:{
                    codigo[i++] = 0xc2; break;
                  }
                }
                break;
              }
              case 3:{// valor que vai receber eh v3
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;
                
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc1; break;
                  }
                  case 2:{
                    codigo[i++] = 0xd1; break;
                  }
                  case 3:{
                    codigo[i++] = 0xc9; break;
                  }
                  case 4:{
                    codigo[i++] = 0xc1; break;
                  }
                }
                break;
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
                    codigo[i++] = 0xc0; break;
                  }
                  case 2:{
                    codigo[i++] = 0xd0; break;
                  }
                  case 3:{
                    codigo[i++] = 0xc8; break;
                  }
                  case 4:{
                    codigo[i++] = 0xc0; break;
                  }
                }
                break;
              }
            } 
          }
          else if(var1 == 'p'){// primeiro operador eh param
            switch(idx0){
              case 1:{// valor que vai receber eh v1
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xf8; break;
                  }
                  case 2:{
                    codigo[i++] = 0xf0; break;
                  }
                }
                break;
              }
              case 2:{// valor que vai receber eh v2
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xfa; break;
                  }
                  case 2:{
                    codigo[i++] = 0xf2; break;
                  }
                }
                break;
              }
              case 3:{// valor que vai receber eh v3
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xf9; break;
                  }
                  case 2:{
                    codigo[i++] = 0xf1; break;
                  }
                }
                break;
              }
              case 4:{// valor que vai receber eh v4
                codigo[i++] = 0x41; codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xf8; break;
                  }
                  case 2:{
                    codigo[i++] = 0xf0; break;
                  }
                }
                break;
              }
            } 
          }
          break;
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
                    codigo[i++] = 0xc7; break;
                  }
                  case 2:{
                    codigo[i++] = 0xd7; break;
                  }
                  case 3:{
                    codigo[i++] = 0xcf; break;
                  }
                  case 4:{
                    codigo[i++] = 0xc7; break;
                  }
                }
                break;
              }
              case 2:{// valor que vai receber eh p2
                if(idx1 == 4){
                  codigo[i++] = 0x44;
                }
                codigo[i++] = 0x89;
                
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xc6; break;
                  }
                  case 2:{
                    codigo[i++] = 0xd6; break;
                  }
                  case 3:{
                    codigo[i++] = 0xce; break;
                  }
                  case 4:{
                    codigo[i++] = 0xc6; break;
                  } 
                }
                break;
              }
            } 
          }
          else if(var1 == 'p'){// primeiro operador eh param
            switch(idx0){
              case 1:{// valor que vai receber eh p1
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xff; break;
                  }
                  case 2:{
                    codigo[i++] = 0xf7; break;
                  }
                }
                break;
              }
              case 2:{// valor que vai receber eh p2
                codigo[i++] = 0x89;
                switch(idx1){// pega o primeiro operador
                  case 1:{
                    codigo[i++] = 0xfe; break;
                  }
                  case 2:{
                    codigo[i++] = 0xf6; break;
                  }
                }
                break;
              }
            } 
          }
          break;
        }
      }
      break;
    }
  }
 
  // add/sub/imul do segundo operador para o valor que vai receber
  switch(op){
    case '+':{// quando a operacao eh uma adicao
      switch(var2) {
        case '$': {// quando o segundo operador eh uma constante
          unsigned char byte1, byte2, byte3, byte4;
          byte1 = (idx2 >> 24) & 0xFF;
          byte2 = (idx2 >> 16) & 0xFF;
          byte3 = (idx2 >> 8) & 0xFF;
          byte4 = idx2 & 0xFF;

          switch(c){// pega a variavel que vai receber
            case 'v':{
              switch(idx0){
                case 1:{
                  codigo[i++] = 0x05; codigo[i++] = byte4; codigo[i++] = byte3; 
                  codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 2:{
                  codigo[i++] = 0x81; codigo[i++] = 0xc2; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 3:{
                  codigo[i++] = 0x81; codigo[i++] = 0xc1; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 4:{
                  codigo[i++] = 0x41; codigo[i++] = 0x81; codigo[i++] = 0xc0; codigo[i++] = byte4; 
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;              
                }
              }
              break;
            }
            case 'p':{
              switch(idx0){
                case 1:{
                  codigo[i++] = 0x81; codigo[i++] = 0xc7; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 2:{
                  codigo[i++] = 0x81; codigo[i++] = 0xc6; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
              }
              break;
            }
          }
          break;
        }
        // quando o segundo operador eh varp
        case 'p':
        case 'v':{
          switch(c){// pega o valor que vai receber
            case 'v':{// valor que vai receber eh var
              if (var2 == 'v'){// segundo operador eh var
                switch(idx0){
                  case 1:{// valor que vai receber eh v1
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x01;

                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd0; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc8; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc0; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh v2
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x01;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc2; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd2; break;
                      }
                      case 3:{
                        codigo[i++] = 0xca; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc2; break;
                      }
                    }
                    break;
                  }
                  case 3:{// valor que vai receber eh v3
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x01;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc1; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd1; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc9; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc1; break;
                      }
                    }
                    break;
                  }
                  case 4:{// valor que vai receber eh v4
                    if(idx2 == 4){
                      codigo[i++] = 0x45;
                    }
                    else{
                      codigo[i++] = 0x41;
                    }
                    codigo[i++] = 0x01;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd0; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc8; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc0; break;
                      }
                    }
                    break;
                  }
                } 
              }
              else if(var2 == 'p'){// segundo operador eh param
                switch(idx0){
                  case 1:{// valor que vai receber eh v1
                    codigo[i++] = 0x01;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf8; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf0; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh v2
                    codigo[i++] = 0x01;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xfa; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf2; break;
                      }
                    }
                    break;
                  }
                  case 3:{// valor que vai receber eh v3
                    codigo[i++] = 0x01;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf9; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf1; break;
                      }
                    }
                    break;
                  }
                  case 4:{// valor que vai receber eh v4
                    codigo[i++] = 0x41; codigo[i++] = 0x01;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf8; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf0; break;
                      }
                    }
                    break;
                  }
                } 
              }
              break;
            }
            case 'p':{// valor que vai receber eh param
              if (var2 == 'v'){// segundo operador eh var
                switch(idx0){
                  case 1:{// valor que vai receber eh p1
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x01;

                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc7; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd7; break;
                      }
                      case 3:{
                        codigo[i++] = 0xcf; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc7; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh p2
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x01;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc6; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd6; break;
                      }
                      case 3:{
                        codigo[i++] = 0xce; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc6; break;
                      }
                    }
                    break;
                  }
                } 
              }
              else if(var2 == 'p'){// segundo operador eh param
                switch(idx0){
                  case 1:{// valor que vai receber eh p1
                    codigo[i++] = 0x01;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xff; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf7; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh p2
                    codigo[i++] = 0x01;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xfe; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf6; break;
                      }
                    }
                    break;
                  }
                } 
              }
              break;
            }
          }
          break;
        }
      }
      break;
    }

    case '-':{// quando a operacao eh uma subtracao
      switch(var2) {
        case '$': {// quando o segundo operador eh uma constante
          unsigned char byte1, byte2, byte3, byte4;
          byte1 = (idx2 >> 24) & 0xFF;
          byte2 = (idx2 >> 16) & 0xFF;
          byte3 = (idx2 >> 8) & 0xFF;
          byte4 = idx2 & 0xFF;

          switch(c){// pega a variavel que vai receber
            case 'v':{
              switch(idx0){
                case 1:{
                  codigo[i++] = 0x2d; codigo[i++] = byte4; codigo[i++] = byte3; 
                  codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 2:{
                  codigo[i++] = 0x81; codigo[i++] = 0xea; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 3:{
                  codigo[i++] = 0x81; codigo[i++] = 0xe9; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 4:{
                  codigo[i++] = 0x41; codigo[i++] = 0x81; codigo[i++] = 0xe8; codigo[i++] = byte4; 
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;              
                }
              }
              break;
            }
            case 'p':{
              switch(idx0){
                case 1:{
                  codigo[i++] = 0x81; codigo[i++] = 0xef; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 2:{
                  codigo[i++] = 0x81; codigo[i++] = 0xee; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
              }
              break;
            }
          }
          break;
        }
        // quando o segundo operador eh varp
        case 'p':
        case 'v':{
          switch(c){// pega o valor que vai receber
            case 'v':{// valor que vai receber eh var
              if (var2 == 'v'){// segundo operador eh var
                switch(idx0){
                  case 1:{// valor que vai receber eh v1
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x29;

                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd0; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc8; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc0; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh v2
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x29;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc2; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd2; break;
                      }
                      case 3:{
                        codigo[i++] = 0xca; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc2; break;
                      }
                    }
                    break;
                  }
                  case 3:{// valor que vai receber eh v3
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x29;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc1; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd1; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc9; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc1; break;
                      }
                    }
                    break;
                  }
                  case 4:{// valor que vai receber eh v4
                    if(idx2 == 4){
                      codigo[i++] = 0x45;
                    }
                    else{
                      codigo[i++] = 0x41;
                    }
                    codigo[i++] = 0x29;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd0; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc8; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc0; break;
                      }
                    }
                    break;
                  }
                } 
              }
              else if(var2 == 'p'){// segundo operador eh param
                switch(idx0){
                  case 1:{// valor que vai receber eh v1
                    codigo[i++] = 0x29;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf8; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf0; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh v2
                    codigo[i++] = 0x29;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xfa; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf2; break;
                      }
                    }
                    break;
                  }
                  case 3:{// valor que vai receber eh v3
                    codigo[i++] = 0x29;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf9; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf1; break;
                      }
                    }
                    break;
                  }
                  case 4:{// valor que vai receber eh v4
                    codigo[i++] = 0x41; codigo[i++] = 0x29;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf8; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf0; break;
                      }
                    }
                    break;
                  }
                } 
              }
              break;
            }
            case 'p':{// valor que vai receber eh param
              if (var2 == 'v'){// segundo operador eh var
                switch(idx0){
                  case 1:{// valor que vai receber eh p1
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x29;

                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc7; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd7; break;
                      }
                      case 3:{
                        codigo[i++] = 0xcf; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc7; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh p2
                    if(idx2 == 4){
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x29;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc6; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd6; break;
                      }
                      case 3:{
                        codigo[i++] = 0xce; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc6; break;
                      }
                    }
                    break;
                  }
                } 
              }
              else if(var2 == 'p'){// segundo operador eh param
                switch(idx0){
                  case 1:{// valor que vai receber eh p1
                    codigo[i++] = 0x29;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xff; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf7; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh p2
                    codigo[i++] = 0x29;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xfe; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf6; break;
                      }
                    }
                    break;
                  }
                } 
              }
              break;
            }
          }
          break;
        }
      }
      break;
    }
    
    case '*':{// quando a operacao eh uma multiplicacao
      switch(var2) {
        case '$': {// quando o segundo operador eh uma constante
          unsigned char byte1, byte2, byte3, byte4;
          byte1 = (idx2 >> 24) & 0xFF;
          byte2 = (idx2 >> 16) & 0xFF;
          byte3 = (idx2 >> 8) & 0xFF;
          byte4 = idx2 & 0xFF;

          switch(c){// pega a variavel que vai receber
            case 'v':{
              switch(idx0){
                case 1:{
                  codigo[i++] = 0x69; codigo[i++] = 0xc0; codigo[i++] = byte4;
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 2:{
                  codigo[i++] = 0x69; codigo[i++] = 0xd2; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 3:{
                  codigo[i++] = 0x69; codigo[i++] = 0xc9; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 4:{
                  codigo[i++] = 0x45; codigo[i++] = 0x69; codigo[i++] = 0xc0; codigo[i++] = byte4; 
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;              
                }
              }
              break;
            }
            case 'p':{
              switch(idx0){
                case 1:{
                  codigo[i++] = 0x69; codigo[i++] = 0xff; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
                case 2:{
                  codigo[i++] = 0x69; codigo[i++] = 0xf6; codigo[i++] = byte4;  
                  codigo[i++] = byte3; codigo[i++] = byte2; codigo[i++] = byte1; break;
                }
              }
              break;
            }
          }
          break;
        }
        // quando o segundo operador eh varp
        case 'p':
        case 'v':{
          switch(c){// pega o valor que vai receber
            case 'v':{// valor que vai receber eh var
              if (var2 == 'v'){// segundo operador eh var
                switch(idx0){
                  case 1:{// valor que vai receber eh v1
                    if(idx2 == 4){
                      codigo[i++] = 0x41;
                    }
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;

                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xc2; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc1; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc0; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh v2
                    if(idx2 == 4){
                      codigo[i++] = 0x41;
                    }
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xd0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd2; break;
                      }
                      case 3:{
                        codigo[i++] = 0xd1; break;
                      }
                      case 4:{
                        codigo[i++] = 0xd0; break;
                      }
                    }
                    break;
                  }
                  case 3:{// valor que vai receber eh v3
                    if(idx2 == 4){
                      codigo[i++] = 0x41;
                    }
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc8; break;
                      }
                      case 2:{
                        codigo[i++] = 0xca; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc9; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc8; break;
                      }
                    }
                    break;
                  }
                  case 4:{// valor que vai receber eh v4
                    if(idx2 == 4){
                      codigo[i++] = 0x45;
                    }
                    else{
                      codigo[i++] = 0x44;
                    }
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xc2; break;
                      }
                      case 3:{
                        codigo[i++] = 0xc1; break;
                      }
                      case 4:{
                        codigo[i++] = 0xc0; break;
                      }
                    }
                    break;
                  }
                } 
              }
              else if(var2 == 'p'){// segundo operador eh param
                switch(idx0){
                  case 1:{// valor que vai receber eh v1
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc7; break;
                      }
                      case 2:{
                        codigo[i++] = 0xc6; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh v2
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xd7; break;
                      }
                      case 2:{
                        codigo[i++] = 0xd6; break;
                      }
                    }
                    break;
                  }
                  case 3:{// valor que vai receber eh v3
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xcf; break;
                      }
                      case 2:{
                        codigo[i++] = 0xce; break;
                      }
                    }
                    break;
                  }
                  case 4:{// valor que vai receber eh v4
                    codigo[i++] = 0x44; codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xc7; break;
                      }
                      case 2:{
                        codigo[i++] = 0xc6; break;
                      }
                    }
                    break;
                  }
                } 
              }
              break;
            }
            case 'p':{// valor que vai receber eh param
              if (var2 == 'v'){// segundo operador eh var
                switch(idx0){
                  case 1:{// valor que vai receber eh p1
                    if(idx2 == 4){
                      codigo[i++] = 0x41;
                    }
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;

                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf8; break;
                      }
                      case 2:{
                        codigo[i++] = 0xfa; break;
                      }
                      case 3:{
                        codigo[i++] = 0xf9; break;
                      }
                      case 4:{
                        codigo[i++] = 0xf8; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh p2
                    if(idx2 == 4){
                      codigo[i++] = 0x41;
                    }
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf0; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf2; break;
                      }
                      case 3:{
                        codigo[i++] = 0xf1; break;
                      }
                      case 4:{
                        codigo[i++] = 0xf0; break;
                      }
                    }
                    break;
                  }
                } 
              }
              else if(var2 == 'p'){// segundo operador eh param
                switch(idx0){
                  case 1:{// valor que vai receber eh p1
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xff; break;
                      }
                      case 2:{
                        codigo[i++] = 0xfe; break;
                      }
                    }
                    break;
                  }
                  case 2:{// valor que vai receber eh p2
                    codigo[i++] = 0x0f; codigo[i++] = 0xaf;
                    switch(idx2){// pega o segundo operador
                      case 1:{
                        codigo[i++] = 0xf7; break;
                      }
                      case 2:{
                        codigo[i++] = 0xf6; break;
                      }
                    }
                    break;
                  }
                } 
              }
              break;
            }
          }
          break;
        }
      }
      break;
    }

  }
  return i;
}

int desvio(unsigned char codigo[], int i, char var0, int idx0){
  //cmp $0 %...
  switch(var0){
    case 'v':{
      if(idx0 == 4){
        codigo[i++] = 0x41;
      }
      codigo[i++] = 0x83;
      switch(idx0){
        case 1:{
          codigo[i++] = 0xf8; codigo[i++] = 0x00;
          break;
        }
        case 2:{
          codigo[i++] = 0xfa; codigo[i++] = 0x00;
          break;
        }
        case 3:{
          codigo[i++] = 0xf9; codigo[i++] = 0x00;
          break;
        }
        case 4:{
          codigo[i++] = 0xf8; codigo[i++] = 0x00;
          break;
        }
      }
      break;
    }
    case 'p':{
      codigo[i++] = 0x83;
      switch(idx0){
        case 1:{
          codigo[i++] = 0xff; codigo[i++] = 0x00;
          break;
        }
        case 2:{
          codigo[i++] = 0xfe; codigo[i++] = 0x00;
          break;
        }
      }
      break;
    }
  }

  //jne <linha>
  codigo[i++] = 0x0f; codigo[i++] = 0x85; codigo[i++] = 0x00; codigo[i++] = 0x00;
  codigo[i++] = 0x00; codigo[i++] = 0x00;
  
  return i;
}

void escreve_offsets(unsigned char codigo[], int endereco_linhas[], int jmps[], int bytes){
  int jmp = 0;
  for(int k = 0; k <= bytes; k++){
    if(codigo[k] == 0x0f && codigo[k+1] == 0x85){
      
      int destino = jmps[jmp];
      jmp++;

      int offset = endereco_linhas[destino];

      unsigned char byte1, byte2, byte3, byte4;
      byte1 = (offset >> 24) & 0xFF;
      byte2 = (offset >> 16) & 0xFF;
      byte3 = (offset >> 8) & 0xFF;
      byte4 = offset & 0xFF;

      codigo[k+2] = byte4; codigo[k+3] = byte3; codigo[k+4] = byte2; codigo[k+5] = byte1;

    }
  }

}

///////////////////////////////////////////////////// FUNCAO PRINCIPAL

funcp CompilaLinB (FILE *f, unsigned char codigo[]) {
  int line = 1;
  int  c;
  int i = 0;
  int endereco_linhas[50];
  int jmps[50];
  int j = 0;
  
  i = escrevePrologo(codigo, i);

  while ((c = fgetc(f)) != EOF) {
    endereco_linhas[line] = i;
    switch (c) {
      case 'r': { /* retorno */
        char c0;
        if (fscanf(f, "et%c", &c0) != 1)
          error("comando invalido1", line);

        i = escreveFim(codigo, i);
        printf("ret\n");
        break;
      }
      case 'v':
      case 'p': {  /* atribuicao*/
        int idx0, idx1, idx2;
        char var0 = c, var1, var2, op;
        if (fscanf(f, "%d <= %c%d %c %c%d", &idx0, &var1, &idx1, &op, &var2, &idx2) != 6)
            error("comando invalido2", line);
          printf("%c%d <= %c%d %c %c%d\n", var0, idx0, var1, idx1, op, var2, idx2);

        i = atribuicao(codigo, i, c, idx0, var1, idx1, op, var2, idx2);
        break;
      }
      case 'i': { /* desvio */
        char var0;
        int idx0, num;
        if (fscanf(f, "f %c%d %d", &var0, &idx0, &num) != 3)
            error("comando invalido3", line);

        i = desvio(codigo, i, var0, idx0);
        jmps[j] = num;
        j++;

        printf("if %c%d %d\n", var0, idx0, num);
        break;
      }
      default: error("comando desconhecido", line);
    }
    line ++;
    fscanf(f, " ");
  }
  
  escreve_offsets(codigo, endereco_linhas, jmps, i);
  return (funcp)codigo;
}
