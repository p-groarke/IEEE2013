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

    Block(int p, int x, int y)
    {
        posX = x;
        posY = y;
        danger = p;
        weight = numeric_limits<int>::max();
    }

    ~Block()
    {

    }

    void addConnection(Block* block)
    {
        connections.push_back(block);
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

    vector<Block*> getConnections()
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
    vector<Block*> connections;

};

void dijkstra(Block* startingNode, Block* endNode, map< pair<int,int>, Block*> network);

int height, width;

int main(int argc, const char * argv[])
{
    map< pair<int,int>, Block*> montagne;

    Block* noeudDepart = new Block(0, 0, -2);
    Block* noeudArriver = new Block(0, 0, -1);

	montagne[noeudArriver->getId()] = (noeudArriver);

    

    cin >> height >> width;

    for (int i = 0; i < height; ++i) //Y
    {
        for (int y = 0; y < width; ++y) //X
        {
            int temp;
            cin >> temp;

            Block* block_ = new Block(temp, y, i);

            if (i == 0) block_->addConnection(noeudArriver);

            else
            {
                for (auto x: montagne)
                {
                    // Higher?
					if (x.second->getY() == i - 1)
                    {
                        // Pas faire la gauche max
                        if (y - 1 >= 0 && x.second->getX() == y - 1) 
							block_->addConnection(x.second);
                        else if (x.second->getX() == y) 
							block_->addConnection(x.second);
                        else if (y + 1 < width && x.second->getX() == y + 1) 
							block_->addConnection(x.second);
                    }
                }
            }

			montagne[block_->getId()] = block_;
        }
    }

    // Connecter noeudDepart
    for (auto x: montagne)
    {
		if (x.second->getY() == height - 1) 
			noeudDepart->addConnection(x.second);
    }

	montagne[noeudDepart->getId()] = noeudDepart;

	dijkstra(noeudDepart, noeudArriver, montagne);
    return 0;
}


void dijkstra(Block* startingNode, Block* endNode, map< pair<int,int>, Block*> network)
{
	map< pair<int,int>, Block*> copy = network;

    map< pair<int,int>, int> distance; // distance from source node, by ID
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
		vector< Block* > links = currentNode->getConnections();
		reverse(links.begin(), links.end());

		for(int i = links.size() - 1; i >= 0; --i)
        {
            Block* currentNeighbor = links[i];

            // Make sure the neighbor hasn't already been removed from network
            bool neighborRemoved = network.count(currentNeighbor->getId()) == 0;

            if(!neighborRemoved)
            {
				int newDistance = distance[currentNode->getId()] + currentNode->getDanger();

                if(newDistance < distance[currentNeighbor->getId()])
                {
                    distance[currentNeighbor->getId()] = newDistance;
                    previous[currentNeighbor->getId()] = currentNode;
                }
            }
        }
    }

    if(previous[endNode->getId()] == NULL)
            cout << "Les noeuds ne sont pas relies." << endl;
    else
    {
		pair<int, int> currentId = endNode->getId();

        cout << "Minimum risk path = ";

        while(previous[currentId] != NULL)
        {
			if(currentId != endNode->getId() && currentId != startingNode->getId())
				cout << "[" << currentId.first << "," << currentId.second << "]";
            currentId = previous[currentId]->getId();
        }

		cout << endl << "Risks along the path = " << distance[endNode->getId()] << endl;
    }
}

/*

if (noeudCourant->getPoids() == infinity)
                cout << endl << "Aucun chemin trouver..." << endl;

            else
            {
                Block* fin = noeudCourant;
                cout << "Minimum risk path = ";

                int risk = 0;

                while (fin != 0)
                {
                    if (fin != noeudArriver && fin != noeudDepart)
                    {
                        cout << "[" << fin->getY() << "," << fin->getX() << "]";
                        risk += fin->getDanger();
                    }


                    fin = precedent[fin];
                }

                cout << endl << "Risks along the path = " << risk << endl;

*/