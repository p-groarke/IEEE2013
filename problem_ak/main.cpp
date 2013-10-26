#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

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
    map<int, Node*> network;
    int nbNodes, idA, idB;
    cin >> nbNodes;

    for(int i = 0; i < nbNodes; ++i)
    {
        cin >> idA >> idB;
        Node* nodeA;
        Node* nodeB;
        
        if(network.count(idA) != 0)
        {
            nodeA = network[idA];
        }
        else
        {
            nodeA = new Node(idA);
            network[idA] = nodeA;
        }
        
        if(network.count(idB) != 0)
        {
            nodeB = network[idB];
        }
        else
        {
            nodeB = new Node(idB);
            network[idB] = nodeB;
        }

        nodeA->addChild(nodeB);
        nodeB->addParent(nodeA);
    }

    // Get all origin nodes
    // ?Maybe get all exit nodes
    // Find all paths that start from origin node and end on exit node
    // Find all nodes that are present in all of these paths which aren't exit nodes
    // These nodes will be the bottlenecks (aka answers to the problem)


    
    return 0;
}
