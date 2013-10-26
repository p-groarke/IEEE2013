#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>


#include <unistd.h>
#include <signal.h>

using namespace std;

class Node
{
public:
    Node(int id)
    : _id(id)
    {
    }

    void addParent(Node* parent)
    {
        _parents.push_back(parent);
    }

    void addChild(Node* child)
    {
        _children.push_back(child);
    }

    vector<Node*> getChilds()
    {
        return _children;
    }

    vector<Node*> getParents()
    {
        return _parents;
    }

    int getId() const
    {
        return _id;
    }

    int getLevel()
    {
        return level_;
    }

    void setLevel(int lev)
    {
        level_ = lev;
    }

private:
    vector<Node*> _parents;
    vector<Node*> _children;
    int _id;
    int level_;
};









int main()
{





    //Wait for debugger to attach
    //kill(getpid(), SIGSTOP);

    // Pipe inside tool instead
    //(void) freopen("/path/to/file", "r", stdin);







    map<int, Node*> network;
    vector<int> levels;
    int nbNodes, idA, idB;
    cin >> nbNodes;


    int levelCourant = 0;

    for(int i = 0; i < nbNodes; ++i)
    {
        cin >> idA >> idB;
        Node* nodeA;
        Node* nodeB;

        // Changer de niveau? Si je le trouve
        if (find(levels.begin(), levels.end(), idA) != levels.end())
        {
            ++levelCourant;
        }

        // Levels (si je le trouve pas rajoute)
        if (find(levels.begin(), levels.end(), idB) == levels.end())
        {
            levels.push_back(idB);
        }




        if(network.count(idA) != 0)
        {
            nodeA = network[idA];
        }
        else
        {
            nodeA = new Node(idA);
            nodeA->setLevel(levelCourant);
            network[idA] = nodeA;
        }
        
        if(network.count(idB) != 0)
        {
            nodeB = network[idB];
        }
        else
        {


            nodeB = new Node(idB);
            nodeB->setLevel(levelCourant + 1);
            network[idB] = nodeB;
        }



        nodeA->addParent(nodeB);
        nodeB->addChild(nodeA);
    }

    // Get all origin nodes
    // ?Maybe get all exit nodes
    // Find all paths that start from origin node and end on exit node
    // Find all nodes that are present in all of these paths which aren't exit nodes
    // These nodes will be the bottlenecks (aka answers to the problem)


    map<int, vector<Node*>> networkParNiveau;

    for (auto x : network)
    {
        networkParNiveau[x.second->getLevel()].push_back(x.second);
    }


    vector<Node*> bottleNecks;

    Node* semblable = networkParNiveau[0].front();

    bool isBottle = true;

    // Checker niveau 1 si toute pareil (crosse)
    for (auto x : networkParNiveau[0])
    {
        if (x != semblable)
        {
            isBottle = false;
            break;
        }
    }

    if (isBottle) bottleNecks.push_back(semblable);

    for (int i = 0; i < networkParNiveau.size(); ++i)
    {
        Node* parent = 0;
        bool bottleNeck = true;

        for (auto x : networkParNiveau[i])
        {
            for (auto y : x->getParents())
            {
                if (y != parent && parent == 0)
                {
                    parent = y;

                }
                if (y != parent && parent != 0)
                {
                    bottleNeck = false;
                    break;
                }
            }

            if (bottleNeck == false) break;

        }

        if (bottleNeck == true)
        {
            if (parent != 0)
                bottleNecks.push_back(parent);
        }
    }

    sort(bottleNecks.begin(), bottleNecks.end());

    for (auto x : bottleNecks)
    {
        cout << x->getId() << endl;
    }

    return 0;
}
