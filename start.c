/*
 * start.c
 *
 *  Created on: Nov 29, 2019
 *      Author: jrenta
 */

#include <stdio.h>
#include "dec2hex.h"
#include "get16BITdecimal.h"


const int userInput = 1250;
int hex = 0; //Initializing

int main(void){
	printf("Hello World!\n\n");

	int decimal = get16BITdecimal(userInput);
	printf("A 16 bit decimal: %d\n", decimal);
	hex = dec2hex(decimal);


	return 0;
}


