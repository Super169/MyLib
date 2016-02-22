//
// MyUI by Super169
//
// Change Log:
//
//   2016-02-22 : Initial Version
//
#ifndef _MYUI_H_
#define _MYUI_H_

#include <Arduino.h>

class MyUI {

	public:

		virtual char* getVersion();
		virtual void whoAmI();
		virtual int begin() = 0;
		virtual int end() = 0;
		virtual int flush() = 0;
		virtual int flush(unsigned long timeout) = 0;

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t*  buffer, size_t len);

		virtual size_t print(char *msg);
		
		virtual size_t print(long data);
		virtual size_t print(long data, uint8_t width);
		virtual size_t print(long data, uint8_t width, uint8_t padMode);
//		virtual size_t print(double data, uint8_t decimal, uint8_t width);
		virtual size_t print(double data, uint8_t decimal, uint8_t width, uint8_t padMode);

		virtual size_t println(char *msg);
		virtual size_t println(long data);
		virtual size_t println(long data, uint8_t width);
		virtual size_t println(long data, uint8_t width, uint8_t padMode);
//		virtual size_t println(double data, uint8_t decimal, uint8_t width);
		virtual size_t println(double data, uint8_t decimal, uint8_t width, uint8_t padMode);

		virtual size_t println();

		virtual void show(uint8_t row, char *msg);
		virtual void show(uint8_t row, uint8_t col, char *msg);

		virtual void show(uint8_t row, uint8_t col, long data);
		virtual void show(uint8_t row, uint8_t col, long, uint8_t width);
		virtual void show(uint8_t row, uint8_t col, long, uint8_t width, uint8_t padMode);
		virtual void show(uint8_t row, uint8_t col, double data, uint8_t decimal, uint8_t width, uint8_t padMode);


		virtual void showXY(uint16_t x, uint16_t y, char *msg);
		virtual void showXY(uint16_t x, uint16_t y, long data);
		virtual void showXY(uint16_t x, uint16_t y, long data, uint8_t width);
		virtual void showXY(uint16_t x, uint16_t y, long data, uint8_t width, uint8_t padMode);
		virtual void showXY(uint16_t x, uint16_t y, double data, uint8_t decimal, uint8_t width, uint8_t padMode);


		virtual void cls();
		virtual void cls(uint8_t row);
		virtual void cls(uint8_t row_start, uint8_t row_end);
		virtual void cls(size_t x1, size_t y1, size_t x2, size_t y2);

		virtual void fill();
		virtual void fill(uint8_t row);
		virtual void fill(uint8_t row_start, uint8_t row_end);
		virtual void fill(size_t x1, size_t y1, size_t x2, size_t y2);
		

};

#endif  // _MYUI_H_
