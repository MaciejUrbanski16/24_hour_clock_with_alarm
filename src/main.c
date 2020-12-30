/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "stm32f1xx.h"


#include "lcd_init.h"
#include "timers_init.h"
#include "buttons_init.h"

#include "time_preaparing.h"


//funkcja do obslugi przerwnia zewnetrznego od klawiszy pinow 2,3,4,5


volatile uint8_t pushes = 0;//zmienna sprawzaj¹ca ile czasu trwa juz wcisniecie przycisku



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
}

void TIM2_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim2);
}

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim3);
}

void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&tim4);
}

//procedura obs³ugi przerwañ od timerów
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){


	//push = 0;

	if(htim->Instance == TIM2){
		//tutaj bedzie implementacja funkcji wywo³ywanej co przerwanie timera TIM2 czyli co 1s zwieksza liczbe sekund o 1

		sec++;

		if(mode == RUNNING_MODE){

			if((alarmIsSet==1 )){
				if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==GPIO_PIN_RESET){
					alarmIsSet = 0;
				}
				else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==GPIO_PIN_SET){
					alarmIsSet =  1;
				}

			}
			else if(alarmIsSet == 0) {

				if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==GPIO_PIN_RESET){
				alarmIsSet = 1;
				}
				else if( HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==GPIO_PIN_SET){
					alarmIsSet = 0;
				}
			}

			checkIfCorrectValuesOfDate();

			hourToDisplay();
			dateToDisplay();
			alarmTimeToDisplay();
			lcd_clear();

			lcd_draw_text(1,1,"ACTUAL TIME");
			lcd_draw_text(2,1,outHour);
			lcd_draw_text(3,1,outDate);
			lcd_draw_text(4,1,alarmTime);

			lcd_copy();

		}


		if(alarmIsSet == 1 &&hour == hourOfAlarm &&min == minOfAlarm && sec == secOfAlarm){

			//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET);
			alarmTriggered = 1;
		}

		if(alarmTriggered == 1 && HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) ==GPIO_PIN_RESET ){

			alarmTriggered = 0;
			//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
		}



	}

	//refactor po testach!!!
	else if(htim->Instance == TIM3){


		 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5) == GPIO_PIN_RESET){

			switch(mode){
			case SETTING_ALARM_MODE:
				hourOfAlarm++;
				checkIfCorrectValuesAfterSetting();
				hourToDisplay();
				dateToDisplay();
				alarmTimeToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE ALARM");
				lcd_draw_text(3,1,alarmTime);
				lcd_copy();
				break;
			case SETTING_HOUR_MODE:
				hour++;
				checkIfCorrectValuesAfterSetting();
				hourToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE TIME");
				lcd_draw_text(3,1,outHour);
				lcd_copy();
				break;
			case SETTING_DATE_MODE:
				day++;
				checkIfCorrectValuesAfterSetting();
				dateToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE DATE");
				lcd_draw_text(3,1,outDate);
				lcd_copy();
				break;
			default:
				break;
			}
		}
		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6) == GPIO_PIN_RESET){

			switch(mode){
			case SETTING_ALARM_MODE:
				minOfAlarm++;
				checkIfCorrectValuesAfterSetting();
				hourToDisplay();
				dateToDisplay();
				alarmTimeToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE ALARM");
				lcd_draw_text(3,1,alarmTime);
				lcd_copy();
				break;
			case SETTING_HOUR_MODE:
				min++;
				checkIfCorrectValuesAfterSetting();
				hourToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE TIME");
				lcd_draw_text(3,1,outHour);
				lcd_copy();
				break;
			case SETTING_DATE_MODE:
				month++;
				checkIfCorrectValuesAfterSetting();
				dateToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE DATE");
				lcd_draw_text(3,1,outDate);
				lcd_copy();
				break;
			default:
				break;
			}
		}

		else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8) == GPIO_PIN_RESET){

			switch(mode){
			case SETTING_ALARM_MODE:
				secOfAlarm++;
				checkIfCorrectValuesAfterSetting();
				hourToDisplay();
				dateToDisplay();
				alarmTimeToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE ALARM");
				lcd_draw_text(3,1,alarmTime);
				lcd_copy();
				break;
			case SETTING_HOUR_MODE:
				sec++;
				checkIfCorrectValuesAfterSetting();
				hourToDisplay();
				dateToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE TIME");
				lcd_draw_text(3,1,outHour);
				lcd_copy();
				break;
			case SETTING_DATE_MODE:
				year++;
				checkIfCorrectValuesAfterSetting();
				hourToDisplay();
				dateToDisplay();
				lcd_clear();
				lcd_draw_text(1,1,"SET THE DATE");
				lcd_draw_text(3,1,outDate);
				lcd_copy();
				break;
			default:
				break;
			}
		}


	}
	else if(htim->Instance == TIM4){
		//sprawdzenie wcisniêcia konkretnego przycisku co 200ms w trakcie przerwania od TIM4
		//i nastawa odpowiednich wartoœci przy odpowiednim naciœniêtym przycisku
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9) == GPIO_PIN_RESET){
			//prze³aczanie trybów za pomoca 4. przycisku PC8
			pushes++;
			if(pushes == 20){
				//przytrzymanie przycisku
				//jesli wcisniecie przycisku 4. trwa juz20*40ms= 800ms to zmien odpowiednio tryb

				switch(mode){
				case RUNNING_MODE:
					mode = SETTING_ALARM_MODE;
					hourToDisplay();
					dateToDisplay();
					alarmTimeToDisplay();
					lcd_clear();
					lcd_draw_text(1,1,"SET THE ALARM");
					lcd_draw_text(3,1,alarmTime);
					lcd_copy();
					break;
				case SETTING_ALARM_MODE:
					mode = SETTING_HOUR_MODE;
					hourToDisplay();
					dateToDisplay();
					lcd_clear();
					lcd_draw_text(1,1,"SET THE TIME");
					lcd_draw_text(3,1,outHour);
					lcd_copy();
					break;
				case SETTING_HOUR_MODE:
					mode = SETTING_DATE_MODE;
					hourToDisplay();
					dateToDisplay();
					lcd_clear();
					lcd_draw_text(1,1,"SET THE DATE");
					lcd_draw_text(3,1,outDate);
					lcd_copy();
					break;
				case SETTING_DATE_MODE:
					mode = RUNNING_MODE;
					hourToDisplay();
					dateToDisplay();
					alarmTimeToDisplay();
					lcd_clear();

					lcd_draw_text(1,1,"ACTUAL TIME");
					lcd_draw_text(2,1,outHour);
					lcd_draw_text(3,1,outDate);
					lcd_draw_text(4,1,alarmTime);

					lcd_copy();
					break;
				default:
					break;
				}
				pushes = 0;
				beepAfterChanging = 1;

			}

			if((pushes<20) && HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_9) == GPIO_PIN_SET){
				//krotkie wcisniecie powoduje natychmiastowy powrot do trybu wyswietlania godziny
				mode = RUNNING_MODE;
				pushes = 0;
			}

		}
		//wyzwolenie dzwieku oznaczaj¹cego zmiane trybu
		//sprawdzenie aby nie bylo kolizji z sygnalem generowanym w momencie alarmu
		if(beepAfterChanging ==1 && counterOfBeep <=10 &&alarmTriggered == 0){
			//tuz po zmianie trybu sygnalizacja dzwiekowa zminionego trybu na 10*20ms = 200ms
			counterOfBeep++;
			//jakby coc to tu zakomentowac
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_SET);
		}
		if(counterOfBeep == 10 && beepAfterChanging == 1&& alarmTriggered == 0){
			beepAfterChanging = 0;
			counterOfBeep = 0;
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
		}


		//wyzwolenie alarmu jako pikanie
		//sparawdzanie aby nie bylo kolizji z sygnalem wyzwalanym w momencie zmiany trybu
		if(alarmTriggered == 1 && directionOfBeeps == 0 &&beepAfterChanging ==0 ){
			if(beepsOfAlarm %2 == 0){//zeby zbyt szybko nie pika³ to pikniecie ustawione na co drugie wystapienie przerwania od timera
				HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_10);
			}
			beepsOfAlarm++;
			if(beepsOfAlarm == 16){
				directionOfBeeps = 1;//cisza
				//0->pikanie
			}
		}
		//
		//odpowiednia flaga kierunku(czy wystepuja pipipipi czy jest ------->pauza)dla sygna³u z alarmu
		if(directionOfBeeps == 1 && alarmTriggered == 1 &&beepAfterChanging == 0){
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
			beepsOfAlarm--;
			if(beepsOfAlarm == 0){
				directionOfBeeps = 0; //->pikanie
			}
		}
		if(alarmTriggered == 0 &&beepAfterChanging ==0){
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);
			directionOfBeeps = 0;
		}
	}

}

int main(void) {


	SystemCoreClock = 8000000; // taktowanie 8Mhz

	HAL_Init();

	//inicjalizacja zegarów dla poszczególnych modu³ów
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_SPI1_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();


	//inicjalizacja pinów i interface'u SPI dla wyswietlacza lcd
	lcdInit();

	lcd_setup();

	//w³aczenie timera 2 z przerwaniem co 1s
	tim2Init();

	//wlaczenie timera 3 z przerwaniem co 200ms
	tim3Init();

	//wlaczenie timera 4 z przerwaniem co 40ms
	tim4Init();


	buttonsInit();

	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_10,GPIO_PIN_RESET);//buzzer wy³aczony

	while (1)
	{
		//
	}
}


