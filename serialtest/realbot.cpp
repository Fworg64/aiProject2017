#include "realbot.h"

#include <iostream>

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int _fd;

int init_bots(std::string ifname) {
	std::cout << ifname << std::endl;


	_fd = open(ifname.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (_fd == -1)
	{
		/*
		* Could not open the port.
		*/

		perror("open_port: Unable to open port");
	}
	else fcntl(_fd, F_SETFL, 0);

	struct termios options;
	tcgetattr(_fd, &options);
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(_fd, TCSANOW, &options);

	return (_fd);
}

typedef struct __attribute__((__packed__)) botdata {
	uint8_t command:8;
	uint32_t id:32;
	int8_t left:8;
	int8_t right:8;
} botdata;
// https://www.cmrr.umn.edu/~strupp/serial.html
void command_bot(uint32_t id, int8_t left, int8_t right) {
	std::cout << "id " << id << "\tleft\t" << (int)left << "\tright\t" << (int)right;
	botdata data;
	data.command = 0x02;
	data.id = id;
	data.left = left;
	data.right = right;

	int n = write(_fd, &data, sizeof(botdata));

	std::cout << " serial write result: " << n <<std::endl;

}
