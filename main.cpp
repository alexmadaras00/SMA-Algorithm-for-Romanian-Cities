#include <iostream>
#include <bits/stdc++.h>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;
#define MIN_DISTANCE 999999;
typedef pair<pair<string, string>, int> distancePair;
typedef pair<string, vector<int>> neighbour;
vector<string> wrongPath;
map<string, bool> isReached = {{"Timisoara", false}, {"Arad", false}, {"Bucuresti", false}, {"Sibiu", false}, {"Brasov", false}, {"Oradea", false}, {"Resita", false}, {"Deva", false}, {"Rimnicu Valcea", false}, {"Pitesti", false}, {"Craiova", false}, {"Slatina", false}, {"Slobozia", false}, {"Giurgiu", false}, {"Constanta", false}, {"Buzau", false}, {"Focsani", false}, {"Bacau", false}, {"Iasi", false}, {"Piatra Neamt", false}, {"Targoviste", false}};
vector<distancePair> distances = {
    {{"Giurgiu", "Bucuresti"}, 65},
    {{"Ploiesti", "Bucuresti"}, 80},
    {{"Slatina", "Bucuresti"}, 178},
    {{"Slobozia", "Bucuresti"}, 125},
    {{"Targoviste", "Bucuresti"}, 109},
    {{"Craiova", "Slatina"}, 51},
    {{"Craiova", "TarguJiu"}, 109},
    {{"Pitesti", "Targoviste"}, 80},
    {{"RamnicuValcea", "Pitesti"}, 62},
    {{"RamnicuValcea", "Sibiu"}, 100},
    {{"RamnicuValcea", "TarguJiu"}, 113},
    {{"Deva", "TarguJiu"}, 148},
    {{"Resita", "TarguJiu"}, 227},
    {{"Resita", "Timisoara"}, 97},
    {{"Arad", "Timisoara"}, 55},
    {{"Arad", "Deva"}, 178},
    {{"Arad", "Oradea"}, 113},
    {{"Deva", "Oradea"}, 185},
    {{"Deva", "Sibiu"}, 128},
    {{"Brasov", "Sibiu"}, 141},
    {{"Brasov", "TarguMures"}, 193},
    {{"Brasov", "Ploiesti"}, 106},
    {{"Buzau", "Ploiesti"}, 71},
    {{"Buzau", "Focsani"}, 72},
    {{"Buzau", "Braila"}, 103},
    {{"Tulcea", "Braila"}, 100},
    {{"Tulcea", "Slobozia"}, 158},
    {{"Constanta", "Slobozia"}, 138},
    {{"Bacau", "Focsani"}, 106},
    {{"Bacau", "PiatraNeamt"}, 60}};

map<string, int> heuristics = {
    {"Bucuresti", 0},
    {"Giurgiu", 62},
    {"Ploiesti", 58},
    {"Slatina", 138},
    {"Slobozia", 100},
    {"Targoviste", 75},
    {"Craiova", 183},
    {"TarguJiu", 233},
    {"Pitesti", 103},
    {"RamnicuValcea", 151},
    {"Resita", 341},
    {"Timisoara", 405},
    {"Arad", 416},
    {"Oradea", 429},
    {"Deva", 293},
    {"Sibiu", 209},
    {"Brasov", 133},
    {"TarguMures", 272},
    {"Tulcea", 226},
    {"PiatraNeamt", 271},
    {"Buzau", 93},
    {"Bacau", 238},
    {"Focsani", 158},
    {"Braila", 172},
    {"Constanta", 205}};

