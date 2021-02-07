#include <iostream>
#include "../header/Bus.h"
#include "../header/BusStop.h"
#include "../header/Schedule.h"
#include "../header/Graph.h"
#include "../header/Program.h"
#include "../header/FileInputOutput.h"
#include "../header/Command.h"


using namespace std;

int main()
{
	Program Container;

	cout << "Are you going to add an information from file? \n";
	string vote;
	cin >> vote;
	FileInputOutput parse;
	if (vote == "yes" || vote == "Yes")
	{
		if (!parse.input(Container))
			return -1;
	}
	
	Command c(Container);
	c.showCommands();
	string command;
	cin.ignore();
	getline(cin,command);
	cout << endl;
	string stopCommand = "end";

	while (command != stopCommand)
	{
		c.execute(command);
		getline(cin, command);
	}

	vector<BusStop*> stops = Container.getBusStopContainer();
	vector<Bus*> buses = Container.getBusesContainer();
	Schedule* sch = Container.getSchedule();
	Graph g(stops, buses);

	cout << "Enter the bus stop name you will start from:\n";
	string startBusStopName;
	getline(cin, startBusStopName);
	cout << "Enter the bus stop name you want to go to:\n";
	string endBusStopName;
	getline(cin, endBusStopName);
	cout << "Enter at what time you go to the start bus stop\n";
	unsigned start_time;
	cin >> start_time;
	
	g.shortestRoute(startBusStopName, endBusStopName, start_time, *sch);
	cout << endl;
	
	cout << "Do you want to save the data int file:\n";
	cin >> vote;
	if (vote == "yes" || vote == "Yes")
	{
		if (!parse.output(Container))
			return -1;
	}

	return 0;
}