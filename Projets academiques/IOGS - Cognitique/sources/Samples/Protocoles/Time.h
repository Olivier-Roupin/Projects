/************************************************************************************
 Filename    :   Time.h
 Content     :   
 Created     :   November 6th, 2018
 Author      :   Olivier Roupin
 Copyright   :   
 *************************************************************************************/

#ifndef Time_h
#define Time_h

#include <ctime>

double clockToMilliseconds(clock_t ticks) {
	// units/(units/time) => time (seconds) * 1000 = milliseconds
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}

double clockInMilliseconds() {
	return clockToMilliseconds(clock());
}

void wait(int ms) {
	clock_t beginFrame = clock();
	clock_t endFrame;
	do
	{
		endFrame = clock();
	} while (clockToMilliseconds(endFrame - beginFrame) < ms);
	return;
}

#endif // Time_h
