#include "../header/BusStop.h"

BusStop:: BusStop(const string name, vector<Bus*> Buses) : name(name), Buses(Buses) {}

string BusStop::getName() const 
{
	return name; 
}

int BusStop::getNumBuses() const
{ 
	return Buses.size();
}

Bus* BusStop::getBusWithIdx(const int idx) const
{
	return Buses[idx];
}

bool BusStop::hasBus(unsigned id) const
{
	int size = Buses.size();
	for (int i = 0; i < size; i++)
	{
		if (Buses[i]->getID() == id)
			return true;
	}
	return false;
}

void BusStop::setName(const string name)
{
	this->name = name;
}

void BusStop::addBus(Bus* bus)
{
	Buses.push_back(bus);
}

// if its there return the idx otherwise -1
int BusStop::hasBusWithID(const int busID) 
{
	int size = Buses.size();
	for (int i = 0; i < size; i++)
	{
		if (Buses[i]->getID() == busID)
			return i;
	}
	return -1;
}

void BusStop::deleteBusLineFromBusStop(const int idx)
{
	Buses.erase(Buses.begin() + idx);
}