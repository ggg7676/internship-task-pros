#include <vector>
#include "FlightsGraph.cpp"

struct Flight
{
    string from;
    string to;
    unsigned cost;
};

void subtaskOne(vector<Flight> input, const string& origin, const string& dest)
{
    FlightsGraph f;

    int numOfEntries = input.size();
    for(int i = 0; i < numOfEntries; ++i)
    {
        f.addFlight(input[i].from, input[i].to, input[i].cost);
    }

    f.getAllRoutes(origin, dest);
}


