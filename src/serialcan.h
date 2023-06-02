#ifndef SERIALCAN_H
#define SERIALCAN_H

#include <Arduino.h>
#include "can_com.h"

/*
 * Message from serial port:
 * 		starts with 2 bytes 0xFF
 *		data size (8 bit)
 *		id (4 bytes)
 *		uuid (2 bytes)
 *		data (up to 8 bytes)
 *      end string LOCO\r\n
 *
 * Minimum length: 
 */

#define SERIALCAN_MAX_BYTES 18
#define SERIALCAN_START_BYTES 2
#define SERIALCAN_START_VALUE 0xFF

#define SERIAL_END_STRING "LOCO"

#define SERIALCAN_BIN_FORMAT 0
#define SERIALCAN_HEX_FORMAT 1

/*
 * CAN_MESSAGE format
 *   uint32_t id;
 *   uint16_t uuid;
 *   uint8_t size;
 *   uint8_t data[8];
 *   uint8_t checksum;
 */

/*
 * message format
 *          content             length (bytes)
 *      ------------------------------------------
 *      START_BYTES         SERIAL_CAN_START_BYTES
 *      message size        1
 *      CAN-id              4
 *      UUID                2
 *      data bytes          message size
 *      checksum            1
 */

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