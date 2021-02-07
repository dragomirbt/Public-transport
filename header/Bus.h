#ifndef __BUS_HEADER_INCLUDED__
#define __BUS_HEADER_INCLUDED__
#include <vector>
#include "BusStop.h"

using namespace std;
class BusStop;


typedef vector<BusStop*> BusRoute;

class Bus
{
private:
	unsigned ID; 
	BusRoute route;
public:
	Bus(const unsigned ID = 0);
	unsigned getID() const;
	void addBusStopInRoute(BusStop* stop);
	bool hasBusStopInRoute(const string& busStopName);
	int getNumBusStopsInRoute() const;
	BusRoute& getRoute();
	string getBusStopNameFromRoute(const int idx);
	int getIdxTodeleteBusStop(const string& busStopName);
	BusStop* getStop(const string& name);
	BusStop* getAfterStop(BusStop* stop);
};

#endif // !__BUS_HEADER_INCLUDED__
