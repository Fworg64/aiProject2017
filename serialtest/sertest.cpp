#include "realbot.h"
#include <iostream>
#include <unistd.h>

int main() {
	int fd = init_bots("/dev/ttyUSB0");
	std::cout << fd <<std::endl;
	int8_t d = 0;
	while(1) {
		command_bot(1481622, d, d);
		d += 10;
		usleep(100000);
	}
}
