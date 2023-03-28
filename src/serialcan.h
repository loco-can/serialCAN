#ifndef SERIALCAN_H
#define SERIALCAN_H

#include <Arduino.h>


/*
 * Message from serial port:
 * 		starts with 4 bytes 0xFF
 *		count of overall bytes of the message (8 bit)
 *		id (16/32 bit) depending on 11 or 29 bit id
 *		[uuid (16 bit)]
 *		data (up to 8 bytes)
 *		data size (8 bit)
 *
 * Minimum length: 
 */


struct CAN_MESSAGE {
    uint32_t id;
    uint16_t uuid;
    uint8_t data[8];
    uint8_t size;
};


class SERIALCAN {

public:

	void begin(long baud);
	bool available(void);
	bool send(CAN_MESSAGE* buffer);
	uint8_t read(CAN_MESSAGE* butter);

private:


};



#endif