#define DOCTEST_CONFIG_IMPLEMENT
#include "../header/doctest.h"
#include "../header/Bus.h"
#include "../header/BusStop.h"
#include "../header/Schedule.h"
#include "../header/Graph.h"


TEST_CASE("Graph check")
{
    vector<BusStop*> stops;
    vector<Bus*> buses;
    Schedule sch;

    stops.push_back(new BusStop("Zagorka"));
    stops.push_back(new BusStop("Mol Galeria"));
    stops.push_back(new BusStop("Remiza"));
    stops.push_back(new BusStop("Ml. Dom"));
    stops.push_back(new BusStop("Bqla mechka"));
    stops.push_back(new BusStop("Hristo Botev"));
    stops.push_back(new BusStop("Poshta"));
    stops.push_back(new BusStop("Otec Paisii"));

    buses.push_back(new Bus(7));
    buses[0]->addBusStopInRoute(stops[0]); // Zagorka
    buses[0]->addBusStopInRoute(stops[1]); // Mol Galeriq
    buses[0]->addBusStopInRoute(stops[4]); // Bqla mechka

    buses.push_back(new Bus(120));
    buses[1]->addBusStopInRoute(stops[0]); // Zagorka
    buses[1]->addBusStopInRoute(stops[1]); // Mol Galeria
    buses[1]->addBusStopInRoute(stops[3]); // Ml dom
    buses[1]->addBusStopInRoute(stops[5]); // Hristo Botev

    buses.push_back(new Bus(80));
    buses[2]->addBusStopInRoute(stops[0]); // Zagorka
    buses[2]->addBusStopInRoute(stops[5]); // Hristo Botev
    buses[2]->addBusStopInRoute(stops[6]); // Poshta

    buses.push_back(new Bus(94));
    buses[3]->addBusStopInRoute(stops[0]); // Zagorka
    buses[3]->addBusStopInRoute(stops[2]); // Remiza
    buses[3]->addBusStopInRoute(stops[7]); // Otec Paisii
    buses[3]->addBusStopInRoute(stops[6]); // Poshta

    buses.push_back(new Bus(3));
    buses[4]->addBusStopInRoute(stops[1]); // Mol Galeria
    buses[4]->addBusStopInRoute(stops[3]); // Ml dom
    buses[4]->addBusStopInRoute(stops[6]); // Poshta
    
    stops[0]->addBus(buses[0]); // 7
    stops[0]->addBus(buses[1]); // 120
    stops[0]->addBus(buses[2]); // 80
    stops[0]->addBus(buses[3]); // 94

    stops[1]->addBus(buses[0]); // 7
    stops[1]->addBus(buses[1]); // 120
    stops[1]->addBus(buses[4]); // 3

    stops[2]->addBus(buses[3]); // 94

    stops[3]->addBus(buses[1]); // 120
    stops[3]->addBus(buses[4]); // 3

    stops[4]->addBus(buses[0]); // 7

    stops[5]->addBus(buses[1]); // 120
    stops[5]->addBus(buses[2]); // 80

    stops[6]->addBus(buses[2]); // 80
    stops[6]->addBus(buses[3]); // 94
    stops[6]->addBus(buses[4]); // 3

    stops[7]->addBus(buses[3]); //94

    vector<unsigned> times = { 365,375,385 };
    sch.addSchedule(7, "Zagorka", times);
   
    times = { 363,367,371 };
    sch.addSchedule(120, "Zagorka", times);

    times = { 361,364,367 };
    sch.addSchedule(80, "Zagorka", times);

    times = { 364,370,376 };
    sch.addSchedule(94, "Zagorka", times);

    times = { 368,378,388 };
    sch.addSchedule(7, "Mol Galeria", times);

    times = { 367,371,375 };
    sch.addSchedule(120, "Mol Galeria", times);

    times = { 368,373,378 };
    sch.addSchedule(3, "Mol Galeria", times);

    times = { 367,373,379 };
    sch.addSchedule(94, "Remiza", times);

    times = { 371,375,379 };
    sch.addSchedule(120, "Ml. Dom", times);

    times = { 373,378,383 };
    sch.addSchedule(3, "Ml. Dom", times);

    times = { 374,380,386 };
    sch.addSchedule(7, "Bqla mechka", times);

    times = { 374,378,379 };
    sch.addSchedule(120, "Hristo Botev", times);

    times = { 376,379,382 };
    sch.addSchedule(80, "Hristo Botev", times);

    times = { 372,377,382 };
    sch.addSchedule(94, "Otec Paisii", times);

    times = { 378,383,388 };
    sch.addSchedule(3, "Poshta", times);

    times = { 381,384,387 };
    sch.addSchedule(80, "Poshta", times);

    times = { 378,383,388 };
    sch.addSchedule(94, "Poshta", times);
        
    Graph g(stops, buses);
    CHECK(g.shortestRoute("Zagorka", "Poshta", 363, sch) == 378);
    CHECK(g.shortestRoute("Zagorka", "Hristo Botev", 360, sch) == 374);
    CHECK(g.shortestRoute("Zagorka", "Bqla mechka", 364, sch) == 374);

}

int main()
{
    doctest::Context().run();
    return 0;
}