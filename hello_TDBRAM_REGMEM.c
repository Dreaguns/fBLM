/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "trueDualBRAM.h"

//#define XPAR_TRUEDUALBRAM_0_S00_AXI_BASEADDR 0x43C20000
//#define XPAR_TRUEDUALBRAM_0_S00_AXI_HIGHADDR 0x43C2FFFF
//#define XPAR_TRUEDUALBRAM_1_S00_AXI_BASEADDR 0x43C30000
//#define XPAR_TRUEDUALBRAM_1_S00_AXI_HIGHADDR 0x43C3FFFF

//#define XPAR_REGMEM_0_S00_AXI_BASEADDR 0x43C00000
//#define XPAR_REGMEM_0_S00_AXI_HIGHADDR 0x43C0FFFF
//#define XPAR_REGMEM_1_S00_AXI_BASEADDR 0x43C10000
//#define XPAR_REGMEM_1_S00_AXI_HIGHADDR 0x43C1FFFF



int ramLength = 4096;
int offset = 4; //4 for TDBRAM
long unsigned int mask = 0x1FFF; //Masking to BLANK the binary offset bit # 14 on the Redpitaya's ADC 14bit range
long unsigned int result;

int main()
{
    init_platform();

    /*print("\nReading BRAMs Test...\n");
    //printf("Reading from BRAM_0: %x: %x\n",XPAR_TRUEDUALBRAM_0_S00_AXI_BASEADDR, Xil_In32(XPAR_TRUEDUALBRAM_0_S00_AXI_BASEADDR) );
    //printf("Reading from BRAM_1: %x: %x",XPAR_TRUEDUALBRAM_1_S00_AXI_BASEADDR, Xil_In32(XPAR_TRUEDUALBRAM_1_S00_AXI_BASEADDR) );

    for(int i = 0; i < ramLength; i++){
    	result = Xil_In32 (XPAR_TRUEDUALBRAM_0_S00_AXI_BASEADDR + (i*offset));
    	result = result & mask; //Keeping the lower 13 bits of ADC's 14 bit data, zeroing the 14th bit = the binary offset bit
    	printf("Reading from BRAM_0 Address: %x: %x, from ram element(%d)\n",XPAR_TRUEDUALBRAM_0_S00_AXI_BASEADDR + (i*offset), result, i );
    }
    */

    int numRegisters = 4; //hvsp, limit trig_n and reset_out

    print("\nReading from REGMEM...\n");
    for(int i = 0; i < numRegisters; i++){
        	result = Xil_In32 (XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset));
        	switch(i){
        		case 0:
        			printf("Reading from REGMEM Address: %x: %x, from HVSP register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
        			break;
        		case 1:
        			printf("Reading from REGMEM Address: %x: %x, from LIMIT register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
        			break;
        		case 2:
        			printf("Reading from REGMEM Address: %x: %x, from TRIG RESET register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
        			break;
        		case 3:
        			printf("Reading from REGMEM Address: %x: %x, from RESET OUT register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
        			break;
        	}
    }



    long unsigned int hvsp = 6;
    long unsigned int limit = 0b001000;
    long unsigned int trig_reset = 0;
    long unsigned int out_reset = 1;

    print("\nWriting to  REGMEM...\n");
    //Xil_Out32(UINTPTR Addr, u32 Value)
    for(int i = 0; i < numRegisters; i++){
    	switch(i){
			case 0:
				Xil_Out32 (XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), hvsp);
				printf("Writing %d to REGMEM Address: %x, in register number: (%d)\n",hvsp, XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), i );
				break;
			case 1:
				Xil_Out32 (XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), limit);
				printf("Writing %d to REGMEM Address: %x, in register number: (%d)\n",limit, XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), i );
				break;
			case 2:
				Xil_Out32 (XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), trig_reset);
				printf("Writing %d to REGMEM Address: %x, in register number: (%d)\n",trig_reset, XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), i );
				break;
			case 3:
				Xil_Out32 (XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), out_reset);
				printf("Writing %d to REGMEM Address: %x, in register number: (%d)\n",out_reset, XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), i );
				break;
    	 }
			//Xil_Out32 (XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), 1);
			//printf("Writing %d to REGMEM Address: %x, in register number: (%d)\n",i, XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), i );
        }

    print("\nReading from REGMEM after writing...\n");
    for(int i = 0; i < numRegisters; i++){
            	result = Xil_In32 (XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset));
            	switch(i){
					case 0:
						printf("Reading from REGMEM Address: %x: %x, from HVSP register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
						break;
					case 1:
						printf("Reading from REGMEM Address: %x: %x, from LIMIT register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
						break;
					case 2:
						printf("Reading from REGMEM Address: %x: %x, from TRIG RESET register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
						break;
					case 3:
						printf("Reading from REGMEM Address: %x: %x, from RESET OUT register.\n",XPAR_REGMEM_0_S00_AXI_BASEADDR + (i*offset), result );
						break;
            	 }
        }

    cleanup_platform();
    return 0;
}
