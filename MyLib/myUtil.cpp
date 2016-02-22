//
// myUtil.cpp by Super169
//
// Change Log:
//   
//   2016-02-22 : Initial version

#include "myUtil.h"

//  
//  unsigned int availableMemory(unsigned int max) 
//
//  Check the available memory in byte with given maximum size
//
unsigned int myUtil::availableMemory(unsigned int max)	 {
  unsigned int size = max; 
  byte *buf;
  while ((buf = (byte *) malloc(--size)) == NULL) ;
  free(buf);
  return size;
}

//
// void myDleay(unsigned long idle_period)
//
// My own delay function (forgot the reason why I build this one, seems it will work for some situation that delay function not work)
//
void myUtil::myDelay(unsigned long idle_period) {
	unsigned long start_time = millis();
	while (millis() - start_time < idle_period);
}


//
// uint8_t f2s(char* buffer, double value, uint8_t decimal, uint8_t width, uint8_t padMode, char padChar) 
//
// Convert the value into string with give format, and return the length of string
// - decimal: decimal place
// - width: size of the string (the buffer must have size not less than width + 1 )
// - padMode: 0 - fit value '1.0', 1 - Right align '  1.0', 2 - Left align  '1.0  '
// - padChar: character used to fill the empty space, will be ignored if padMode = 0        
//
//
uint8_t myUtil::f2s(char* buffer, double value, uint8_t decimal, uint8_t width, uint8_t padMode, char padChar) {

  if (width == 0) return false;

  double absValue, adjValue;
  // for safety, don't use unsigned int here, as the length (e.g. len_rem) can be negative after calculation
  int len_ne, len_int, len_dec, len_rem, data_len;

  if (value < 0) {
    len_ne = 1;
    absValue = - value;
  } else {
    len_ne = 0;
    absValue = value;
  }
  len_int = getLen(absValue);
  if (len_ne + len_int > width) {
    return fillError(buffer, width);
  }

  len_dec = (decimal > 0 ? 1 : 0);
  if (decimal) {
    len_rem = width - (len_ne + len_int + len_dec);
    if (len_rem > decimal) {
      len_rem = decimal;
    } else {
      if (len_rem <= 0) {
        len_rem = 0;
        len_dec = 0;  // no need to display decimal place
      }
    }
  } else {
    len_rem = 0;
  }

  data_len = len_ne + len_int + len_dec + len_rem;
  adjValue = absValue + 0.5 / getFactor(len_rem);

  // check if addition digits after round up (e.g. 999.5 -> 1000.0)
  if (getLen(adjValue) > len_int) {
    len_int++;
    if (len_ne + len_int > width) {
      return fillError(buffer, width);
    }
    if ((width > 0) && (data_len >= width)) {
      // try to reduce decimal to fit the display
      if (len_rem > 0) {
        len_rem--;
        adjValue = absValue + 0.5 / getFactor(len_rem);
        if (len_rem == 0) len_dec = 0;
      }
    }
    data_len = len_ne + len_int + len_dec + len_rem;
  }
  
  // Fill buffer with 0 as terminator anywhere, * size = width + 1
  for (int idx = 0; idx <= width; idx++) buffer[idx] = 0;

  if (len_rem == 0) len_dec = 0;
  data_len = len_ne + len_int + len_dec + len_rem;

  uint8_t ptr = 0;
  // pad left
  if (padMode == _F2S_PAD_LEFT) while (ptr < width - data_len) buffer[ptr++] = padChar;

  if (len_ne) buffer[ptr++] = '-';

  unsigned long adjInt = (unsigned long) adjValue;

  setNum(buffer, ptr, adjInt, len_int);
  ptr += len_int;
  if (len_rem > 0) {
    buffer[ptr++] = '.';
    unsigned long adjRem = getFactor(len_rem) * (adjValue - adjInt);
    setNum(buffer, ptr, adjRem, len_rem);
    ptr += len_rem;
  }
  // pad right
  if (padMode == _F2S_PAD_RIGHT) while (ptr < width) buffer[ptr++] = padChar;

  // Just for safety, should already filled with 0 before
  buffer[ptr] = 0;
  return ptr;
  
}

//
// (private) uint8_t fillError(char* buffer, uint8_t width) 
//
// Fill the buffer with error; it's expected that the buffer has size not less than (width + 1) 
//
uint8_t myUtil::fillError(char* buffer, uint8_t width) {
  for (int idx=0; idx < width; idx++) buffer[idx] = '-';
  buffer[width] = 0;
  return 0;
}

