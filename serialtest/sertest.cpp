#include "realbot.h"
#include <iostream>
#include <unistd.h>

int main() {
	int fd = init_bots("/dev/ttyUSB0");
	std::cout << fd <<std::endl;
	int8_t d = 127;
	while(1) {
		//command_bot(1481622, d, d);
		d = 120;
		command_bot(1557094, d, -d);
		usleep(10000);
		command_bot(1554593, d, -d);
		usleep(10000);
		command_bot(1481416, d, -d);
		usleep(1000000);

		d = 0;
		command_bot(1557094, d, d);
		usleep(10000);
		command_bot(1554593, d, d);
		usleep(10000);
		command_bot(1481416, d, d);
		usleep(1000000);
		//1554593
		//1481416
	}
}
