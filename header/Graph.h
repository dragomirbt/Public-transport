#ifndef __GRAPH__HEADER_INCLUDED
#define __GRAPH__HEADER_INCLUDED
#include "Bus.h"
#include "BusStop.h"
#include <vector>
#include <unordered_set>

using namespace std;
class Schedule;

class Graph
{
private:
    friend class Schedule;

    struct Edge;

    struct Node
    {
        BusStop* stop;
        vector<Edge> adj;

        // dijkstra only fields
        Node* pred; //predecessor
        int timeFromStart;
        int busID;
    };
    
    struct Edge
    {
        Bus* bus;
        Node* to;
    };
    

    vector<Node> vertices;


    void addEdge(Node& fromNode, BusStop* to, Bus* bus);
    Node* getByStop(BusStop* stop);
    Node* getByStopName(const string& name);
    void dijkstraInit(Node* startNode, unsigned startingTime, Schedule& sch);
    Node* next(unordered_set<Node*> &in);
    void update(Node* from, Edge toEdge, Schedule& sch);
    void printDijkstra(Node* node) const;
public:
    Graph(vector<BusStop*> &stops, vector<Bus*> &busses); 
    unsigned shortestRoute(const string& start, const string& end, unsigned startingTime, Schedule& sch);
};

#endif // !__GRAPH__HEADER_INCLUDED__