//
// MyUI_HWSerial_Test by Super169
//
#ifndef _MYUI_HWSERIAL_H_
#define _MYUI_HWSERIAL_H_
#include "myUtil.h"
#include "MyUI.h"
#include "HardwareSerial.h"

class MyUI_HWSerial : public MyUI
{
	private:
		static const char* VERSION;

	public:

		MyUI_HWSerial(HardwareSerial& hwSerial, unsigned long speed);
		~MyUI_HWSerial();
		void whoAmI();
		char* getVersion();

		int begin();
		int end();
		int flush() {return 1;};
		int flush(unsigned long timeout) {return 1;};

    size_t write(uint8_t);
    size_t write(const uint8_t*  buffer, size_t len);

		size_t print(char *msg);
		size_t print(double data, uint8_t decimal, uint8_t width, uint8_t padMode);

		size_t print(long data)		{ return this->print((double) data, 0, 0, 0); };
		size_t print(long data, uint8_t width)		{ return this->print((double) data, 0, width, 1); };
		size_t print(long data, uint8_t width, uint8_t padMode)		{ return this->print((double) data, 0, width, padMode); };


		size_t println();
		size_t println(char *msg);

		size_t println(long data)		{ return (this->print(data) + this->println()); };
		size_t println(long data, uint8_t width)		{ return (this->print(data, width) + this->println()); };
		size_t println(long data, uint8_t width, uint8_t padMode)		{ return (this->print(data, width, padMode) + this->println()); };
		size_t println(double data, uint8_t decimal, uint8_t width, uint8_t padMode)		{	return (this->print( data, decimal, width, padMode) + this->println()); };


		void show(uint8_t row, char *msg);
		void show(uint8_t row, uint8_t col, char *msg);
		void show(uint8_t row, uint8_t col, double data, uint8_t decimal, uint8_t width, uint8_t padMode);

		void show(uint8_t row, uint8_t col, long data) 				{ this->show(row, col, (double) data, 0, 0, 0); };
		void show(uint8_t row, uint8_t col, long data, uint8_t width) 	{ this->show(row, col, (double) data, 0, width, 1); };
		void show(uint8_t row, uint8_t col, long data, uint8_t width, uint8_t padMode)		{ this->show(row, col, (double) data, 0, width, padMode); };



		void showXY(uint16_t x, uint16_t y, char *msg);
		void showXY(uint16_t x, uint16_t y, double data, uint8_t decimal, uint8_t width, uint8_t padMode);

		void showXY(uint16_t x, uint16_t y, long data)		{ this->showXY(x, y, (double) data, 0, 0, 0); } ;
		void showXY(uint16_t x, uint16_t y, long data, uint8_t width)		{ this->showXY(x, y, (double) data, 0, width, 1); } ;
		void showXY(uint16_t x, uint16_t y, long data, uint8_t width, uint8_t padMode)		{ this->showXY(x, y, (double) data, 0, width, padMode); } ;


		void cls() {};
		void cls(uint8_t row) {};
		void cls(uint8_t row_start, uint8_t row_end) {};
		void cls(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {};

		void fill() {};
		void fill(uint8_t row) {};
		void fill(uint8_t row_start, uint8_t row_end) {};
		void fill(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {};

	private:
		HardwareSerial& _conn;
		 unsigned long _speed;
		boolean _ready;
};

#endif  // _MYUI_HWSERIAL_H_
