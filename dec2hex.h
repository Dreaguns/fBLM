/*
 * FILENAME: dec2hex.c
 *
 * DESCRIPTION:
 *      This program converts decimal to hexadecimal
 *
 * AUTHOR: Julio Renta <jrenta@bnl.gov>
 *
 * CREATED DATE:  30 November 2019
 *
 *
 * CHANGES:
 * VERSION | AUTHOR |  DATE  | DETAIL
 * 1.0        JCR     30NOV19  Init
 *
 */

#pragma once

#include <stdio.h>
#include <math.h>

char * gethex(int input);

long quotient, r;
int i = 0;
int j = 0;
char hexadecimal[4] = {'0', '0', '0', '0'};


char * gethex(int input){
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

        char * str = (char *) malloc(sizeof(char) * 5);
        str[0] = hexadecimal[0];
        str[1] = hexadecimal[1];
        str[2] = hexadecimal[2];
        str[3] = hexadecimal[3];
        str[4] = '\0';

return str;
}
