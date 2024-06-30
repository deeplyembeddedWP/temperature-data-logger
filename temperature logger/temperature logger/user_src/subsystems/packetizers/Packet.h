/*
 * Packet.h
 *
 * Created: 30/06/2024 12:17:23 pm
 *  Author: Vinay Divakar
 */ 


#ifndef PACKET_H_
#define PACKET_H_

#include <stdint.h>
#include <stdbool.h>

struct packet_type_t {
	char name[32];
};

struct packet_param_t {
	char name[32];
	uint32_t timestamp;
	int8_t error;
	union {
		char value_str[64];
		float value_float;
		int value_int;
		bool value_bool;
	} value;
};



struct packet_t {
	struct packet_type_t type;
	struct packet_param_t param;
};

#endif /* PACKET_H_ */