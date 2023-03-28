#include "serialcan.h"


// start serial communication with baudrate
void SERIALCAN::begin(long baud) {

	Serial.begin(baud);
}


// message is available
bool SERIALCAN::available(void) {

}


// send message to serial bus
bool send(CAN_MESSAGE* buffer) {

}


// read message
uint8_t read(CAN_MESSAGE* buffer) {

}