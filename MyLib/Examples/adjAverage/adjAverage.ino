//
//  adjAverage.ino by Super169 
//
//    Sample program to test adjAverage in myUtil
//
//  Change Log:
//
//    2016-02-22 : Initial version
//    
//
// Sample Data:
//
//   	1.63,98.51,5.16,29.54,71.,21.88,28.24,85.03,72.76,77.98,68.59,77.08,59.84,43.8,30.07,86.25,46.,28.5,16.49,71.62
//
// Expected Result:
//
//		0 >> 50.9985
//		1 >> 51.1017
//		2 >> 51.7763
//		3 >> 51.9214
//		4 >> 52.2533
//		5 >> 52.1720
//		6 >> 52.5575
//		7 >> 53.2167
//		8 >> 54.5575
//		9 >> 52.9200
//		10 >> 0.0000
//		11 >> 0.0000

#include "myUtil.h"

void setup() {
	Serial.begin(115200);
	double data[] = {1.63,98.51,5.16,29.54,71.,21.88,28.24,85.03,72.76,77.98,68.59,77.08,59.84,43.8,30.07,86.25,46.,28.5,16.49,71.62};
	for (uint8_t i = 0; i < 12; i++) {
		double avg = myUtil::adjAverage(data, 20,i);
		Serial.print(i);
		Serial.print(" >> ");
		Serial.println(avg, 4);
	}
}

void loop() {

}