//
// (private) setNum(char* buffer, uint8_t idx, unsigned long value, uint8_t len)
//
// Convert the unsigned long value into a string and stored in character array of fixed length (fill with leading zero) in given position 
//
uint8_t myUtil::setNum(char* buffer, uint8_t idx, unsigned long value, uint8_t len) {

  idx += len- 1;
  for (int i = 0; i < len; i++) {
    buffer[idx - i] = '0' + (value % 10);
    value /= 10;
  }
}

//
// (private) double getFactor(uint8_t len)
//
// Get the value of 10^len, to be used as the multiplier for internal calculation
//
double myUtil::getFactor(uint8_t len) {
  unsigned long ul_decimal = 1;
  for (int i = 0; i < len; i++) ul_decimal *= 10;
  return ((double) ul_decimal);
}

//
// (private) uint8_t getLen(unsigned long value):
//
// Use simple comparison for quick checking of data length instead of mathematical function: int(log10(value))
// maximum value = 4294967040; i.e. max 10 digits
//
uint8_t myUtil::getLen(unsigned long value) {
  if (value < 0) value = -value;
  if (value >= 1000000000) return 10;
  if (value >= 100000000) return 9;
  if (value >= 10000000) return 8;
  if (value >= 1000000) return 7;
  if (value >= 100000) return 6;
  if (value >= 10000) return 5;
  if (value >= 1000) return 4;
  if (value >= 100) return 3;
  if (value >= 10) return 2;
  return 1;
}

//
// double adjAverage(double* samples, uint8_t sample_size, uint8_t exclude_size)
//
// Calculate the average of given array with adjustment for removing extreme values
//
double myUtil::adjAverage(double* samples, uint8_t sample_size, uint8_t exclude_size) {

  uint8_t idx;
  if (sample_size == 0) return 0;

  if (sample_size <= 2 * exclude_size) return 0;

  double exclude_min[exclude_size], exclude_max[exclude_size];

  if (sample_size == 1) {
    return samples[0];
  }

  double sum, max, min, avg;
  boolean upd_min, upd_max;

  sum = 0;
  if (exclude_size) {
    exclude_min[0] = exclude_max[0] = sum = samples[0];
    uint8_t pos;
    for (uint8_t i = 1; i < exclude_size; i++) {
      sum += samples[i];
      for (pos = 0; pos < i; pos++) {
        if (exclude_min[pos] > samples[i]) break;
      }
      insertToArray(samples[i], exclude_min, i + 1, pos);
      for (pos = 0; pos < i; pos++) {
        if (exclude_max[pos] < samples[i]) break;
      }
      insertToArray(samples[i], exclude_max, i + 1, pos);
    }
  }

  for (int i = exclude_size; i < sample_size; i++) {
    upd_min = upd_max = false;
    for (uint8_t j=0; j < exclude_size; j++) {

      if ((!upd_min) && (exclude_min[j] > samples[i])) {
        upd_min = true;
        insertToArray(samples[i], exclude_min, exclude_size, j);
      }
      if ((!upd_max) && (exclude_max[j] < samples[i])) {
        upd_max = true;
        insertToArray(samples[i], exclude_max, exclude_size, j);
      }
    }
    sum += samples[i];
  }
  for (int i = 0; i < exclude_size; i++) {
    sum -= exclude_min[i];
    sum -= exclude_max[i];
  }
  avg = sum / (sample_size - 2 * exclude_size);
  return avg;

}


//
// void insertToArray(double value, double* data, uint8_t size, uint8_t pos) 
//
// Insert the value into data array of given position, exiting data will be shifted, and the last one will be lost
//
void myUtil::insertToArray(double value, double* data, uint8_t size, uint8_t pos) {
  if (pos >= size) return;
  if (pos == size -1) {
    data[pos] = value;
  } else {
    for (uint8_t i = size - 1; i > pos; i--) {
      data[i] = data[i-1];
    }
    data[pos] = value;
  }
}

//
// uint8_t getFlashMsg(char * localMsgPtr, const char * flashMsgPtr, uint8_t buffer_size)
//
//  Get the message string from Flash Memory 
//
uint8_t myUtil::getFlashMsg(char * localMsgPtr, const char * flashMsgPtr, uint8_t buffer_size) {
	uint8_t idx = 0;
	while ((idx < buffer_size - 1) && (localMsgPtr[idx] =  pgm_read_byte(&flashMsgPtr[idx]))) {idx++;}
	localMsgPtr[idx] = 0;
  return idx;
}