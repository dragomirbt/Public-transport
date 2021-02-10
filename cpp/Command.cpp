#include "../header/Command.h"

Command::Command(Program& Container) : containers(&Container) {}

void Command::showCommands()
{
	cout << "These are the commands which you can use:\n\n";

	cout << "add bus stop -> adds bus stop\n"
		<< "add bus line -> adds bus line\n"
		<< "add course -> adds course to a bus line\n";

	cout << "\ndelete bus stop -> deletes bus stop\n"
		<< "delete bus line -> deletes bus line\n"
		<< "delete course -> deletes course in bus line\n";

	cout << "\nbus stop schedule -> shows the schedule for the bus stop\n"
		 << "bus line schedule -> shows the schedule for the whole bus line\n";

	cout << "\nend -> end of commands\n";
}
void Command::execute(const string& command)
{
	if (command == "add bus stop")
	{
		cout << "Enter the bus stop name you would like to add: \n";
		string busStopName;
		getline(cin,busStopName);
		BusStop* b = new BusStop(busStopName);
		containers->addBusStop(b);
	}
	else if (command == "add bus line")
	{
		cout << "Enter bus ID for which you would like to add a bus line:\n";
		unsigned busID;
		cin >> busID;
		Bus* bus = new Bus(busID);
		containers->addBus(bus);
		Bus* busptr = containers->getBus(busID);
		cout << "Enter how many bus stops will the bus pass through:\n";
		unsigned numStops;
		cin >> numStops;
		string busStopName;
		for (int i = 0; i < numStops; i++)
		{
			cout << "Enter the " << i + 1 << " bus stop name\n";
			cin.ignore();
			getline(cin, busStopName);
			BusStop* busStopptr = containers->getBusStop(busStopName);
			while (busStopptr == nullptr)
			{
				cout << "There is no such a bus stop name\n";
				cout << "Please enter an existing bus stop name\n";
				getline(cin, busStopName);
				busStopptr = containers->getBusStop(busStopName);

			}
			busptr->addBusStopInRoute(busStopptr);
			busStopptr->addBus(busptr);

			cout << "Enter the schedule for that stop\n"
				 << "Enter the number of times you will enter\n";

			unsigned numTimes;
			cin >> numTimes;
			vector<unsigned> times;
			for (int j = 0; j < numTimes; j++)
			{
				cout << "Enter the " << j + 1 << " time\n";
				unsigned time;
				cin >> time;
				times.push_back(time);
			}
			containers->addSchedule(busID, busStopName, times);
		}
	}
	else if (command == "add course")
	{
		cout << "Enter the bus ID for which u want to add a course\n";
		unsigned busID;
		cin >> busID;
		cout << "Enter the bus stop name that the bus will go to\n";
		string busStopName;
		cin.ignore();
		getline(cin, busStopName);
		//pointer to the b
		Bus* busptr = containers->getBus(busID);

		if (!busptr->hasBusStopInRoute(busStopName))
		{
			if (!containers->hasBusStop(busStopName))
			{
				vector<Bus*> buses;
				buses.push_back(busptr);
				BusStop* b = new BusStop(busStopName, buses);
				containers->addBusStop(b);
			}
			BusStop* busStopptr = containers->getBusStop(busStopName);

			busptr->addBusStopInRoute(busStopptr);
			busStopptr->addBus(busptr);

			cout << "Enter the schedule for that stop\n";
			
			int numTimes = containers->getSchedule().getNumTimes(busID, busStopName); //num times 
			if (numTimes == 0)
			{
				cout << "Enter the number of times you will enter\n";
				unsigned numTimes;
				cin >> numTimes;
				vector<unsigned> times;
				for (int i = 0; i < numTimes; i++)
				{
					cout << "Enter the " << i + 1 << " time\n";
					unsigned time;
					cin >> time;
					times.push_back(time);
				}
				containers->addSchedule(busID, busStopName, times);
			}
			else
			{
				vector<unsigned> times;
				for (int i = 0; i < numTimes; i++)
				{
					cout << "Enter the " << i + 1 << " time\n";
					unsigned time;
					cin >> time;
					times.push_back(time);
				}
				containers->addSchedule(busID, busStopName, times);
			}
		}
		else
			cout << "This bus has already that stop in his course\n";
	}
	else if (command == "delete bus stop")
	{
		cout << "Enter the bus stop name you want to delete:\n";
		string busStopName;
		getline(cin, busStopName);
		containers->deleteBusStop(busStopName);
		containers->deleteBusStopFromRoute(busStopName);
		containers->deleteBusStopSchedule(busStopName);
	}
	else if (command == "delete bus line")
	{
		cout << "Enter the bus ID line which you want to delete:\n";
		int busID;
		cin >> busID;
		//removes the bus from everywhere 
		containers->deleteBusLine(busID);
	}
	else if (command == "delete course")
	{
		cout << "Enter the bus ID and bus stop name of the course which you want to delete:\n";
		int busID;
		cin >> busID;
		cin.ignore();
		string busStopName;
		getline(cin, busStopName);

		containers->deleteCourse(busID, busStopName);
		containers->deleteBusStopFromRouteWithBusID(busID, busStopName);
		containers->deleteBusFromBusStop(busID, busStopName);
	}
	else if (command == "bus stop schedule")
	{
		cout << "Enter the bus stop name which schedule you want to see:\n";
		string busStopName;
		getline(cin, busStopName);

		containers->printBusStopSchedule(busStopName);
	}
	else if (command == "bus line schedule")
	{
		cout << "Enter the bus ID which line schedule you want to see:\n";
		int busID;
		cin >> busID;
		containers->printBusLineSchedule(busID);
	}
	else
	{
		cout << "There is no such a command like that\n";
	}

	cout << "Executed!\n" << "Enter next command:\n";
}