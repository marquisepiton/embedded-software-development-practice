/* 
 * LED PULSE
 * AUTHOR: KYU
 * DESCRIPTION: A flashing Led light. 
 * NOTES: 
 *
 * To bypass the arduino abstraction, I need to use the standard AVR Toolchain. (avr-libc: https://www.nongnu.org/avr-libc/user-manual/overview.html) 
 * Using avr-libc is the library I use to write the equivalent of a kernel for the microcontroller. 
 */

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main()
{
	// Fixed path and flag
	int serial_port = open("/dev/ttyACM0", O_RDWR);

	if (serial_port) 
	{
		printf("Error %i from open: %\n", errno, strerror(errno));
		return 1;
	}

	printf("Successfully open serial port!\n");
	return 0; 
}
