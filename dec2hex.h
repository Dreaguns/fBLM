/*
 * dec2hex.c
 *
 *  Created on: Nov 29, 2019
 *      Author: jrenta
 */
#include <stdio.h>
#include <math.h>

int dec2hex(int input);

long quotient, r;
int i = 0;
int j = 0;
char hexadecimal[4] = {'0', '0', '0', '0'};


int dec2hex(int input){
	quotient = input;

	if(quotient == 0)
		hexadecimal[0] = 48;


	while (quotient != 0){
		r = quotient % 16;
		if (r < 10)
			hexadecimal[j++] = 48 + r;
		else
			hexadecimal[j++] = 55 + r;

		quotient = quotient / 16;
	}

	printf("Distributed into a 16 Bit Hexadecimal: 0x");
	for(int i = 3; i >= 0; i--)
		printf("%c", hexadecimal[i]);
	printf("\n");

return 0;
}




