#include <stdio.h>

int main(void){
  int num = 5;
  unsigned char byte1, byte2, byte3, byte4;
  byte1 = (num >> 24) & 0xFF;
  byte2 = (num >> 16) & 0xFF;
  byte3 = (num >> 8) & 0xFF;
  byte4 = num & 0xFF;
  
  printf("%02X %02X %02X %02X\n", byte4, byte3, byte2, byte1);
  return 0;
}
