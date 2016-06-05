#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int main(void)
{
	int fd;
	char buf[20];
	int gpio = 22;
	
	//export or reserve gpio
	fd = open("/sys/class/gpio/export", O_RDWR);
	if (fd < 0)
	{
		printf("error %d\n", fd);
	}
	else
	{
		sprintf(buf, "%d", gpio);
	    write(fd, buf, strlen(buf));	
	    close(fd);
	}
	
	//gpio mode/direction
	fd = open("/sys/class/gpio/gpio22/direction", O_RDWR);
	if (fd <  0)
	{
		printf("Error %d\n", fd);
	}
	else
	{
		read(fd, buf, 3);
		printf("%s\n", buf);
		write(fd, "out", 3);
		close(fd);
	}
	
	//gpio value
	fd = open("/sys/class/gpio/gpio22/value", O_RDWR);
	if (fd <  0)
	{
		printf("Error %d\n", fd);
	}
	else
	{
		char val;
		int i = 0;
		for(i=0; i<2; ++i)
	    {
			int err = read(fd, &val, 1);
			printf("val %d err %d\n", val, err);
			lseek(fd, err, SEEK_SET);
			
			if (val==49)
				write(fd, "0", 1);
			else if (val == 48)
				write(fd, "1", 1);
				
		    sleep(2);
        }			  
		
		close(fd);
	}
	
	return 0;
}
