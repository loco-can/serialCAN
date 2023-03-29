#ifndef SERIALCAN_H
#define SERIALCAN_H

#include <Arduino.h>


/*
 * Message from serial port:
 * 		starts with 4 bytes 0xFF
 *		data size (8 bit)
 *		id (4 bytes)
 *		uuid (2 bytes)
 *		data (up to 8 bytes)
 *
 * Minimum length: 
 */

#define SERIALCAN_MAX_BYTES 15
#define SERIALCAN_START_BYTES 2
#define SERIALCAN_START_VALUE 0xFF


struct CAN_MESSAGE {
    uint32_t id;
    uint16_t uuid;
    uint8_t size;
    uint8_t data[8];
    uint8_t checksum;
};


class SERIALCAN {

public:

	void begin(long baud);
	bool available(void);
	bool send(CAN_MESSAGE* buffer);
	CAN_MESSAGE read(void);

private:

    uint8_t _i, _j; // global iterators
    CAN_MESSAGE _message;
    uint8_t _buffer[sizeof(CAN_MESSAGE) + SERIALCAN_START_BYTES + 1];
    uint8_t _startbytes;
    uint8_t _counter;
    bool _reading;

    void _reset(void);
    bool _check_start(uint8_t);
    uint8_t _message2buffer(CAN_MESSAGE*);
    uint8_t _checksum(uint8_t*, uint8_t);
};



#endif