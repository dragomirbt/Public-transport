#ifndef __BUSSTOP_HEADER_INCLUDED__
#define __BUSSTOP_HEADER_INCLUDED__
#include <string>
#include <vector>
#include "Bus.h"
using namespace std;
class Bus;

class BusStop
{
private:
	string name;
	vector<Bus*> Buses;
public:
	BusStop(const string name, vector<Bus*> Buses = vector<Bus*>());
	string getName() const;
	int getNumBuses() const;
	Bus* getBusWithIdx(const int idx) const;
	bool hasBus(unsigned id) const;
	void setName(const string name);
	void addBus(Bus* bus);
	int hasBusWithID(const int busID);
	void deleteBusLineFromBusStop(const int idx);
};





#endif // !__BUSSTOP_HEADER_INCLUDED__
