#include "stm32f4xx.h"
#include <stdlib.h>
#include <stdint.h>
#include "RccConfig.h"
#include "Delay.h"

void UARTInit()
{
    // TX MCU Pin 9 --> RX Bluetooth Module
    RCC->AHB1ENR   |= RCC_AHB1ENR_GPIOAEN;      // Turn on GPIOA Clock
    GPIOA->MODER   |= GPIO_MODER_MODE2_1;       // PA2 AF Mode
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2; // Fastest Speed
    GPIOA->AFR[0]  |= (7 << 8) | (7 << 12);     // AF for USART2 for Tx(PA2) and Rx(PA3)
    // TX Bluetooth --> RX MCU Pin 10
    GPIOA->MODER   |= GPIO_MODER_MODE3_1;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;
    //UART Init
    RCC->APB1ENR  |=RCC_APB1ENR_USART2EN;         //Enable Clock for USART2
    USART2->CR1   = 0x00;                         // clearing register
    USART2->CR1   |= USART_CR1_UE;                // Enabling USART2
    USART2->CR1   &= ~(USART_CR1_M);              // 1start bit 8 data bits n stop bit
    USART2->BRR   = (7<<0) | (24<<4);                       // 45MHz 
    USART2->CR1   |= USART_CR1_TE | USART_CR1_RE; // Transmitter Enabled
}

void sendChar(uint8_t data)
{
    USART2->DR = data;
    while (!(USART2->SR & USART_SR_TC))
    {
        ;
    }
    
}
uint8_t getChar()
{
    while(!(USART2->SR & USART_SR_RXNE))
    {
        ;
    }
    uint8_t temp = USART2->DR;
    return temp;
}
char * getString()
{
    while(!(USART2->SR & USART_SR_RXNE))
    {
        ;
    }
    char* temp = USART2->DR;
    return temp;
}
void sendString (char *string)
{
	while (*string) sendChar (*string++);
}

int main (void)
{
    SysClockConfig();
    TIM6Config();
    UARTInit();

    while(1)
    {
        char *data = getString();
        sendString(data);
        Delay_ms(1000);
    }
}