//
//  main.cpp
//  Problem_AM
//
//  Created by Philippe Groarke on 2013-10-26.
//  Copyright (c) 2013 Groarke and co. All rights reserved.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <map>

using namespace std;

class Block {
public:
    Block()
    {
        danger = 0;
        weight = numeric_limits<int>::max();
    }

    Block( int x, int y, int type)
    {
        posX = x;
        posY = y;

		danger = 0;

        weight = numeric_limits<int>::max();
    }

    ~Block()
    {

    }

    void addConnection(Block* block, double cost)
    {
		connections.push_back(make_pair(block, cost));
    }

    void setPoids(const int w)
    {
        weight = w;
    }

    void setDanger(const int d)
    {
        danger = d;
    }

    int getX() const
    {
        return posX;
    }
    int getY() const
    {
        return posY;
    }

	pair<int, int> getId()
	{
		return make_pair(posY, posX);
	}

    vector< pair<Block*, double> > getConnections()
    {
        return connections;
    }

    int getPoids() const
    {
        return weight;
    }

    int getDanger() const
    {
        return danger;
    }

private:
    int posX, posY;
    int danger;
    int weight;
    vector< pair<Block*, double> > connections;

};

double dijkstra(Block* startingNode, Block* endNode, map< pair<int,int>, Block*> network);
void dijkstraCarre(Block* startingNode, Block* endNode, map< pair<int,int>, Block*> network);

int height, width;

int main(int argc, const char * argv[])
{
    map< pair<int, int>, Block*> desert;

    Block* noeudDepart = new Block(-1, -1, 'S');
    Block* noeudArriver = new Block(-2, -1, 'E');

	vector< Block*> oasis;

    cin >> height >> width;

    for (int i = 0; i < height; ++i) //Y
    {
        for (int y = 0; y < width; ++y) //X
        {
            char type;
            cin >> type;

			Block* block_ = new Block(y, i, type);
			desert[block_->getId()] = block_;

			if(type == 'S')
				noeudDepart = block_;
			else if(type == 'E')
				noeudArriver = block_;
			else if(type == '+')
				oasis.push_back(block_);
        }
    }

	double result =  dijkstra(noeudDepart, noeudArriver, desert);
	if(result != INT_MAX)
	{
		cout << result;
        return 0;
	}

	for(int i = 0; i < oasis.size(); ++i)
	{
		double result =  dijkstra(noeudDepart, oasis[i], desert);
		if(result != INT_MAX)
		{
			noeudDepart->addConnection(oasis[i], result);
			oasis[i]->addConnection(noeudDepart, result);
		}
	}

	for(int i = 0; i < oasis.size(); ++i)
	{
		double result = dijkstra(oasis[i], noeudArriver, desert);
		if(result != INT_MAX)
		{
			noeudArriver->addConnection(oasis[i], result);
			oasis[i]->addConnection(noeudArriver, result);
		}
	}
	
	for(int i = 0; i < oasis.size(); ++i)
		for(int j = i + 1; j < oasis.size(); ++j)
		{
			double result = dijkstra(oasis[i], oasis[j], desert);
			if(result != INT_MAX)
			{
				oasis[j]->addConnection(oasis[i], result);
				oasis[i]->addConnection(oasis[j], result);
			}
		}

	dijkstraCarre(noeudDepart, noeudArriver, desert);

    return 0;
}

