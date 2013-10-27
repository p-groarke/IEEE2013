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
#include <limits>
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















int main(int argc, const char * argv[])
{
    vector<Block*> montagne;

    Block* noeudDepart = new Block(0, 0, -1);
    Block* noeudArriver = new Block(0, 0, -1);

    montagne.push_back(noeudArriver);

    int height, width;

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
                    if (x->getY() == i - 1)
                    {
                        // Pas faire la gauche max
                        if (y - 1 >= 0 && x->getX() == y - 1) block_->addConnection(x);
                        else if (x->getX() == y) block_->addConnection(x);
                        else if (y + 1 < width && x->getX() == y + 1) block_->addConnection(x);
                    }
                }
            }

            montagne.push_back(block_);
        }
    }

    // Gosser les valeurs de y = max
//    for (int i = 0; i < montagne.size(); ++i)
//    {
//        int lowest = 1000000;
//        if (montagne[i]->getY() == height - 1)
//        {
//            if (montagne[i]->getDanger() < lowest) lowest = montagne[i]->getDanger();
//            if (i + 1 < montagne.size() && montagne[i + 1]->getDanger() == lowest)
//            {
//                montagne[i + 1]->setDanger(montagne[i + 1]->getDanger() + 1);
//            }
//        }
//    }

    // Connecter noeudDepart
    for (auto x: montagne)
    {
        if (x->getY() == height - 1) noeudDepart->addConnection(x);
    }

    montagne.push_back(noeudDepart);






    // Djikstra



    // Initialezer
    int infinity = numeric_limits<int>::max();

    vector<Block*> unvisited;
    map<Block*, Block*> precedent; //Noeud precedant, Noeud courant

    for (auto x: montagne)
    {
        unvisited.push_back(x);
    }

    // Distance du noeud de depart a 0
    for (auto x: unvisited)
    {
        if (x == noeudDepart)
        {
            x->setPoids(0);
            precedent[x] = 0;

            vector<Block*> temp = x->getConnections();

//            sort(temp.begin(), temp.end(), [](Block* b1, Block* b2)
//            {
//                return b1->getX() < b2->getX();
//            });

            for (auto y: temp)
            {
                y->setPoids(y->getDanger());
                precedent[y] = x;
            }

            unvisited.erase(find(unvisited.begin(), unvisited.end(), x));

			break;
        }
    }

    Block* noeudPrecedant = noeudDepart;
    Block* noeudCourant = noeudDepart;

//    sort(unvisited.begin(), unvisited.end(), [](Block* b1, Block* b2)
//         {
//             return b1->getX() > b2->getX();
//         });

    while (unvisited.size() != 0)
    {
        noeudCourant = unvisited[0];


        // Trouver noeud avec le poids plus petit.
        for (auto x: unvisited)
        {
            if (x->getPoids() == noeudCourant->getPoids() &&
                x->getX() < noeudCourant->getX())
            {
                noeudCourant = x;
            }

            else if (x->getPoids() < noeudCourant->getPoids())
            {
                noeudCourant = x;
            }
        }

        noeudPrecedant = precedent[noeudCourant];

        // Unlever le noeud
        unvisited.erase(find(unvisited.begin(), unvisited.end(), noeudCourant));

        if (noeudCourant == noeudArriver)
        {
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

                break;
            }
        }


        vector<Block*> temp = noeudCourant->getConnections();
        //reverse(temp.begin(), temp.end());

        for (auto x: temp)
        {
            if (noeudCourant->getPoids() + noeudPrecedant->getPoids() < x->getPoids())
            {
                x->setPoids(noeudCourant->getPoids() + x->getDanger());
                precedent[x] = noeudCourant;
            }


            else if (noeudCourant->getPoids() + noeudPrecedant->getPoids() == x->getPoids())
            {
                if (noeudCourant->getX() < precedent[x]->getX())
                {
                    precedent[x] = noeudCourant;
                }
            }


        }
    }

    return 0;
}

