
#include "morze.h"
#include "rxtx.h"



// StrobePin1    PORT_Pin_0
// StrobePin2    PORT_Pin_3
// RXPin       PORT_Pin_1
// TXPin       PORT_Pin_2

void clk_CoreConfig (uint32_t div, uint32_t mul);
void button_Init    (void);
bool button_State   (void);
void PinInitA       (PORT_OE_TypeDef mode, uint16_t pin);
void LedInit        ();
void LedMorze       (uint8_t *symbols);
void LedWrite       (bool on_off);

int main()
{   
    uint8_t counter = 0, symbol_tx[8], symbol_rx[8], numbBit = 0, tempValue = 255;
    //clk_CoreConfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul10);
    button_Init();
    PinInitA(PORT_OE_OUT, TXPin);
    PinInitA(PORT_OE_IN, RXPin);
    PinInitA(PORT_OE_OUT, StrobePin1);
    PinInitA(PORT_OE_IN, StrobePin2);
    LedInit();
    
    while(1) {
        
        
        //if (PORT_ReadInputDataBit(MDR_PORTA, StrobePin2)) {
        if (GPIO_ReadInputDataBit(GPIOA, StrobePin2)) {
            ClearSymbol(symbol_rx);
            ReceiveSymbol(symbol_rx);
            LedMorze(symbol_rx);
            tempValue = MorzeToChar(symbol_rx);
            tempValue == 255 ? printf("Symbol is undefined! \n") : printf("Char: %c \n", tempValue);
        }
        // Read button
        while (!button_State()) {
            counter++;
            Delay(500);
            if (counter == 4) printf("DEBUG INFO: Completed char! \n");
        }
        // Define sign
        if (counter > 0) {
            if (counter == 1) {
                symbol_tx[numbBit] = '.';
                numbBit++;
                printf("DEBUG INFO: %s \n", symbol_tx);
            }
            else if (counter < 4) {
                symbol_tx[numbBit] = '-';
                numbBit++;
                printf("DEBUG INFO: %s \n", symbol_tx);
            }
            else {
                 for (numbBit; numbBit < 8; ++numbBit)
                    symbol_tx[numbBit] = 'x';
            }
            // If end symbol
            if (numbBit == 8) {
                numbBit = 0;
                TransmitSymbol(symbol_tx);
                tempValue = MorzeToChar(symbol_tx);
                tempValue == 255 ? printf("Symbol is undefined! \n") : printf("Char: %c \n", tempValue);
            }
    }
        
        if (counter != 0) {
            //printf("numbSymb: %d \n", numbBit);
        }
        counter = 0;
        
    }
}

void LedMorze (uint8_t *symbols) {
    for (uint8_t i = 0; i < 8; ++i) {
        if (symbols[i] == '.') {
            LedWrite(1);
            Delay(500);
        }
        else if (symbols[i] == '-') {
            LedWrite(1);
            Delay(1500);
        }
        else {
            LedWrite(0);
            break;
        }
        LedWrite(0);
        Delay(500);
    }
}

void PinInitA(GPIO_OE_TypeDef mode, uint16_t pin)
{
    PORT_InitTypeDef PORT_InitStructure;
    PORT_InitStructure.PORT_OE = mode;
    PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
    PORT_InitStructure.PORT_Pin = (pin);
    GPIO_Init(GPIOA, &PORT_InitStructure);
}

//void PinInitA(PORT_OE_TypeDef mode, uint16_t pin)
//{
//    PORT_InitTypeDef PORT_InitStructure;
//    PORT_InitStructure.PORT_OE = mode;
//    PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
//    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
//    PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
//    PORT_InitStructure.PORT_Pin = (pin);
//    PORT_Init(MDR_PORTA, &PORT_InitStructure);
//}
void clk_CoreConfig(uint32_t div, uint32_t mul) {
    RCC_DeInit();
    RCC_HSEConfig( RCC_HSE_ON);
    uint8_t HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS)
    {
        RCC_HCLKConfig( RCC_SYSCLK_Div1);
        RCC_PCLK2Config( RCC_HCLK_Div1);
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        RCC_PLLCmd( ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }
        RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
    else 
    {   while (1)
        {
        }
    }
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
} 
//void clk_CoreConfig(uint32_t div, uint32_t mul) {
// //Реинициализация настроек тактирования
// //RST_CLK_DeInit();
// //Включение тактирования от внешнего источника HSE (High Speed External)
// RST_CLK_HSEconfig(RST_CLK_HSE_ON);
// //Проверка статуса HSE
// if (RST_CLK_HSEstatus() == ERROR) while (1);
// //Настройка делителя/умножителя частоты CPU_PLL(фазовая подстройка частоты)
// RST_CLK_CPU_PLLconfig(div, mul);
// //Включение CPU_PLL
// RST_CLK_CPU_PLLcmd(ENABLE);
// //Проверка статуса CPU_PLL
// if (RST_CLK_CPU_PLLstatus() == ERROR) while (1);
// //Коммутация выхода CPU_PLL на вход CPU_C3
// RST_CLK_CPU_PLLuse(ENABLE);
// //Выбор источника тактирования ядра процессора
// RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
// //Подача тактовой частоты на PORTC, PORTD
// RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
// RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
//} 

void button_Init(void) {
 //Создание структуры для инициализации порта
 GPIO_InitTypeDef GPIO_InitStructure;
 //Настройки порта: ввод, функция ввода/вывода, цифровой режим, минимальная скорость, Pin5
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_5);
 GPIO_Init(GPIOD, &GPIO_InitStructure);
}

//void button_Init(void) {
// //Создание структуры для инициализации порта
// PORT_InitTypeDef PORT_InitStructure;
// //Настройки порта: ввод, функция ввода/вывода, цифровой режим, минимальная скорость, Pin5
// PORT_InitStructure.PORT_OE = PORT_OE_IN;
// PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
// PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
// PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
// PORT_InitStructure.PORT_Pin = (PORT_Pin_5);
// PORT_Init(MDR_PORTD, &PORT_InitStructure);
//}
//Функция считывания текущего состояния кнопки SA4
bool button_State(void) {
    return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_5);
}

void LedInit()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_2);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

//void LedInit()
//{
//    PORT_InitTypeDef PORT_InitStructure;
//    PORT_InitStructure.PORT_OE = PORT_OE_OUT;
//    PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
//    PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
//    PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
//    PORT_InitStructure.PORT_Pin = (PORT_Pin_2);
//    PORT_Init(MDR_PORTC, &PORT_InitStructure);
//}

void LedWrite (bool on_off) {
    GPIO_WriteBit(GPIOC, GPIO_Pin_2, on_off ? Bit_SET : Bit_RESET);
}