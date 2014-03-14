/*
 * Created on 14/03/2014
 * Author: Cong Nguyen
 *
 * Using an Arduino Leonardo to interface with a TrackPoint
 * Pin 3 (int.0)	: CLOCK
 * Pin 2			: DATA
 * Pin 13			: RESET
 */
#include "TrackPoint.h"

#define	CLOCK		3
#define DATA		2
#define RESET		13
#define CLOCK_INT	0

TrackPoint trackpoint(CLOCK, DATA, RESET, true);

void setup()
{
	Mouse.begin();

	trackpoint.reset();
	trackpoint.setSensitivityFactor(0xC0);
	trackpoint.setStreamMode();

	attachInterrupt(CLOCK_INT, clockInterrupt, FALLING);
}

void loop()
{
	if(trackpoint.reportAvailable()) {
		TrackPoint::DataReport d = trackpoint.getStreamReport();
		Mouse.move(d.x, -d.y, 0);
	} 
}

void clockInterrupt(void) {
	trackpoint.getDataBit();
}