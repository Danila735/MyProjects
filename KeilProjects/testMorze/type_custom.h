#ifndef TYPE_CUSTOM_H
#define TYPE_CUSTOM_H

#define StrobePin1     GPIO_Pin_0
#define StrobePin2    GPIO_Pin_3
#define RXPin       GPIO_Pin_1
#define TXPin       GPIO_Pin_2

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"     // Файл с функциями управления ножками контроллера
#include "stm32f10x_rcc.h"      // Управление тактированием
#include <stdint.h>             // Правильные типы данных, вместо всяких int, char и тому подобных
#include <stdio.h>

#endif /* TYPE_CUSTOM_H */