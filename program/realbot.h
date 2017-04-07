#ifndef REALBOT
#define REALBOT

#include <cstdint>
#include <string>

int init_bots(std::string ifname);
void command_bot(uint32_t id, int8_t left, int8_t right);

#endif
