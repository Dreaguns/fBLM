#include <stdio.h>
#include "dec2hex.c"
#include "fullScale.c"
#include <string.h>



const int userInput = 250;
char * hex; //Initializing

int main(void){
        
printf("Hello World!\n\n");

        int decimal = getSpreaded16Bit(userInput);
        printf("A 16 bit decimal: %d\n", userInput);


        char data[3] = {0x19, 0x00, 0x00};
        printf("Data[0]: %x\n", data[0]);
        printf("Data[1]: %x\n", data[1]);
        printf("Data[2]: %x\n", data[2]);

        printf("decimal in hex: %x\n", decimal);


        int word1 = decimal >> 8; //change this later
        int word2 = decimal - word1;
        printf("word1 in hex: %x\n", word1);
        printf("word2 in hex: %x\n", word2);

        data[1] = word1;
        data[2] = word2;

        printf("Data[0]: %x\n", data[0]);
        printf("Data[1]: %x\n", data[1]);
        printf("Data[2]: %x\n", data[2]);


//      char word1 = decimal << 4;
//      printf("word1: %x\n", word1);

return 0;
}
