#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <map>
#include <climits>
#include <list>

using namespace std;

bool ContainsNode( std::vector<int>& nodes, int node );

class Link
{
public:

    Link( int source, int target ) 
    {        
    sourceNode = source;
    targetNode = target;        
    }
    
    void GetSourceTargetNodes( int& source, int& target )
    {
    source = sourceNode;
    target = targetNode;
    }
    
protected:
    int sourceNode;
    int targetNode;
};

class Network
{
private:
        
    std::map< std::pair<int,int>, Link*> link_map;        
    bool bi_direction;    

public:

    Network();
    ~Network();

    void Reset();    
    void SetBiDirection( bool bi );            
    void AddLink( Link* l );
    void AddLink( int s, int d );

    bool LinkExists( int sourceID, int targetID );
    bool BiDirectional();

    std::vector< int > GetAdjNodeIDs( int n );                 
};

Network::Network()
{
    bi_direction = true;
}

Network::~Network()
{
    Reset();
}

// Re-set all the network data
void Network::Reset()
{   
    // Delete the link pointers
    for ( map< std::pair<int,int>, Link*>::iterator it = link_map.begin(); 
          it != link_map.end(); 
          it++ )
    {
        Link* l = (*it).second;
        delete l;
        l = NULL;
    }

    link_map.erase ( link_map.begin(), link_map.end() );    
}



void Network::AddLink( Link* l )
{   
    // update one-to-one mapping between each link added
    // and its unique node pair

    int s, d;
    l->GetSourceTargetNodes( s, d );
    std::pair<int,int> p( s, d );
    link_map[ p ] = l;
}



void Network::AddLink(int s, int d )
{   
    if ( !LinkExists( s, d ) )
    {
        AddLink( new Link( s, d ) );
    }
}

bool Network::LinkExists( int sourceID, int targetID )
{
    bool found = false;

    std::map< std::pair<int,int>, Link* >::iterator it1, it2;

    std::pair<int,int> p1( sourceID, targetID );
    std::pair<int,int> p2( targetID, sourceID );

    it1 = link_map.find( p1 );

    // Condition for bi-directional (full duplex) links
    if ( BiDirectional() )
    {
        it2 = link_map.find( p2 );
        found = it1 != link_map.end() ||
                it2 != link_map.end();      
    }
    // Otherwise directed links
    else
    {       
        found =  it1 != link_map.end();
    }

    return found;
}



std::vector< int > Network::GetAdjNodeIDs( int n )
{
    vector< int > adj;

    std::map< std::pair<int,int>, Link* >::iterator link_it = 
        link_map.begin();

    for ( ;
          link_it != link_map.end();
          link_it++ )
    {
        int start  = -1;
        int target = -1;

        Link* l = (*link_it).second;

        l->GetSourceTargetNodes( start, target );        

        if ( LinkExists( start, target ) )
        {
            if ( BiDirectional() && ( start == n || target == n ) )
            {
                adj.push_back( start == n ? target : start );
            }
            else if ( start == n )
            {
                adj.push_back( target );
            }
        }
    }
                
    return adj;
}


bool Network::BiDirectional()
{
    return bi_direction;
}


// Set bi-directional status of network links
void Network::SetBiDirection( bool bi )
{
    bi_direction = bi;
}

const int size = 5;

bool ContainsNode( std::vector<int>& nodes, int node )
{
    std::vector<int>::const_iterator nodes_it;

    for ( nodes_it = nodes.begin();
          nodes_it != nodes.end();
          nodes_it++ )
    {
        if ( (*nodes_it) == node ) return true;
    }

    return false;
}

static vector< vector<char> > results;


// Algorithm to recursively search network for paths
void DepthFirst( Network* network, 
                std::vector<int>& visited, 
                int end )
{
    int back = visited.back();

    std::vector< int > adjNode = network->GetAdjNodeIDs( back );

    // Examine adjacent nodes
    for ( std::vector<int>::iterator node_it = adjNode.begin();
          node_it != adjNode.end();
          node_it++ )
    {   
        int node = (*node_it);

        if ( ContainsNode( visited, node ) ) 
			continue;

        if ( node == end )
        {
            visited.push_back( *node_it );
                        
            int hops = (int) visited.size();        
			vector<char> path;

            for ( int i = 0; i < hops; i++ )
				path.push_back((char)visited[ i ]);
			results.push_back(path);
                                
            int n = (int) visited.size() - 1;
            visited.erase( visited.begin() + n );

            break;
        }           
    }


    // in breadth-first, recursion needs to come after visiting adjacent nodes
    for ( std::vector<int>::iterator node_it = adjNode.begin();
          node_it != adjNode.end();
          node_it++ )
    {
        int node = (*node_it);

        if ( ContainsNode( visited, node ) || node == end )     
            continue;
        
        visited.push_back( node );

        DepthFirst( network, visited, end );        

        int n = (int) visited.size() - 1;               
        visited.erase( visited.begin() + n );
    }       
}

int main() 
{
	Network nw;

    nw.SetBiDirection( true );

	char target;
	string input;
	getline(cin, input);
	target = input[0];

	while(cin.good())
	{
		char id1, id2;
		cin >> id1;
		cin >> id2;

		if( id1 >= 'F' && id1 <= 'Z' && id2 >= 'F' && id2 <= 'Z')
			nw.AddLink(id1, id2);
		
	}
	
	std::vector<int> visited; 
    visited.push_back( 'F' );
    DepthFirst( &nw, visited, target );

	if(results.size() == 0)
	{
		cout << "No Route Available from F to Z" << endl;
		return 0;
	}

	int min = INT_MAX;
	int minIndex = 0;
	for(int i = 0; i < results.size(); ++i)
		if(results[i].size() < min)
		{
			minIndex = i;
			min = results[i].size();
		}
			
	vector<char> path = results[minIndex];

	string result;
	for(int i = 0; i < path.size(); ++i)
	{
		result += " ";
		result += path[i];
	}


	cout << "Total Routes: " << results.size() << endl;
	cout << "Shortest Route Length: " << min << endl;
	cout << "Shortest Route after Sorting of Routes of length " << min << ":" << result << endl;

    return 0;
}