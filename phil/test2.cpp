#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int N;
    cin >> N;

    vector<int> ints;

    for(int i = 0; i < N; ++i)
    {
        string str;
        if(getline(std::cin, str))
        {
            istringstream sstr(str);
            int n;
            while(sstr >> n)
                ints.push_back(n);
        }
    }

    //Trouver nombre de variables
    int cas = ints.size()/N;


return 0;
}
