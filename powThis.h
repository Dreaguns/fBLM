/*
 * powThis.h
 *
 *  Created on: Nov 29, 2019
 *      Author: jrenta
 */

#include <stdio.h>

int powThis(int base, int exponent);

int powThis(int base, int exponent){
	int result=1;
	for(exponent; exponent>0; exponent--) // @suppress("Statement has no effect")
		result = result * base;

return result;
}