vector<neighbour> neighbours(string node)
{
    vector<neighbour> neighboursList;
    vector<string> destinationStack;

    int f = 0, g = 0, h = 0;
    for (distancePair el : distances)
    {
        vector<int> values;
        if (el.first.first == node)
        {
            h = heuristics[el.first.second];

            g = el.second;
            f = g + h;

            values.push_back(f);
            values.push_back(g);
            values.push_back(h);

            bool isOk = true;
            if (find(wrongPath.begin(), wrongPath.end(), el.first.second) != wrongPath.end())
                isOk = false;
            if (isOk)
                neighboursList.push_back(make_pair(el.first.second, values));
        }
        else if (el.first.second == node)
        {
            h = heuristics[el.first.first];

            g = el.second;
            f = g + h;

            values.push_back(f);
            values.push_back(g);
            values.push_back(h);

            bool isOk = true;
            if (find(wrongPath.begin(), wrongPath.end(), el.first.first) != wrongPath.end())
                isOk = false;
            if (isOk)
                neighboursList.push_back(make_pair(el.first.first, values));
        }
    }
    return neighboursList;
}
vector<string> destinationStack;
void SMA(string start)
{
    int currentDistance = 0, memoryBound = 5;

    string currentNode = start, end = "Bucuresti";
    destinationStack.push_back(currentNode);
    isReached[currentNode] = true;

    while (currentNode != end)
    {
        int minF = MIN_DISTANCE;
        neighbours(currentNode);

        for (neighbour city : neighbours(currentNode))
        {
            int currentF = city.second.at(0);
            if (minF > currentF)
                minF = currentF;
        }
        if (!neighbours(currentNode).size())
        {
            currentDistance = 0;
            break;
        }
        for (neighbour city : neighbours(currentNode))
        {
            if (minF == city.second.at(0))
            {
                isReached[currentNode] = true;
                if (destinationStack.size() == memoryBound)
                {
                    if (city.first == end)
                    {
                        currentNode = city.first;
                        currentDistance += city.second.at(1);
                        destinationStack.push_back(currentNode);
                    }
                    else if (city.first != end || !neighbours(city.first).size())
                    {
                        wrongPath.push_back(city.first);
                        string previousNode = destinationStack[destinationStack.size() - 1];
                        int lastDistance = 0;
                        for (auto el : distances)
                        {
                            if (el.first.first == currentNode && el.first.second == previousNode)
                                lastDistance = el.second;
                            else if (el.first.second == currentNode && el.first.first == previousNode)
                                lastDistance = el.second;
                        }
                        destinationStack.pop_back();
                        previousNode = destinationStack[destinationStack.size() - 1];
                        currentNode = previousNode;
                        currentDistance -= lastDistance;
                    }
                }
                else
                {
                    if (!neighbours(city.first).size())
                    {
                        wrongPath.push_back(city.first);
                        string previousNode = destinationStack[destinationStack.size() - 1];
                        int lastDistance = 0;
                        for (auto el : distances)
                        {
                            if (el.first.first == currentNode && el.first.second == previousNode)
                                lastDistance = el.second;
                            else if (el.first.second == currentNode && el.first.first == previousNode)
                                lastDistance = el.second;
                        }
                        destinationStack.pop_back();
                        previousNode = destinationStack[destinationStack.size() - 1];
                        currentNode = previousNode;
                        currentDistance -= lastDistance;
                    }
                    else
                    {
                        currentNode = city.first;
                        currentDistance += city.second.at(1);
                        destinationStack.push_back(currentNode);
                    }
                }
            }
        }

        neighbours(currentNode).clear();
    }
    if (currentDistance > 0)
    {
        cout << "The path between " << start << " and " << end << " is: ";
        for (int i = 0; i < destinationStack.size(); i++)
        {
            if (i != destinationStack.size() - 1)
                cout << destinationStack.at(i) << " -> ";
            else
                cout << destinationStack.at(i) << endl;
        }
        cout << "The distance is: " << currentDistance << " km";
    }
    else
        cout << "No path found between " << start << " and " << end << " with the maximum length of " << memoryBound;
}

int main()
{
    string start, end = "Bucuresti";
    cout << "Where are you now? ";
    cin >> start;
    SMA(start);
    return 0;
}