/* 
 * LED PULSE
 * AUTHOR: KYU
 * DESCRIPTION: A flashing Led light. 
 * NOTES: 
 *
 * To bypass the arduino abstraction, I need to use the standard AVR Toolchain. (avr-libc: https://www.nongnu.org/avr-libc/user-manual/overview.html) 
 * Using avr-libc is the library I use to write the equivalent of a kernel for the microcontroller. 
 */
// Standard C Library Header:
#include <time.h> // Used for manipulating time and time information
#include <stdio.h> // Standard I/O For essential functions like printf() and scanf()
#include <errno.h> // Used for error reporting
#include <string.h> // String string manipulation
//  POSIX/Unix-specific Header: 
#include <termios.h> //  Used fro controlling terminal I/O characteristics.
#include <unistd.h> // Unix Standard 
#include <fcntl.h> //File Control
int main()
{
	// Fixed path and flag
	int serial_port = open("/dev/ttyACM0", O_RDWR);

	if (serial_port < 0) 
	{
		printf("%d\n",serial_port);
		printf("Error %i from open: %\n", errno, strerror(errno));
		return -1;
	}

	printf("Successfully open serial port!\n");

	struct terminos tty;

	if(tcgetattr(serial_port, &tty) != 0){
        	printf("Error %i from tcgetattr: %s\n", errono, strerror(errno));
        	return 1;
	}

	//set Baud Rate (speed)
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);

	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag &= |= CS8;

	tcsetattr(serial_port, TCSANOW, &tty);

	close(serial_port);
	return 0; 
}


