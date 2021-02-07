#include "../header/Schedule.h"
#
void Schedule::addSchedule(const unsigned busID, const string& busStopName, const vector<unsigned>& times)
{
	this->schedule[busID][busStopName] = times;
}

int Schedule::getNumTimes(const unsigned busID, const string& busStopName)
{
	return schedule[busID][busStopName].size();
}
int Schedule::getTimeByIndex(const unsigned busID, const string& busStopName, const int index)
{
	return schedule[busID][busStopName][index];
}

void Schedule::deleteCourse(const int busID,const string& busStopName)
{
	schedule[busID].erase(busStopName);
}

void Schedule::deleteBusLine(const int busID)
{
	schedule.erase(busID);
}

void Schedule::printSchedule(const string& busStopName)
{
	for (pair<const int, stopSchedule> &i : schedule)
	{
		cout << i.first << " ";
		for (pair<const string, vector<unsigned>> & j : i.second)
		{
			if (j.first == busStopName)
			{
				cout << j.first << " ";
				int arrSize = j.second.size();
				for (int c = 0; c < arrSize; c++)
				{
					cout << j.second[c] << " ";
				}
			}
		} 
		cout << endl;
	}
}
void Schedule::printBusLineSchedule(const int busID)
{
	for (auto& i : schedule)
	{
		if (i.first == busID)
		{
			for (auto& j : i.second)
			{
				cout << i.first << ' ';
				cout << j.first << ' ';
				int size = j.second.size();
				for (int c = 0; c < size; c++)
				{
					cout << j.second[c] << ' ';
				}
				cout << endl;
			}
		}
	}
}
int Schedule::arrivalTime(unsigned busId, Graph::Node* from, const string& arrivalStopName)
{
	vector<unsigned> list = schedule[busId][from->stop->getName()];
	unsigned index = 0;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == from->timeFromStart)
		{
			index = i;
			break;
		}
	}
	return schedule[busId][arrivalStopName][index];
}

int Schedule::quickestArrivalTimeAfter(unsigned busId, const string& startName, const string& stopName, unsigned time)
{
	vector<unsigned> list = schedule[busId][startName];
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] >= time)
			return schedule[busId][stopName][i];
	}
	return -1;
}
