/* Copyright(C) Shubhra Rajadhyaksha, Salil Rajadhyaksha.
 * Copying, re-distributing or sharing without permission of the authors
 * is strictly prohibited.
 * 
 * Author: Salil Rajadhyaksha
 * Date: June 4, 2016
 */

/*
 * INCLUDES
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>

//#include "ss_gpio.h"

/*
 * DEFINITIONS
 */
int ss_gpio_cfg(uint8_t mode, uint8_t pin, uint8_t value);
//int ss_gpio_on(uint8_t pin);
//int ss_gpio_off(uint8_t pin);


int gpio_fd;
volatile unsigned *gpio;

/*
 * MAIN
 */
int main(int argc, char** argv) {
	
	printf("Bebu's iot proj...\n");
	
	ss_gpio_cfg(0,29,1/*mode, pin, default value */);
	
	//ss_gpio_on(/*pin*/);
/*	char buf[255];
	sprintf(buf, "/sys/class/gpio/gpio40/value");
	int fd = open(buf, O_RDWR);
	if (fd < 0) {
		printf("Error! %d\n", fd);
	}
	else {
		printf("fd = %d\n", fd);
		int val;
		read(fd, &val, 29);
		printf("Val = %d\n", val);
		write(fd, "1", 29);
	}*/
	
	//ss_gpio_off(/*pin*/);
	
	return 0;
}


/*
 * FUNCTIONS
 */
 
/**@Brief - Configures gpio 'mode' specified by 'pin'. Sets it to
 * 'value'
 * 
 **@Returns - error code, 0 if no errors
 */
int ss_gpio_cfg(uint8_t mode, uint8_t pin, uint8_t value) {
	
	int status = 0; //no error yet
	int fd;
	char buf[255];
	
	fd = open("/sys/class/gpio/export", O_RDWR);
	
	if (fd < 0)
	    printf("Error! %d", fd);
	else {
		printf("fd %d\n", fd);
		
	    sprintf(buf, "%d", pin);
	
	    write(fd, buf, strlen(buf));
	
        close(fd);
        
	    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
	
	    fd = open(buf, O_RDWR);
	    if (fd < 0)
	        printf("Error! %d\n", fd);
	        
	    else {
			
			write(fd, "out", pin);
			
			close(fd);
		}
	    
	    close(fd);    
	}
	
	return status;
}
