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

	int N, max = 0, vit = 0;

	string input;
	getline(cin, input);
	N = atoi(input.c_str());
	
	getline(cin, input);

	istringstream buf(input);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end); 

	vector<int> dist;
	for(int i = 0; i < tokens.size(); ++i)
		dist.push_back(atoi(tokens[i].c_str()));

	for(int i = 0; i < dist.size(); ++i)
	{
		vit += dist[i];
		if(vit > max)
			max = vit;

		if(vit < 0)
			vit = 0;
	}

	cout << vit;

}

