#include "../header/Program.h"

Program::~Program()
{
	int BusStopSize = BusStopsContainer.size();
	for (int i = 0; i < BusStopSize; i++)
		delete BusStopsContainer[i];
	
	int BusesSize = BusesContainer.size();
	for (int i = 0; i < BusesSize; i++)
		delete BusesContainer[i];

	delete schedule;
}

int Program::getNumBusStops() const
{
	return BusStopsContainer.size();
}
int Program::getNumBuses() const
{
	return BusesContainer.size();
}

void Program::addBusStop(BusStop*& stop)
{
	BusStopsContainer.push_back(stop);
}
void Program::addBus(Bus*& bus)
{
	BusesContainer.push_back(bus);
}
void Program::addSchedule(Schedule*& sch)
{
	schedule = sch;
}

BusStop* Program::getBusStop(const string& BusStopName)
{
	unsigned size = BusStopsContainer.size();
	for (unsigned i = 0; i < size; i++)
	{
		if (BusStopsContainer[i]->getName() == BusStopName)
			return BusStopsContainer[i];
	}
	return nullptr;
}
Bus* Program::getBus(const int ID)
{
	unsigned size = BusesContainer.size();
	for (unsigned i = 0; i < size; i++)
	{
		if (BusesContainer[i]->getID() == ID)
			return BusesContainer[i];
	}
	return nullptr;
}
vector<BusStop*> Program::getBusStopContainer() const
{
	return BusStopsContainer;
}
vector<Bus*> Program::getBusesContainer() const
{
	return BusesContainer;
}
Schedule* Program::getSchedule() const
{
	return schedule;
}

bool Program::hasBusStop(const string& busStopName)
{
	if (!getBusStop(busStopName))
		return false;
	return true;
}

int Program::getBusWithID(const int busID)
{
	int size = BusesContainer.size();
	for (int i = 0; i < size; i++)
	{
		if (BusesContainer[i]->getID() == busID)
			return i;
	}
}

void Program::deleteBusStop(const string& busStopName)
{
	int size = BusStopsContainer.size();
	for (int i = 0; i < size; i++)
	{
		if (BusStopsContainer[i]->getName() == busStopName)
		{
			BusStopsContainer.erase(BusStopsContainer.begin() + i);
			break;
		}
	}
}

void Program::deleteBusStopFromRoute(const string& busStopName)
{
	int size = BusesContainer.size();
	for (int i = 0; i < size; i++)
	{
		if (BusesContainer[i]->hasBusStopInRoute(busStopName))
		{
			int idx = BusesContainer[i]->getIdxTodeleteBusStop(busStopName);
			BusRoute* arrPtr = &BusesContainer[i]->getRoute();
			arrPtr->erase(arrPtr->begin() + idx);
		}
	}
}
void Program::deleteBusStopFromRouteWithBusID(const int busID ,const string& busStopName)
{
	int size = BusesContainer.size();
	for (int i = 0; i < size; i++)
	{
		if (BusesContainer[i]->hasBusStopInRoute(busStopName) && BusesContainer[i]->getID() == busID)
		{
			int idx = BusesContainer[i]->getIdxTodeleteBusStop(busStopName);
			BusRoute* arrPtr = &BusesContainer[i]->getRoute();
			arrPtr->erase(arrPtr->begin() + idx);
			break;
		}
	}
}
void Program::deleteBusStopSchedule(const string& busStopName)
{
	int numBuses = BusesContainer.size(); // num of buses will be the same as num schedules
	for (int i = 0; i < numBuses; i++)
	{
		int numBusStops = BusesContainer[i]->getRoute().size();
		for (int j = 0; j < numBusStops; j++)
		{
			if (BusesContainer[i]->getRoute()[j]->getName() == busStopName)
			{
				schedule->deleteCourse(BusesContainer[i]->getID(), busStopName);
				break;
			}
		}
	}
}

void Program::deleteBusLine(const int busID)
{
	//deletes the whole schedule for a bus
	schedule->deleteBusLine(busID);

	//delete the bus
	int numBuses = BusesContainer.size();
	for (int i = 0; i < numBuses; i++)
	{
		if (BusesContainer[i]->getID() == busID)
		{
			BusesContainer.erase(BusesContainer.begin() + i);
			break;
		}
	}

	int numBusStops = BusStopsContainer.size();
	for (int i = 0; i < numBusStops; i++)
	{
		int idx = BusStopsContainer[i]->hasBusWithID(busID);
		if (idx!= -1)
		{
			BusStopsContainer[i]->deleteBusLineFromBusStop(idx);
		}
	}
}
void Program::deleteCourse(const int busID, const string& busStopName)
{
	schedule->deleteCourse(busID, busStopName);
}
void Program::deleteBusFromBusStop(const int busID, const string& busStopName)
{
	int size = BusStopsContainer.size();
	for (int i = 0; i < size; i++)
	{
		if (BusStopsContainer[i]->getName() == busStopName)
		{
			int idx = BusStopsContainer[i]->hasBusWithID(busID);
			if (idx != -1)
			{
				BusStopsContainer[i]->deleteBusLineFromBusStop(idx);
			}
			break;
		}
	}
}
void Program::printBusStopSchedule(const string& busStopName)
{
	schedule->printSchedule(busStopName);
}

void Program::printBusLineSchedule(const int busID)
{
	schedule->printBusLineSchedule(busID);
}

