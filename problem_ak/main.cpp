#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

static vector< vector<int> > results;

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

    bool isOrigin()
    {
	return _parents.size() == 0;
    }

    bool isExit()
    {
	return _children.size() == 0;
    }

    vector<Node*> getChildren()
    {
	return _children;
    }

    vector<Node*> getParents()
    {
	return _parents;
    }

private:
    vector<Node*> _parents;
    vector<Node*> _children;
    int _id;
};

bool containsNode(vector<Node*>& nodes, Node* node)
{
    for(auto nodes_it = nodes.begin(); nodes_it != nodes.end(); nodes_it++)
        if((*nodes_it) == node)
	    return true;

    return false;
}

// Algorithm to recursively search network for paths
void depthFirst(vector<Node*>& visited, Node* end)
{
    Node* back = visited.back();

    vector<Node*> adjNode = back->getChildren();

    // Examine adjacent nodes
    for(auto node_it = adjNode.begin(); node_it != adjNode.end(); ++node_it)
    {
	Node* node = (*node_it);

        if(containsNode(visited, node))
	    continue;

        if(node == end)
        {
            visited.push_back(*node_it);
                        
            int hops = (int) visited.size();        
	    vector<int> path;

            for(int i = 1; i < hops - 1; ++i)
		path.push_back(visited[i]->getId());
	    results.push_back(path);
                                
            int n = (int) visited.size() - 1;
            visited.erase(visited.begin() + n);

            break;
        }           
    }

    for(auto node_it = adjNode.begin(); node_it != adjNode.end(); ++node_it)
    {
        Node* node = (*node_it);

        if(containsNode(visited, node) || node == end)
            continue;
        
        visited.push_back(node);

        depthFirst(visited, end);        

        int n = (int) visited.size() - 1;               
        visited.erase(visited.begin() + n);
    }       
}

int main() 
{
    map<int, Node*> network;

    int nbNodes, idA, idB;
    cin >> nbNodes;

    // These are 2 nodes I create just so I don't have to call
    // the search function with multiple different origin and end nodes
    Node* head = new Node(0);
    Node* tail = new Node(nbNodes + 1);

    for(int i = 0; i < nbNodes - 1; ++i)
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

    // Add origin nodes as children of the head node, but do not add the latter as their parent
    // So we'll still know they are origin nodes
    // Add tail node as child of exit nodes for same reasons.
    for(int i = 1; i <= nbNodes; ++i)
    {
	if(network[i]->isOrigin())
	    head->addChild(network[i]);
	else if(network[i]->isExit())
	    network[i]->addChild(tail);
    }

    // Find all paths and store in results
    vector<Node*> visited; 
    visited.push_back(head);
    depthFirst(visited, tail);

    // Find all nodes that are present in all of these paths
    map<int, int> bottlenecks;
    for(int i = 1; i <= nbNodes; ++i)
	bottlenecks[i] = 0;

    for(int i = 0; i < results.size(); ++i)
	for(int j = 0; j < results[i].size(); ++j)
	    ++bottlenecks[results[i][j]];
    
    // These nodes will be the bottlenecks (aka answers to the problem)
    for(int i = 1; i <= nbNodes; ++i)
	if(bottlenecks[i] == results.size())
	    cout << i << endl;
    
    return 0;
}
