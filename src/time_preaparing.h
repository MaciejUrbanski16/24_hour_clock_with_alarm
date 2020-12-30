/*
 * time_preapring.h
 *
 *  Created on: 14.12.2020
 *      Author: Admin
 */
#pragma once
#ifndef __TIME_PREAPARING_H_
#define __TIME_PREAPARING_H_

#include "stm32f1xx.h"
//#include "alarm.h"

//zmienne do przechowywania i aktualizowania godziny i daty


//kontenery do przechowania godziny i daty i godziny alarmu do wyswietlenia
char outHour[9];
char outDate[9];
char alarmTime[9];

//wyszczególenienie trybow pracy zegara
enum{
	RUNNING_MODE,
	SETTING_HOUR_MODE,
	SETTING_DATE_MODE,
	SETTING_ALARM_MODE
};

//aktualny tryb pracy zegara
/*extern volatile uint8_t mode;// = RUNNING_MODE;

//zmienne do sygnalizacji dzwiekowej tuz po zmianie trybu
extern volatile uint8_t beepAfterChanging;// = 0;
extern volatile uint8_t counterOfBeep;// = 0;


extern volatile uint8_t hourOfAlarm;// = 5;
extern volatile uint8_t minOfAlarm;// = 30;
extern volatile uint8_t secOfAlarm;// = 0;



//flaga sprawdzajaca czy alarm jest aktualnie ustawiony
extern volatile uint8_t alarmIsSet;// = 0;
extern volatile uint16_t automaticSilenceOfAlarm;// = 0;
extern volatile uint8_t alarmTriggered;// =0;
extern volatile uint8_t alarmIsSetToShow;// =0;

//flagi do wyzwolenia pikania w alarmie
extern volatile uint16_t beepsOfAlarm;// = 0;
extern volatile uint8_t directionOfBeeps;// = 0;*/

volatile uint8_t hour = 23;
volatile uint8_t min = 59;
volatile uint8_t sec = 57;
volatile uint8_t day = 31;
volatile uint8_t month = 7;
volatile uint8_t year = 20;

volatile uint8_t hourOfAlarm = 5;
volatile uint8_t minOfAlarm = 30;
volatile uint8_t secOfAlarm = 0;



 //volatile uint8_t hourOfAlarm = 5;
// volatile uint8_t minOfAlarm = 30;
// volatile uint8_t secOfAlarm = 0;

 //aktualny tryb pracy zegara
 volatile uint8_t mode = RUNNING_MODE;

 //zmienne do sygnalizacji dzwiekowej tuz po zmianie trybu
volatile uint8_t beepAfterChanging = 0;
volatile uint8_t counterOfBeep = 0;


 //flaga sprawdzajaca czy alarm jest aktualnie ustawiony
 volatile uint8_t alarmIsSet= 0;
 volatile uint16_t automaticSilenceOfAlarm = 0;
 volatile uint8_t alarmTriggered =0;
 volatile uint8_t alarmIsSetToShow=0;

 //flagi do wyzwolenia pikania w alarmie
 volatile uint16_t beepsOfAlarm= 0;
 volatile uint8_t directionOfBeeps = 0;


void alarmTimeToDisplay();


void checkIfCorrectValuesOfDate();

void checkIfCorrectValuesAfterSetting();

void dateToDisplay();

void hourToDisplay();


#endif /* TIME_PREAPARING_H_ */
