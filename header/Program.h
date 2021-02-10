#ifndef __PROGRAM_HEADER_INCLUDED__
#define __PROGRAM_HEADER_INCLUDED__
#include "BusStop.h"
#include "Schedule.h"
#include <vector>
#include <string>
#include <iostream>


class Program
{
private:
	vector<BusStop*> BusStopsContainer;
	vector<Bus*> BusesContainer;
	Schedule schedule;
public:
	~Program();
	int getNumBusStops() const;
	int getNumBuses() const;
	void addBusStop(BusStop*& stop);
	void addBus(Bus*& bus);
	void addSchedule(const int busID, const string& busStopName, const vector<unsigned>& times);
	BusStop* getBusStop(const string& BusStopName);
	Bus* getBus(const int ID);
	vector<BusStop*> getBusStopContainer() const;
	vector<Bus*> getBusesContainer() const;
	Schedule getSchedule() const;
	bool hasBusStop(const string& busStopName);
	int getBusWithID(const int busID);
	void deleteBusStop(const string& busStopName);
	void deleteBusStopFromRoute(const string& busStopName);
	void deleteBusStopFromRouteWithBusID(const int busID, const string& busStopName);
	void deleteBusStopSchedule(const string& busStopName);
	void deleteBusLine(const int busID);
	void deleteBusFromBusStop(const int busID, const string& busStopName);
	void deleteCourse(const int busID, const string& busStopName);
	void printBusStopSchedule(const string& busStopName);
	void printBusLineSchedule(const int busID);
};

#endif // !__PROGRAM_HEADER_INCLUDED__
