#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int main() {
   
	/*int M;
	cin >> M;

	int N = 3;
	for(int i = 1; i < M; ++i)
		N *= 3;

	int i = 1;
	int s[11];
	for(int j = 0; j < M; ++j)
		s[j] = i;

	while(i)
	{
		if(s[i] - N)
		{
			++s[i];
			if(f(s, (s+i+1) - s, i + 1))
			{
				if(i < M - 1)
				{
					++i;
					s[i] = s[i-1];
				}
				else
					N = s[-1];
			}
		}
		else
			--i;
	}
	cout << N << endl;*/

	/*
	M=int(input())
	N=3**M
	i=1
	s=M*[i]
	while i:
		if s[i]-N:
			s[i]=s[i]+1
			if o(s[:i+1]):
				if i<M-1:
					i=i+1
					s[i]=s[i-1]
				else:
					N=s[-1]
		else:
			i=i-1
	print(N)*/ 

    return 0;
}


