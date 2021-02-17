#include "type_custom.h"
#include "rxtx.h"

void TransmitSymbol (uint8_t *symb) { 
 
    printf("Start transmit symbol...\n");
    GPIO_WriteBit(GPIOA, StrobePin1, Bit_SET);
 
    // PORT_SetBits(GPIOA, StrobePin1); 
 
    for(uint8_t i = 0; i < 8; i++) { 
        if(symb[i] == '.')
            GPIO_WriteBit(GPIOA, TXPin, Bit_SET);            
            // PORT_SetBits(MDR_PORTA, TXPin); 
        else if(symb[i] == '-')
            GPIO_WriteBit(GPIOA, TXPin, Bit_RESET);             
            // PORT_ResetBits(MDR_PORTA, TXPin); 
        else
            break;
        Delay(200); 
    }
    GPIO_WriteBit(GPIOA, StrobePin1, Bit_RESET);    
    // PORT_ResetBits(MDR_PORTA, StrobePin1); 
    printf("End transmit symbol!\n");
    GPIO_WriteBit(GPIOA, TXPin, Bit_RESET);     
    // PORT_ResetBits(MDR_PORTA, TXPin);
}

void ReceiveSymbol(uint8_t *symb)
{
    printf("Start receive symbol!\n");
    
    uint8_t i = 0;
    
    // while(PORT_ReadInputDataBit(MDR_PORTA, StrobePin2))
    while(GPIO_ReadInputDataBit(GPIOA, StrobePin2))
    {
        //if(PORT_ReadInputDataBit(MDR_PORTA, RXPin) != 0)
        if(GPIO_ReadInputDataBit(GPIOA, RXPin) != 0)
            symb[i] = '.';
        else 
            symb[i] = '-';
        i++;
        Delay(200);
    }
    printf("End receive symbol!\n");
    printf("Sign: %s \n", symb);
}

