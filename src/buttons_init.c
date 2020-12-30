#include "buttons_init.h"
#include "stm32f1xx.h"
GPIO_InitTypeDef gpio;

void buttonsInit(void){
	//konfiguracja przyciskow do ustawiania godziny i daty i alarmu (umiejscowione na porcie B
	gpio.Mode = GPIO_MODE_INPUT;//piny jako wejœcia
	gpio.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_8|GPIO_PIN_9; //piny 5,6,8 pos³u¿a do ustawiania czasu, (pin 9 do zmiany stanu
	gpio.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOC, &gpio);

	gpio.Pin = GPIO_PIN_10; //konfiguracja pinu jako wyjscia dla buzzera
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &gpio);
}
