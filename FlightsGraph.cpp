#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

struct sortByPrice
{
    bool operator() (pair<vector<string>, unsigned>& a, pair<vector<string>, unsigned>& b)
    {
        return a.second < b.second;
    }
};


class FlightsGraph
{
    unordered_map<string, vector<pair<string, unsigned>>> adjList;

    void DFS(const string& origin, const string& dest, unordered_map<string, bool>& visited, 
            vector<string>& currRoute, unsigned currTotalPrice, vector<pair<vector<string>, unsigned>>& allRoutes);


public:

    void addFlight(const string& from, const string& to, unsigned cost)
    {
        adjList[from].push_back(make_pair(to, cost));
    }

    void getAllRoutes(const string& origin, const string& dest);


};

//O(n + m)
void FlightsGraph::DFS(const string& origin, const string& dest, unordered_map<string, bool>& visited, 
                       vector<string>& currRoute, unsigned currTotalPrice, vector<pair<vector<string>, unsigned>>& allRoutes)
{
    visited[origin] = true;
    currRoute.push_back(origin);

    if (origin == dest)
    {
        allRoutes.push_back(make_pair(currRoute, currTotalPrice));
    }

    else
    {
        vector<pair<string, unsigned>>::iterator it = adjList[origin].begin();
        for(it; it != adjList[origin].end(); ++it)
        {
            string neighbour = (*it).first;
            unsigned cost = (*it).second;

            if(!visited[neighbour])
            {
                //we continue creating the route from here onwards
                DFS(neighbour, dest, visited, currRoute, currTotalPrice + cost, allRoutes);
            }
        }
    }

    currRoute.pop_back();
    visited[origin] = false;

    
}

void FlightsGraph::getAllRoutes(const string& origin, const string& dest)
{
    unordered_map<string, bool> visited;
    vector<string> currRoute;
    unsigned currTotalPrice = 0;
    vector<pair<vector<string>, unsigned>> allRoutes;

    DFS(origin, dest, visited, currRoute, currTotalPrice, allRoutes);

    if (allRoutes.empty())
    {
        cout << "No routes";
    }

    else
    {
        
        sort(allRoutes.begin(), allRoutes.end(), sortByPrice());

        vector<pair<vector<string>, unsigned>>::iterator it = allRoutes.begin();
        for (it; it != allRoutes.end(); ++it)
        {
            vector<string> routeCities = (*it).first;
            unsigned routePrice = (*it).second;

            vector<string>::iterator it2 = routeCities.begin();
            for(it2; it2 != routeCities.end(); ++it2)
            {
                cout << (*it2) << ", ";
            }

            cout << routePrice <<endl;
        }
    }
}