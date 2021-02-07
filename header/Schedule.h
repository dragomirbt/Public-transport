#ifndef __SCHEDULE_HEADER_INCLUDED__
#define __SCHEDULE_HEADER_INCLUDED__
#include<unordered_map>
#include<iostream>
#include "Graph.h"

using namespace std;

// maps stop -> its schedule
typedef  unordered_map<string, vector<unsigned>> stopSchedule;

class Schedule
{
private:
	//maps bus ID -> certain stop -> its schedule
	unordered_map<int, stopSchedule> schedule;

public:
	void addSchedule(const unsigned busID, const string& busStopName, const vector<unsigned>& times);
	int getNumTimes(const unsigned busID, const string& busStopName);
	int getTimeByIndex(const unsigned busID, const string& busStopName, const int index);
	void deleteCourse(const int busID, const string& busStopName);
	void deleteBusLine(const int busID);
	void printSchedule(const string& busStopName);
	void printBusLineSchedule(const int busID);

	int quickestArrivalTimeAfter(unsigned busId, const string& startName, const string& stopName, unsigned time);
	int arrivalTime(unsigned busId, Graph::Node* from, const string& arrivalStopName);

};

#endif // !__SCHEDULE_HEADER_INCLUDED__
