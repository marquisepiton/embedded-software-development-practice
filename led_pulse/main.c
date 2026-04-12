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
	// Part 1: I setup contract with my kernel.
	//	
	// Fixed path and flag
	int serial_port = open("/dev/ttyACM0", O_RDWR);

	if (serial_port < 0) 
	{
		printf("%d\n",serial_port);
		printf("Error %i from open: %s\n", errno, strerror(errno));
		return -1;
	}

	//If serial_port is able to connect to device than it should return 1. 
	//
	printf("%d\n", serial_port);
	printf("Successfully open serial port!\n");

	struct termios tty;

	if(tcgetattr(serial_port, &tty) != 0){
        	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        	return -1;
	}

	/*set Baud Rate (speed)
	 * Baud rate is the speed at which data is transmitted in a communication system, measured in t		he number of signal changes (symbols) per second. 
	 * Common Baud Rate: 9600, 19200, 38400, 57600, 115200
	 *
	 * Bit Rate = Baud Rate x Number of bits per symbol.
	 *
	 * What if I increase the Bd Rate?: 
	 * Increasing the baud rate can significantly improve your project's performance, but makes the		connectiion more sensitive to hardware limits and external interference. 
	 *
	 * What would be instances for increasing?: 
	 * 
	 * If I'm collecting data every 1 millisecond (1000 samples per second).
	 *
	 *
	 *
	 */
	cfsetispeed(&tty, B9600);
	cfsetospeed(&tty, B9600);

	tty.c_cflag &= ~PARENB;i
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |= CS8;

	//tcsetattr(serial_port, TCSANOW, &tty);
	 if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
       		 printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        	 return 1;
    	}
	
	printf("Successfully opened and configured serial port! \n");

	// Part 2 Sending and Waiting for data: 
	// Read and write system calls
	//
	

	
	close(serial_port);
	return 0; 
}


