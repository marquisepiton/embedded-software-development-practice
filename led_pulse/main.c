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
//#include <time.h> // Used for manipulating time and time information
//#include <stdio.h> // Standard I/O For essential functions like printf() and scanf()
//#include <errno.h> // Used for error reporting
//#include <string.h> // String string manipulation
//  POSIX/Unix-specific Header: 
//#include <termios.h> //  Used fro controlling terminal I/O characteristics.
//#include <unistd.h> // Unix Standard 
//#include <fcntl.h> //File Control
#include <avr/io.h>
#define F_CPU 16000000UL // Tell the compiler the clock speed (16MHz)
#include <util/delay.h>
int main()
{
	// Part 1: I setup contract with my kernel.
	// Fixed path and flag
	/*
	 * Success: 3
	 * Fail: -1
	 */
//	int serial_port = open("/dev/ttyACM0", O_RDWR);

//	if (serial_port < 0) 
//	{
//		printf("%d\n",serial_port);
///		printf("Error %i from open: %s\n", errno, strerror(errno));
//		return -1;
//	}

	//If serial_port is able to connect to device than it should return negative integeri. 
	//
//	printf("%d\n", serial_port);
//	printf("Successfully open serial port!\n");
//
	//https://man7.org/linux/man-pages/man3/termios.3.html#ATTRIBUTES
//	struct termios tty;

	// Return 0 or 1 if connection is set and valid 
//	if(tcgetattr(serial_port, &tty) != 0){
  //      	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    //    	return -1;
//	}

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
	 */
//	cfsetispeed(&tty, B9600);
//	cfsetospeed(&tty, B9600);
	
	// Note: Terminal Flags Pg. 1301
//	tty.c_cflag &= ~PARENB; // Enable parity generation on output and parity checking for input
//	tty.c_cflag &= ~CSTOPB; // Set two stop bits, rather than one. 
//	tty.c_cflag &= ~CSIZE; // Character size mask. Values are CS5, CS6, CS7, or CS8
//	tty.c_cflag |= CS8; //

	//tcsetattr(serial_port, TCSANOW, &tty);
//	 if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
  //     		 printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    //    	 return 1;
  //  	}
	
//	printf("Successfully opened and configured serial port! \n");

	// Part 2 Sending and Waiting for data: 
	// Read and write system calls
	
/*	
	// 1. Wait 2 seconds for the board to finish rebooting
	printf("Waiting for board to wake up...\n");
	usleep(2000000); 

	// 2. Write (Send) one byte
	char msg = 'A';
	write(serial_port, &msg, 1);
	printf("Sent: %c\n", msg);

	// 3. Read (Listen) loop
	printf("Waiting for reply...\n");
	char read_buf[256];
	while (1) {
    	// read() will block (wait) here until a byte arrives
    	int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

    	if (num_bytes > 0) {
        	// Print what we got from the Elegoo
        	for(int i = 0; i < num_bytes; i++) {
            		printf("Elegoo says: %c\n", read_buf[i]);
        	}
        	break; // Exit loop after we get a reply
    		}
	}	
*/

//#define GPIO_BASE 0x40020000
//#define GPIO_MODER (*(volatile unsigned int *)(GPIO_BASE + 0x00))
//#define GPIO_ODR (*(volatile unsigned int *)(GPIO_BASE + 0x2B))
	
	//volatile uint8_t *portd = (uint8_t *)0x2B;
	// Set pin as output (bit manipulation based on datasheet)
	// 0x0B (0x2B) 
	//GPIO_MODER |= (1 << 5);
	DDRD |= (1 << DD5);
	while(1){
		//Toggle specific bit for the LED
//		GPIO_ODR ^=(1 << 5);
//		for(volatile int i = 0; i < 100000; i++);
		PORTD |= (1 << PORT5);
        	_delay_ms(500); // Wait 500ms

        	// 3. Set PD5 LOW (Turn LED off)
        	PORTD &= ~(1 << PORT5);
        	_delay_ms(500); // Wait 500ms
	}
	//Close connection
//	close(serial_port);
	return 0; 
}


