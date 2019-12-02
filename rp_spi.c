/* AUTHOR:  Luka Golinar <luka.golinar@redpitaya.com>
 * VERSION: 1.0
 *
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * DESCRIPTION:
 *      This part of code is written in C programming language.
 *      Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 *      for more details on the language used herein.
 *
 * CHANGES:
 * Version| Author |  DATE  | NOTES
 * 1.1       JCR    20NOV19  Changed data & added tons of feedback statements
 *                           MODES: https://liftoff.github.io/cupi_shift/spidev/constant.SPI_CPHA.html
 *                           Added Various Data Commands
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <linux/spi/spidev.h>
#include <linux/types.h>

/* Inline functions definition */
static int init_spi();
static int release_spi();
//static int read_flash_id(int fd);
static int write_spi(char *write_data, int size);
void convertDACInt2ArryHex(int value, int channel);
void startDAC(int value, int dacChannel);


int bufferSize = 3;
char data[3]; // = {0x19, 0x9f, 0xff}; //0001 1001 XXXXXXXXXXXXXXXX




/* Constants definition */
int spi_fd = -1;

//int main(){
//int  startDAC(char *myData){
void startDAC(int value, int dacChannel){
        convertDACInt2ArryHex(value, dacChannel);
//      char *data = myData;
//      printf("Welcome to rp_spi, attempting to communicate with SPI protocol...\n\n");

        /* Sample data */
//      char *data = "REDPITAYA SPI TEST";
//      printf("The data sent via SPI is: %s\n", data);


        /* Init the spi resources */
        if(init_spi() < 0){
                printf("Initialization of SPI failed. Error: %s\n", strerror(errno));
//              return -1;
        }
//      else
//              printf("init_spi()... Success!\n");

        /* Write some sample data */
        if(write_spi(data ,bufferSize) < 0){
                printf("Write to SPI failed. Error: %s\n", strerror(errno));
//              return -1;
        }
//      else
//              printf("write_spi(*char, strlen(data))... Success!\n");

        /* Read flash ID and some sample loopback data */
/*      if(read_flash_id(spi_fd) < 0){
                printf("Error reading from SPI bus : %s\n", strerror(errno));
                return -1;
        }
        else
                printf("read_flash_id(int)... Success!\n");
*/
        /* Release resources */
        if(release_spi() < 0){
                printf("Release of SPI resources failed, Error: %s\n", strerror(errno));
//              return -1;
        }
//      else
//              printf("release_spi()... Success!\n");
//              printf("All functions within rp_spi.c have been reached\n");

}

static int init_spi(){

        /* MODES: mode |= SPI_LOOP;
         *        mode |= SPI_CPHA;
         *        mode |= SPI_CPOL;
         *                mode |= SPI_LSB_FIRST;
         *        mode |= SPI_CS_HIGH;
         *        mode |= SPI_3WIRE;
         *        mode |= SPI_NO_CS;
         *        mode |= SPI_READY;
         *
         * multiple possibilities possible using | */

        int mode = 0;

        /* Opening file stream */
        spi_fd = open("/dev/spidev1.0", O_RDWR | O_NOCTTY);
        if(spi_fd < 0){
                printf("Error opening spidev0.1. Error: %s\n", strerror(errno));
                return -1;
        }
//      else
//               printf("Opening /dev/spidev1.0 ... Success!\n");



//      mode |= SPI_CPHA;       //uncomment to change the phase of Clock with respect to MOSI
      mode |= SPI_CPOL;
        /* Setting mode (CPHA, CPOL) */
        if(ioctl(spi_fd, SPI_IOC_WR_MODE, &mode) < 0){
                printf("Error setting SPI MODE. Error: %s\n", strerror(errno));
                return -1;
        }
//      else{
//              printf("CPHA Mode: %d\n", SPI_CPHA);
//              printf("Setting SPI MODE... Success!\n");
//      }


        /* Setting SPI bus speed */
        int spi_speed = 10000; //Default: 1000000;
        
 
        if(ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed) < 0){
                printf("Error setting SPI MAX_SPEED_HZ. Error: %s\n", strerror(errno));
                return -1;
        }

        return 0;
}

static int release_spi(){

        /* Release the spi resources */
        close(spi_fd);

        return 0;
}

/* Read data from the SPI bus */
static int read_flash_id(int fd){

        int size = 2;

        /*struct spi_ioc_transfer {
          __u64           tx_buf;
          __u64           rx_buf;

          __u32           len;
          __u32           speed_hz;

          __u16           delay_usecs;
          __u8            bits_per_word;
          __u8            cs_change;
          __u32           pad;
    }*/
    /* If the contents of 'struct spi_ioc_transfer' ever change
         * incompatibly, then the ioctl number (currently 0) must change;
         * ioctls with constant size fields get a bit more in the way of
         * error checking than ones (like this) where that field varies.
         *
         * NOTE: struct layout is the same in 64bit and 32bit userspace.*/
        struct spi_ioc_transfer xfer[size];

    unsigned char           buf0[1];
    unsigned char           buf1[3];
        int                     status;

        memset(xfer, 0, sizeof xfer);

        /* RDID command */
        buf0[0] = 0x9f;
        /* Some sample data */
        buf1[0] = 0x01;
        buf1[1] = 0x23;
        buf1[2] = 0x45;

        /* RDID buffer */
        xfer[0].tx_buf = (__u64)((__u32)buf0);
        xfer[0].rx_buf = (__u64)((__u32)buf0);
        xfer[0].len = 1;

        /* Sample loopback buffer */
        xfer[1].tx_buf = (__u64)((__u32)buf1);
        xfer[1].rx_buf = (__u64)((__u32)buf1);
        xfer[1].len = 3;

        /* ioctl function arguments
         * arg[0] - file descriptor
  * arg[1] - message number
         * arg[2] - spi_ioc_transfer structure
         */
        status = ioctl(fd, SPI_IOC_MESSAGE(2), xfer);
        if (status < 0) {
                perror("SPI_IOC_MESSAGE");
                return -1;
        }

        printf("Reading back from buffer...\n");
        /* Print read buffer */
        for(int i = 0; i < 3; i++){
                printf(" Buffer: %d\n", buf1[i]);
        }

        return 0;
}

/* Write data to the SPI bus */
static int write_spi(char *write_buffer, int size){
//      printf("**************************************\n");
//      printf("Write Buffer: %s\n", write_buffer);
//      printf("**************************************\n");
//      printf("Write Buffer Address: %p\n", &write_buffer);
//      printf("**************************************\n");

//      int write_spi = write(spi_fd, write_buffer, size);
        int write_spi = write(spi_fd, write_buffer, size);

        if(write_spi < 0){
                printf("Failed to write to SPI. Error: %s\n", strerror(errno));
                return -1;
        }
//      else
//              printf("write_spi feedback: %d\n", write_spi);

        return 0;
}

void convertDACInt2ArryHex(int value, int channel){
        if(value == 0){
                if(channel == 1){
                        data[0] = 0x11; //0001 1001 XXXXXXXXXXXXXXXX
                        data[1] = 0x00;
                        data[2] = 0x00;
                }
                else if(channel == 2){
                        data[0] = 0x18;
                        data[1] = 0x00;
                        data[2] = 0x00;
                }
        }
        else{
                if(channel == 1){
                        data[0] = 0x11; //0001 1001 XXXXXXXXXXXXXXXX
                        data[1] = 0x00; //data[1] = 0x9f;
                        data[2] = 0x00; //data[2] = 0xff;
                }
                else if(channel == 2){
                        data[0] = 0x18;
                        data[1] = 0x9f;
                        data[2] = 0xff;
                }
        }
}
