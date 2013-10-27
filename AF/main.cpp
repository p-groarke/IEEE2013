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

using namespace std;

bool contains(int a, char n)
{
	return std::to_string(a).find(n) != std::string::npos;
}

int main() {

	int N;
	cin >> N;

	int* nbs = new int[N];
	map<int, int> results;
	int founds = 0;

	for(int i = 0; i < N; ++i)
	{
		int nb;
		cin >> nb;
		nbs[i] = nb;
		
	}

	int pos = 1;
	int nb = 1;

	int dir = 1;

	while(founds < N)
	{
		for(int i = 0; i < N; ++i)
			if(nbs[i] == nb)
			{
				results[nbs[i]] = pos;
				++founds;
			}

		if(nb % 7 == 0 || contains(nb, '7'))
			dir *= -1;

		++nb;
		pos += dir;

		if(pos < 1)
			pos = 1337;
		else if(pos > 1337)
			pos = 1;
	}

	for(auto x : results)
		cout << x.second << endl;

}

