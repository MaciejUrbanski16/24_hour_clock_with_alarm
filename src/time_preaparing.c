/*
 * time_preaparing.c
 *
 *  Created on: 14.12.2020
 *      Author: Admin
 */
#include "time_preaparing.h"


void alarmTimeToDisplay(){
	if(alarmIsSet == 0 && mode == RUNNING_MODE){
		alarmTime[0] = '-';
		alarmTime[1] = '-';
		alarmTime[2] = ':';
		alarmTime[3] = '-';
		alarmTime[4] = '-';
		alarmTime[5] = ':';
		alarmTime[6] = '-';
		alarmTime[7] = '-';
		//alarmTime[8] = '-';
	}
	else if(alarmIsSet == 1 && mode == RUNNING_MODE){
		//zamiana pszczegolnych wartoœci godziny w ci¹g znakow w formacie hh:mm:ss
		uint8_t jednH = hourOfAlarm%10;
		uint8_t dzH = (hourOfAlarm -jednH)/10;

		uint8_t jednMin = minOfAlarm%10;
		uint8_t dzMin = (minOfAlarm -jednMin)/10;

		uint8_t jednSek = secOfAlarm%10;
		uint8_t dzSek = (secOfAlarm -jednSek)/10;

	    alarmTime[0] = (dzH%10) +48;
	    alarmTime[1] = (jednH%10) +48;
	    alarmTime[2] = ':';
	    alarmTime[3] =  (dzMin%10) + 48;
	    alarmTime[4] = (jednMin%10) +48;
	    alarmTime[5] = ':';
	    alarmTime[6] = (dzSek%10)+48;
	    alarmTime[7] = (jednSek%10) + 48;
	}
	else if(mode == SETTING_ALARM_MODE){
		uint8_t jednH = hourOfAlarm%10;
		uint8_t dzH = (hourOfAlarm -jednH)/10;

		uint8_t jednMin = minOfAlarm%10;
		uint8_t dzMin = (minOfAlarm -jednMin)/10;

		uint8_t jednSek = secOfAlarm%10;
		uint8_t dzSek = (secOfAlarm -jednSek)/10;

	    alarmTime[0] = (dzH%10) +48;
	    alarmTime[1] = (jednH%10) +48;
	    alarmTime[2] = ':';
	    alarmTime[3] =  (dzMin%10) + 48;
	    alarmTime[4] = (jednMin%10) +48;
	    alarmTime[5] = ':';
	    alarmTime[6] = (dzSek%10)+48;
	    alarmTime[7] = (jednSek%10) + 48;
	}

}



//sprawdza poprawnosc aktualnej godziny i daty oraz modyfikuje odpowiednie wartoœci adekwatnie do obecnego czaasu
void checkIfCorrectValuesOfDate(){
	if(sec>=60){
		sec = 0;
		min++;
	}
	if(min>=60){
		min = 0;
		hour++;
	}
	if(hour >= 24){
		hour = 0;
		day++;
	}
	if(month == 2){
		if(year%4 == 0 && day == 30){
			month++;
			day = 1;
		}
		else if(year%4 !=0 && day == 29){
			month++;
			day = 1;
		}
	}
	else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10){
		if(day >= 32){
			month++;
			day= 1;
		}
	}
	else if(month == 4 || month == 6 || month == 9 || month == 11){
		if(day >= 31){
			month++;
			day = 1;
		}
	}
	else if(month >= 12){
		if(day >= 32){
			day = 1;
			month = 1;
			year++;
		}
	}
	if(year >= 100){
		year = 0;
	}

}
void checkIfCorrectValuesAfterSetting(){

	//sprawdzenie cxzy w czasie ustawiania godziny i daty przez uzytkownika
	//nie zosta³y przekroczone zakresy poszczególnych danych

	if(sec >= 60)sec = 0;
	if(min >= 60)min = 0;
	if(hour >= 24)hour = 0;
	if(month >= 13) month = 0;
	if(month == 2 && year%4 == 0 && day == 30) day = 0;
	if(month == 2 && year%4 != 0 && day == 29) day = 0;
	if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day == 32)
		day = 0;
	if((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
		day = 0;
	if(year >= 100) year = 0;
	if(secOfAlarm >=60) secOfAlarm = 0;
	if(minOfAlarm >= 60) minOfAlarm = 0;
	if(hourOfAlarm >=24) hourOfAlarm = 0;
}

void dateToDisplay()
{
	//zamiana poszczególnych wartoœci daty na ci¹g znaków w formacie dd.mm.rr
    uint8_t jednD = day%10;
    uint8_t dzD = (day-jednD)/10;

    uint8_t jednM = month %10;
    uint8_t dzM = (month - jednM)/10;

    uint8_t jednY = year %10;
    uint8_t dzY = (year - jednY)/10;

    outDate[0] = (dzD%10) +48;
    outDate[1] = (jednD%10) + 48;
    outDate[2] = '.';
    outDate[3] = (dzM%10)+48;
    outDate[4] = (jednM%10) + 48;
    outDate[5] = '.';
    outDate[6] = (dzY%10)+48;
    outDate[7] = (jednY%10) +48;
}

void hourToDisplay(){

	//zamiana pszczegolnych wartoœci godziny w ci¹g znakow w formacie hh:mm:ss
	uint8_t jednH = hour%10;
	uint8_t dzH = (hour -jednH)/10;

	uint8_t jednMin = min%10;
	uint8_t dzMin = (min -jednMin)/10;

	uint8_t jednSek = sec%10;
	uint8_t dzSek = (sec -jednSek)/10;

    outHour[0] = (dzH%10) +48;
    outHour[1] = (jednH%10) +48;
    outHour[2] = ':';
    outHour[3] =  (dzMin%10) + 48;
    outHour[4] = (jednMin%10) +48;
    outHour[5] = ':';
    outHour[6] = (dzSek%10)+48;
    outHour[7] = (jednSek%10) + 48;
}
