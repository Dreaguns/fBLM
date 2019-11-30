/*
 * get16BITdecimal.h
 *
 * This function takes a value from 0 to 1250
 * Spreads out this value into a 16 bit decimal number
 * 0 = 0 and 1250 = 65,535
 *
 *  Created on: Nov 29, 2019
 *      Author: jrenta
 *
 */
#include <stdio.h>
#include <math.h>
#include "powThis.h"

int get16BITdecimal(int userVoltage);
const int numBits = 16;
const int maxVoltage = 1250;
long decimal;
float resolution;
long range;
long spread;



int get16BITdecimal(int userVoltage){
	if(userVoltage != 0){
		long p = (long)powThis(2, numBits);
		resolution =  (float)maxVoltage / (float)p;
		decimal = (userVoltage/resolution) - 1;
	}
	else decimal = 0;
return decimal;
}
