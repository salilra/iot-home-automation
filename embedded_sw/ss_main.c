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
#include <errno.h>
#include "ss_gpio.h"

/*
 * DEFINITIONS
 */
#define SS_ENABLE_DEBUG_LOGS    (0)
#if SS_ENABLE_DEBUG_LOGS
#define SS_LOG_LEVEL_APP        (1)
#endif // SS_ENABLE_DEBUG_LOGS

#define OUT (1)
#define IN (0)
#define HIGH OUT
#define LOW IN

//TODO: Define custom print

/*
 * MAIN
 */
//run numoffixtures, fix1 fix 2 fix3....fixn
int main(int argc, char** argv) {
	int status = 0; //TODO-define
	
	if (argc != 3) { //TODO-define
		fprintf(stderr, "Error! Invalid number of args\n");
		status = -1; //TODO-define
		goto SS_EXIT_FINAL;
	}
	
	if (argv == NULL) {
		fprintf(stderr, "Error! Arguments not supplied\n");
		status = -2;
        goto SS_EXIT_FINAL;
	}

	fprintf(stdout, "SS Labs IoT ...\n");

#if 1//SS_ENABLE_DEBUG_LOGS	
	ss_dump_pinout();
#endif
	
	ss_gpio_cfg(OUT, SS_RELAY_REGULAR_LAMP);

	ss_gpio_write(SS_RELAY_REGULAR_LAMP, HIGH);
	sleep(2);
	ss_gpio_write(SS_RELAY_REGULAR_LAMP, LOW);

SS_EXIT_FINAL:
	return status;
}


/*
 * FUNCTIONS
 */
 
/**@Brief - Configures gpio 'mode' specified by 'pin'. Sets it to
 * 'value'.
 * 
 **@Returns - error code, 0 if no errors
 */
int ss_gpio_cfg(uint8_t mode, uint8_t pin) {
	
	int status = 0; //no error yet
	int fd;
	char buf[25]; //Assuming pins do not go into 3 digit nums like pin 123.
	
	/* RESERVE GPIO */
	fd = open(SS_GPIO_EXPORT_STR, O_RDWR);
	
	if (fd < 0) {
	    fprintf(stderr, "Error! Cannot open file descriptor because of %d.", fd);
	    status = -4; //TODO-define
	}
	else {
#if SS_ENABLE_DEBUG_LOGS
		printf("fd %d\n", fd);
#endif
        fprintf(stdout, "Reserving gpio...\n");
	    sprintf(buf, "%d", pin);
	
	    write(fd, buf, strlen(buf));
	
        close(fd);
        
        
        /* SET GPIO Direction/Mode */
	    sprintf(buf, "/sys/class/gpio/gpio%d/direction", pin);
	    fd = open(buf, O_RDWR);
	    
	    if (fd < 0) {
	        fprintf(stderr, "Error! Cannot open file descriptor because of %d.\n", fd);
		    status = -5; //TODO-define
		}
	    else {
			fprintf(stdout, "Setting gpio direction...\n");
			
			if (mode == OUT) {
				write(fd, "out", pin);
			}
			else if (mode == IN) {
			    write(fd, "in", pin);
			}
			else {
				fprintf(stderr, "Error! Mode can only be (out) or (in). \n");
			}
			
			close(fd);
		}    
	}
	
	return status;
}

/**@Brief - 
 * TODO-fill this up!!
 */
int ss_gpio_write(uint8_t pin, bool value)
{
	int status = 0;
	int fd;
	char buf[100];
	
	sprintf(buf, "/sys/class/gpio/gpio%d/value", pin);
	
	/* Turning on GPIO */
	fd = open(buf, O_RDWR);
	
	if (fd < 0) {
		fprintf(stderr, "Error! Cannot open fd because of %d\n", errno);
	}
	else {
		fprintf(stdout, "Writing gpio...\n");
		
        if (value)
            write(fd, "1", 1); 
        else
            write(fd, "0", 1);
            
		close(fd);
	}
	
	return status;
}
