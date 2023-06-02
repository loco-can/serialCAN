#include "serialcan.h"


// start serial communication with baudrate
void SERIALCAN::begin(long baud) {

	Serial.begin(baud);

	_reset();
}


// message is available
bool SERIALCAN::available(void) {

	uint8_t byte;

	if (Serial.available()) {

		// add data to buffer
		if (_counter < SERIALCAN_MAX_BYTES) {

			if (_check_start(byte)) {
				_buffer[_counter++] = byte;
			}
		}

		// message is too long -> discard
		else {
			_reset();
			return false;
		}
	}
}


// send message to serial bus
bool SERIALCAN::send(CAN_MESSAGE* message) {

	uint8_t length;

	length = _message2buffer(message);

	// send data as binary
	Serial.write(_buffer, length);

	// send header as ascii line
	// Serial.println(SERIAL_END_STRING);
}


// read message
CAN_MESSAGE SERIALCAN::read(void) {

}


// reset read counter
void SERIALCAN::_reset(void) {

	_counter = 0;
	_startbytes = 0;
	_reading = false;
}


// check if message has started
// SERIALCAN_START_BYTES SERIALCAN_START_VALUE received
bool SERIALCAN::_check_start(uint8_t byte) {

	if (byte == SERIALCAN_START_VALUE) {

		if (_startbytes < SERIALCAN_START_BYTES) {

			_startbytes++;
			return false;
		}

		else {
			return true;
		}
	}
}


// convert message to byte buffer array
uint8_t SERIALCAN::_message2buffer(CAN_MESSAGE* message) {

	// write start bytes
	for (_i = 0; _i < SERIALCAN_START_BYTES; _i++) {
		_buffer[_i] = SERIALCAN_START_VALUE;
	}

	// add data size in bytes
	_buffer[_i++] = message->size;

	// add can-id
	_buffer[_i++] = (message->id >> 24) & 0xFF;
	_buffer[_i++] = (message->id >> 16) & 0xFF;
	_buffer[_i++] = (message->id >> 8) & 0xFF;
	_buffer[_i++] = message->id & 0xFF;

	// add uuid
	_buffer[_i++] = (message->uuid >> 8) & 0xFF;
	_buffer[_i++] = message->uuid & 0xFF;

	// add data bytes
	for (_j = 0; _j < message->size; _j++) {
		_buffer[_i++] = message->data[_j];
	}

	// add checksum
	_buffer[_i++] = _checksum(_buffer, _i);

	// add end string
	for (_j = 0; _j < sizeof(SERIAL_END_STRING) - 1; _j++) {
		_buffer[_i++] = SERIAL_END_STRING[_j];
	}

	// add end of line
	_buffer[_i++] = 13;
	_buffer[_i++] = 10;

	return _i;
}


// calculate checksum of array
uint8_t SERIALCAN::_checksum(uint8_t* data, uint8_t length) {

	uint8_t sum = 0;
	uint8_t i;

	for(_j = 0; _j < length; _j++) {
		sum ^= data[_j];
	}

	return sum;
}