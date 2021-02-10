#include <queue>
#include <unordered_set>
#include <stack>
#include <iostream>
#include "../header/Graph.h"
#include "../header/Schedule.h"


typename Graph::Node* Graph::getByStop(BusStop* stop)
{
    int size = vertices.size();
    for (int i = 0; i < size ; i++)
    {
        if (vertices[i].stop == stop)
            return &vertices[i];
    }
}

typename Graph::Node* Graph::getByStopName(const std::string& name)
{
    for (int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].stop->getName() == name)
            return &vertices[i];
    }
}


void Graph::addEdge(Node& fromNode, BusStop* to, Bus* bus)
{
    Node* toNode = getByStop(to);

    fromNode.adj.push_back(Edge{bus, toNode});
    
}

Graph::Graph(std::vector<BusStop*> &stops, vector<Bus*> &busses)
{
    int size = stops.size();
    for (int i = 0; i < size; i++)
    {
        vertices.push_back(Node{stops[i]});
    }

    BusStop* nextStop;
    int Vsize = vertices.size();
    int Bsize = busses.size();
    for (int i = 0; i <Vsize; i++)
    {
        for (int j = 0; j < Bsize; j++)
        {
            if (vertices[i].stop->hasBus(busses[j]->getID()))
            {
                nextStop = busses[j]->getAfterStop(vertices[i].stop); //next stop in route
                if (nextStop != nullptr) //if not last stop
                    addEdge(vertices[i], nextStop, busses[j]);
            }
        }
    }
}

typename Graph::Node* Graph::next(std::unordered_set<Node*> &in)
{
    Node* min = nullptr;
    int size = vertices.size();
    for (int i = 0; i < size; i++)
    {
        if (vertices[i].timeFromStart != -1 && in.find(&vertices[i]) == in.end())  //if not found -> end iter
        {
            if (min == nullptr || vertices[i].timeFromStart < min->timeFromStart)
                min = &vertices[i];
        }
    }
    in.insert(min);
    return min;
}

void Graph::dijkstraInit(Graph::Node* startNode, unsigned startingTime, Schedule& sch)
{
    int size = vertices.size();
    for (int i = 0; i < size; i++)
    {
        vertices[i].timeFromStart = -1;
        vertices[i].pred = nullptr;
        vertices[i].busID = -1;
    }

    startNode->timeFromStart = startingTime; 
}

void Graph::update(Node* from, Edge toEdge, Schedule& sch)
{
    //find all buses which go from from->stop to toEdge.to->stop (neighboring stops)
    vector<Bus*> busses;
    int numBuses = from->stop->getNumBuses();
    for (int i = 0; i < numBuses; i++)
    {
        if (from->stop->getBusWithIdx(i)->getAfterStop(from->stop) == toEdge.to->stop)
            busses.push_back(from->stop->getBusWithIdx(i));
    } 

    // for each bus find the shortest time ariving to toEdge.to->stop,
    // which time for start is >= from->timeFromStart
    // and from all found choose the smallest
    int crrTime;
    int bestTime = -1;
    unsigned bestBusId = -1;
    for (Bus* bus: busses)
    {
        crrTime = sch.quickestArrivalTimeAfter(bus->getID(), from->stop->getName(), toEdge.to->stop->getName(), from->timeFromStart);
        if (bestTime == -1 || bestTime > crrTime)
        {
             bestTime = crrTime;
             bestBusId = bus->getID();
        }
    }

    // if traveling time to toEdge.to->timeFromStart >= bestTime или е -1 (aka not defined), we make an assignment,
    // because that way we have found the fastest way to go to that bus stop(until that moment!,later by traveling the graph there can be shroter)
    if (toEdge.to->timeFromStart == -1 || toEdge.to->timeFromStart > bestTime)
    {
        toEdge.to->timeFromStart = bestTime;
        toEdge.to->pred = from;
        toEdge.to->busID = bestBusId;
    }

}

void Graph::printDijkstra(Node* node) const
{
    stack<Node*> s;
    while (node != nullptr)
    {
        s.push(node);
        node = node->pred;
    }

    Node* crrNode;
    while (!s.empty())
    {
        crrNode = s.top();
        s.pop();
        if (s.empty())
            cout << crrNode->stop->getName() << '(' << crrNode->busID << ")\n";
        else
        {
            if (crrNode->busID != -1)
                cout << crrNode->stop->getName() << '(' << crrNode->busID << ") -> ";
            else
                cout << crrNode->stop->getName() << " -> ";
        }
    }
}


unsigned Graph::shortestRoute(const string& start, const string& end, unsigned startingTime, Schedule& sch)
{   
  
    Node* startNode = getByStopName(start);
    dijkstraInit(startNode, startingTime, sch);
    size_t size = vertices.size();
    unordered_set<Node*> in;


    Node* crr = nullptr;
    while (size > 0)
    {
        crr = next(in);
        if (crr != nullptr)
        {
            int size = crr->adj.size();
            for (int i = 0; i < size; i++)
            {
                update(crr, crr->adj[i], sch);
            }
        }
        size--;
    }
    Node* endNode = getByStopName(end);
    cout << "\nShortestRoute: ";
    printDijkstra(endNode);
    cout << "Arived at " << end << " at: " << endNode->timeFromStart << '\n';
    cout << "Total time traveled: " << endNode->timeFromStart - startingTime << '\n';
    return endNode->timeFromStart;
}
