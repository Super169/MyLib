//
// MyUI_HWSerial by Super169
//
// MyUI class for Hardware Serial
//
//  Change Log:
//
//    2016-02-22 : Initial version
//
#include "MyUI_HWSerial.h"
#include "myUtil.h"

const char* MyUI_HWSerial::VERSION = "1.0.0";


MyUI_HWSerial::MyUI_HWSerial(HardwareSerial& hwSerial,  unsigned long speed) :
	_conn(hwSerial)
{
	_speed = speed;
	_ready = false;
}

MyUI_HWSerial::~MyUI_HWSerial()
{
	this->end();
}

void MyUI_HWSerial::whoAmI() {
	this->print("MyUI_HWSerial v");
	this->println((char *)MyUI_HWSerial::VERSION);
}

char* MyUI_HWSerial::getVersion() {
	return (char *) MyUI_HWSerial::VERSION;
}

int MyUI_HWSerial::begin() {
	_conn.begin(_speed);
	_ready = true;
	return 1;
}

int MyUI_HWSerial::end() {
	if (_ready) {
		_conn.end();
		_ready = false;
	}
	return 1;
}

size_t MyUI_HWSerial::write(uint8_t c) {
	if (!_ready) return 0;
	_conn.write(c);
	return 1;
}

size_t MyUI_HWSerial::write(const uint8_t*  buffer, size_t len) {
	if (!_ready) return 0;
	_conn.write(buffer, len);
	return 1;
}

size_t MyUI_HWSerial::print(char* msg) {
	if (!_ready) return 0;
	return _conn.print(msg);
}

size_t MyUI_HWSerial::print(double data, uint8_t decimal, uint8_t width, uint8_t padMode) {
	if (!_ready) return 0;
	char buffer[21];
	uint8_t data_len;
	if (width == 0) {
		width = 20;
		padMode = 0;
	}
	data_len = myUtil::f2s(buffer, data, decimal, width, padMode);
	if (data_len) {
		this->print(buffer);
	}
	return data_len;
}


size_t MyUI_HWSerial::println(char* msg) {
	if (!_ready) return 0;
	return _conn.println(msg);
}

size_t MyUI_HWSerial::println() {
	if (!_ready) return 0;
	return _conn.println();
}

void MyUI_HWSerial::show(uint8_t row, char *msg) { 
	if (!_ready) return;
	return this->show(row, 0, msg);
}


void MyUI_HWSerial::show(uint8_t row, uint8_t col, char *msg) { 
	if (!_ready) return;
	_conn.print("[");
	_conn.print(row);
	_conn.print(",");
	_conn.print(col);
	_conn.print("] ");
	_conn.println(msg);
}

void MyUI_HWSerial::show(uint8_t row, uint8_t col, double data, uint8_t decimal, uint8_t width, uint8_t padMode) {
	if (!_ready) return;
	char buffer[21];
	uint8_t data_len;
	if (width == 0) {
		width = 20;
		padMode = 0;
	}	
	data_len = myUtil::f2s(buffer, data, decimal, width, padMode);
	if (data_len) {
		this->show(row, col, buffer);
	}
}

void MyUI_HWSerial::showXY(uint16_t x, uint16_t y, char *msg) { 
	if (!_ready) return;
	_conn.print("{");
	_conn.print(x);
	_conn.print(",");
	_conn.print(y);
	_conn.print("} ");
	_conn.println(msg); 
}

void MyUI_HWSerial::showXY(uint16_t x, uint16_t y, double data, uint8_t decimal, uint8_t width, uint8_t padMode) {
	if (!_ready) return;
	char buffer[21];
	uint8_t data_len;
	if (width == 0) {
		width = 20;
		padMode = 0;
	}	
	data_len = myUtil::f2s(buffer, data, decimal, width, padMode);
	if (data_len) {
		this->showXY(x, y, buffer);
	}
}
