#include <stdint.h>

void UARTInit();
void sendChar(uint8_t data);
char getChar();
void sendString (char *string);