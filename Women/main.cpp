#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>

using namespace std;

int main() {

	double a1 = 2.7 / 3600 * 1000;
	double a3 = -3.8 / 3600 * 1000;
	
	double vmax = 25;

	double t1max = vmax * a1;
	double d1max = t1max*t1max * a1 / 2;

	double t3max = -1 * vmax * a3;
	double d3max = t3max*t3max * a3 / 2 + vmax * t3max;

    string input = "5 1000 500 98500";
	//getline(cin, input);

	istringstream buf(input);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end); 

	int nbTrains = atoi(tokens[0].c_str());
	if(tokens.size() - 1 > 5 || tokens.size() - 1 < 1 || nbTrains > 5 || nbTrains < 1)
	{
		cout << "ERROR";
		return 0;
	}

	vector<int> dist;
	int nbStations = tokens.size() - 1;
	for(int i = 1; i < tokens.size(); ++i)
		dist.push_back(atoi(tokens[i].c_str()));

	int sum = 0;
	for(int i = 0; i < dist.size(); ++i)
		sum += dist[i];

	if(sum != 100000)
	{
		cout << "ERROR";
		return 0;
	}

	for(int i = 0; i < dist.size(); ++i)
		if(dist[i] < 500)
		{
			cout << "ERROR";
			return 0;
		}

	double dep[5][5];
	double arr[5][5];

	for(int i = 0; i < nbTrains; ++i)
	{
		for(int j = 0; j < nbStations; ++j)
		{
			//departure of station
			if(j == 0)
			{
				if(i == 0)
					dep[0][0] = 1;
				else
					dep[i][0] = dep[i - 1][1] + 1;
			}
			else
			{
				if(i == 0)
				{
					dep[0][j] = arr[0][j - 1] + 120 + 1;
				}
				else
				{
					if(arr[i][j-1] + 120 > arr[i-1][j])
						dep[i][j] = arr[i][j-1] + 120 + 1;
					else
						dep[i][j] = arr[i-1][j] + 1;
				}
			}

			//arrival of station

			arr[i][j] = dep[i][j] + t1max + t3max + (dist[j] - d1max - d3max) / vmax;
			if(j == nbStations - 1)
				arr[i][j]++;
		}
	}

	for(int i = 0; i < nbTrains; ++i)
	{
		cout << (i+1) << " : *****";
			for(int j = 0; j < nbStations; ++j)
			{
				cout << " - " << setw(5) << right << floor(dep[i][j]);
				cout << "  ";
				cout << setw(5) << right << floor(arr[i][j]); 
			}
		cout << " *****" << endl;
	}

    return 0;
}