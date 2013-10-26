// Code for IEEEXtreme problem 3, computer society
// Copyright 2013 TeamFullOfLove
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define llong long long

using namespace std;

// Linear Congruential Generator, pseudo-random generator.
class LCG
{
public:
    static const llong m = 281474976710656; // modulus, 2^48
    static const int a = 1664525; // multiplier
    static const int c = 1013904223; // increment

    LCG(int seed) : _seed(seed), _previousX(seed)
    {
    }

    int generate()
    {
	int _currentX = a * _previousX + (c % m);
	_previousX = _currentX;
	return _currentX;
    }
    
    int generate(int min, int max)
    {
	generate();
	return abs((_previousX % max) + min);
    }
    
private:
    int _seed;
    int _previousX;
};


int main()
{    
    return 0;
}