void dijkstraCarre(Block* startingNode, Block* endNode, map< pair<int,int>, Block*> network)
{
	map< pair<int,int>, Block*> copy = network;

    map< pair<int,int>, double> distance; // distance from source node, by ID
    map< pair<int,int>, Block*> previous; // id of node, pointer to previous node in path

    for(auto it = network.begin(); it != network.end(); ++it)
    {
        distance[it->first] = INT_MAX;
        previous[it->first] = NULL;
    }

    distance[startingNode->getId()] = 0;

    while(network.size() > 0)
    {
        // Find node with shortest distance yet
        Block* currentNode;
        pair<int,int> closestId;
        int shortestDistance = INT_MAX;

		/*for(int i = height - 1; i >= 0; --i)
		{
			for(int j = width - 1; j >= 0; --j)
			{
				if(network.count(make_pair(i, j)) != 0 && distance[make_pair(i, j)] <= shortestDistance)
				{
					closestId = make_pair(i, j);
					shortestDistance = distance[closestId];
				}
			}
		}*/

        for(auto it = network.begin(); it != network.end(); ++it)
        {
            if(distance[it->first] < shortestDistance)
            {
                closestId = it->first;
                shortestDistance = distance[closestId];
            }
        }

        currentNode = network[closestId];

        if(currentNode == endNode) // Destination reached
                break;

        // Remove the closest node from our local copy of the network
        auto it = network.find(closestId);
        network.erase(it);

        if(distance[closestId] == INT_MAX) // No existing path
                break;

        // Visit all wired neighbors of closestNode
		vector< pair<Block*, double> > links = currentNode->getConnections();
		reverse(links.begin(), links.end());

		for(int i = links.size() - 1; i >= 0; --i)
        {
			Block* currentNeighbor = links[i].first;

            // Make sure the neighbor hasn't already been removed from network
            bool neighborRemoved = network.count(currentNeighbor->getId()) == 0;

            if(!neighborRemoved)
            {
				double newDistance = distance[currentNode->getId()] + links[i].second;

                if(newDistance < distance[currentNeighbor->getId()])
                {
                    distance[currentNeighbor->getId()] = newDistance;
                    previous[currentNeighbor->getId()] = currentNode;
                }
            }
        }
    }

    if(previous[endNode->getId()] == NULL)
            cout << "IMPOSSIBLE";
    else
    {
		cout << distance[endNode->getId()];
		/*pair<int, int> currentId = endNode->getId();


        cout << "Minimum risk path = ";

        while(previous[currentId] != NULL)
        {
			double cost = 0;
			auto paths = copy[currentId]->getConnections();
			for(auto x : paths)
			{
				if(x.first == previous[currentId])
				{
					cost = x.second;
					break;
				}
					
			}

			cout << " /[" << currentId.second << "," << currentId.first << "] " << cost;
            currentId = previous[currentId]->getId();
        }

		double cost = 0;
		auto paths = copy[currentId]->getConnections();
		for(auto x : paths)
		{
			if(x.first == previous[currentId])
			{
				cost = x.second;
				break;
			}
					
		}
		cout << " /[" << currentId.second << "," << currentId.first << "] " << cost;
		cout << endl << "Risks along the path = " << distance[endNode->getId()] << endl;*/
    }
}

double dijkstra(Block* startingNode, Block* endNode, map< pair<int,int>, Block*> network)
{
	map< pair<int,int>, Block*> perfect = network;

    map< pair<int,int>, double> distance; // distance from source node, by ID
    map< pair<int,int>, Block*> previous; // id of node, pointer to previous node in path

    for(auto it = network.begin(); it != network.end(); ++it)
    {
        distance[it->first] = INT_MAX;
        previous[it->first] = NULL;
    }

    distance[startingNode->getId()] = 0;

    while(network.size() > 0)
    {
        // Find node with shortest distance yet
        Block* currentNode;
        pair<int,int> closestId;
        int shortestDistance = INT_MAX;

        for(auto it = network.begin(); it != network.end(); ++it)
        {
            if(distance[it->first] <= shortestDistance)
            {
                closestId = it->first;
                shortestDistance = distance[closestId];
            }
        }

        currentNode = network[closestId];

        if(currentNode == endNode) // Destination reached
                break;

        // Remove the closest node from our local copy of the network
        auto it = network.find(closestId);
        network.erase(it);

        if(distance[closestId] == INT_MAX) // No existing path
                break;

		for(int i = currentNode->getY() - 1; i <= currentNode->getY() + 1; ++i)
		{
			if(i < 0 || i >= height)
				continue;

			for(int j = currentNode->getX() - 1; j <= currentNode->getX() + 1; ++j)
			{
				if(j < 0 || j >= width)
					continue;

				if(i == currentNode->getY() && j == currentNode->getX())
					continue;

				Block* currentNeighbor = perfect[make_pair(i, j)];

				// Make sure the neighbor hasn't already been removed from network
				bool neighborRemoved = network.count(currentNeighbor->getId()) == 0;

				if(!neighborRemoved)
				{
					double newDistance = distance[currentNode->getId()];

					if(currentNode->getX() != currentNeighbor->getX() &&
						currentNode->getY() != currentNeighbor->getY())
						newDistance += 1.5;
					else
						newDistance += 1;

					if(newDistance < distance[currentNeighbor->getId()])
					{
						distance[currentNeighbor->getId()] = newDistance;
						previous[currentNeighbor->getId()] = currentNode;
					}
				}
			}
		}
    }

    if(previous[endNode->getId()] == NULL)
		return INT_MAX;
    else
    {
		/*pair<int, int> currentId = endNode->getId();

        cout << "Minimum risk path = ";

        while(previous[currentId] != NULL)
        {
			cout << "[" << currentId.first << "," << currentId.second << "]";
            currentId = previous[currentId]->getId();
        }
		cout << "[" << currentId.first << "," << currentId.second << "]";

		cout << endl << "Risks along the path = " << distance[endNode->getId()] << endl;*/

		if(distance[endNode->getId()] > 5)
			return INT_MAX;

		return distance[endNode->getId()];
    }
}