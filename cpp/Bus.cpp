#include "../header/Bus.h"
#include "../header/BusStop.h"

Bus::Bus(const unsigned ID) : ID(ID) {}

unsigned Bus::getID() const
{ 
	return ID;
}

void Bus::addBusStopInRoute(BusStop* stop)
{
	if(stop != nullptr)
		route.push_back(stop);
}

bool Bus::hasBusStopInRoute(const string& busStopName)
{
	int size = route.size();
	for (int i = 0; i < size; i++)
	{
		if (route[i]->getName() == busStopName)
			return true;
	}
	return false;
}

int Bus::getNumBusStopsInRoute() const
{
	return route.size();
}
BusRoute& Bus::getRoute() 
{
	return route;
}

string Bus::getBusStopNameFromRoute(const int idx)
{
	return route[idx]->getName();
}

int Bus::getIdxTodeleteBusStop(const string& busStopName)
{
	int size = route.size();
	for (int i = 0; i < size; i++)
	{
		if (route[i]->getName() == busStopName)
			return i;
	}
}

BusStop* Bus::getStop(const string& name)
{
	int size = route.size();
	for (int i = 0; i < size; i++)
	{
		if (route[i]->getName() == name)
		{
			return route[i];
		}
	}
	return nullptr;
}
BusStop* Bus::getAfterStop(BusStop* stop)
{
	size_t size = route.size();
	for (int i = 0; i < size; i++)
	{
		if (route[i] == stop && i != size - 1)
		{
			return route[i + 1];
		}
	}
	return nullptr;
}
