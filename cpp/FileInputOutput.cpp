#include "../header/FileInputOutput.h"

bool FileInputOutput::input( Program& Container)
{
	cout << "Enter the name of the input file: \n";
	string file_name;
	cin >> file_name;

	reading_file.open(file_name, ios::in);
	if (!reading_file)
	{
		cout << "Coudlnt open file\n";
		return false;
	}

	unsigned numBusStops;
	reading_file >> numBusStops;
	reading_file.ignore();
	string busStopName;
	for (unsigned i = 0; i < numBusStops; ++i)
	{

		getline(reading_file, busStopName);
		BusStop* stop = new BusStop(busStopName);
		Container.addBusStop(stop);
	}

	unsigned numBuses;
	reading_file >> numBuses;
	//reading the route for each bus
	for (unsigned i = 0; i < numBuses; ++i)
	{
		unsigned busID;
		reading_file >> busID;
		Bus* bus = new Bus(busID);
		Container.addBus(bus);
		unsigned numStops;
		reading_file >> numStops;
		string row; // get all bus stops 
		getline(reading_file, row);

		string stopName;
		int cnt = 0;
		while (row[cnt])
		{
			while (row[cnt] == ' ')
				cnt++;
			while (row[cnt] != ',' && row[cnt] != '\0')
			{
				stopName.push_back(row[cnt]);
				cnt++;
			}

			BusStop* busStopNameptr = Container.getBusStop(stopName);
			Bus* busptr = Container.getBus(busID);

			busptr->addBusStopInRoute(busStopNameptr);
			busStopNameptr->addBus(busptr);
			stopName = "";

			if (row[cnt] == '\0')
				break;
			cnt++;
		}
	}
	//reading the schedules
	reading_file.ignore();
	char c;
	Schedule* schedule = new Schedule();
	for (int i = 0; i < numBuses; i++)
	{
		do 
		{
			unsigned busID;
			reading_file >> busID;

			reading_file.get(c);
			while (c == ',' || c == ' '	)
				reading_file.get(c);

			reading_file.putback(c);
			string busStopName;
			reading_file.get(c);
			while (c != ',')
			{
				busStopName.push_back(c);
				reading_file.get(c);
			}

			vector<unsigned> times;
			while (reading_file.get(c))
			{
				if (c == '\n')
					break;
				unsigned time;
				reading_file >> time;
				times.push_back(time);
			}
			schedule->addSchedule(busID, busStopName, times);
			Container.addSchedule(schedule);

			reading_file.get(c);
			
			if (c == '-')
				break;
			else if (reading_file.eof())
				break;
			else
				reading_file.putback(c);

		} while (true);

	}
	return true;
}

bool FileInputOutput::output(Program& Container)
{
	cout << "Enter the name of the output file: \n";
	string file_name;
	cin >> file_name;

	writing_file.open(file_name, ios::out);
	if (!writing_file)
	{
		cout << "Couldnt open file\n";
		return false;
	}
	//printing the bus stops
	int numBusStops = Container.getNumBusStops();
	writing_file << numBusStops << endl;
	for (int i = 0; i < numBusStops; i++)
	{
		writing_file << Container.getBusStopContainer()[i]->getName() << endl;
	}
	writing_file << endl;

	int numBuses = Container.getNumBuses();
	writing_file << numBuses << endl;
	//printing the bus lines
	for (int i = 0; i < numBuses; i++)
	{
		int numBusStopsInRoute = Container.getBusesContainer()[i]->getNumBusStopsInRoute();
		writing_file << Container.getBusesContainer()[i]->getID() << ' ' << numBusStopsInRoute << ' ';
		for (int j = 0; j < numBusStopsInRoute; j++)
		{
			writing_file << Container.getBusesContainer()[i]->getRoute()[j]->getName();
			if (j != numBusStopsInRoute - 1)
				writing_file << ", ";
		}
		writing_file << endl;
	}
	writing_file << endl;

	//printing schedule
	for (int i = 0; i < numBuses; i++)
	{
		int busId = Container.getBusesContainer()[i]->getID();
		int numBusStopsInRoute = Container.getBusesContainer()[i]->getNumBusStopsInRoute();
		for (int j = 0; j < numBusStopsInRoute; j++)
		{
			string busStop_name = Container.getBus(busId)->getRoute()[j]->getName();
			writing_file << busId << ", " << busStop_name << ", ";
			//for the times
			int numTimes = Container.getSchedule()->getNumTimes(busId, busStop_name);
			for (int t = 0; t < numTimes; t++)
			{
				unsigned time = Container.getSchedule()->getTimeByIndex(busId, busStop_name, t);
				writing_file << time;
				if (t != numTimes - 1)
					writing_file << " ";
			}
			writing_file << endl;
		}
		if (i != numBuses - 1)
			writing_file << '-';

		writing_file << endl;
	}
	return true;
}