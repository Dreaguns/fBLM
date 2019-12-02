/*
 * FILENAME: dac_handler.c
 *
 * DESCRIPTION:
 *      This program sends DAC values to rp_spi.c
 *      rp_spi.c talks via spi to the RedPitaya
 *
 * AUTHOR: Julio Renta <jrenta@bnl.gov>
 *
 * NOTES:
 *      For more information about the RedPitaya's DAC,
 *      visit   : https://redpitaya.readthedocs.io/en/latest/developerGuide/125-14/fastIO.html
 *      section : 3.1.3.1.2 Analog output
 *
 * CREATED DATE:  20 November 2019
 *
 *
 * CHANGES:
 * VERSION | AUTHOR |  DATE  | DETAIL
 * 1.0        JCR     19NOV19  Init
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "rp_spi.c"
#include <string.h>
#include <math.h>

/* Function Declaration*/
void dacConverter(int);

int main(){
        system("clear");
        printf("*************************************************\n");
        printf("Enter a High Voltage value for Hamamatsu C12597-01: 0 to -1250 volts\n");

        int userInput = 0;
        char term;
        printf("User input: ");
        scanf("%d%c", &userInput, &term); //Looks for an integer only and the return
//      printf("\nUser input: %d\n", abs(userInput) );
//      userInput = abs(userInput);
        printf("\n");

        if(userInput < 0 || userInput > 1250)
                printf("Your input has exceeded the limits\n");
        else if(term != '\n')
                printf("Invalid Entry\n");
        else
                printf("Ramping High Voltage to : -%d Volts\n", userInput);

        printf("*************************************************\n\n");

//      int rp_spi_STATUS = startDAC(str);
        int rp_spi_STATUS = startDAC();


//      printf("rp_spi_STATUS: %d\n", rp_spi_STATUS);

return 0;
}
