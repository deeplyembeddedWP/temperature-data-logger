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

/*
Parameter/Key-Value structure
*/
struct packet_param_t {
	char name[32]; // parameter name or key
	uint32_t timestamp; // timestamp the parameter was recorded
	int8_t error; // operational errors
	union { // value relevant to the parameter/key
		char value_str[64];
		float value_float;
		int value_int;
		bool value_bool;
	} value;
};


/*
Packet structure used for serializing into any format
*/
struct packet_t {
	char type[32]; // type of packet e.g. measurement
	struct packet_param_t param; // packet content
};

#endif /* PACKET_H_ */