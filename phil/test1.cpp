#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    int N;
    vector<int> numList1, numList2, numList3, numList4, numList5, usedNums;

    cin >> N;

    // ATTENTION GUYS TRUIE CODE INCOMING!!!

    for (int i = 0; i < N; ++i)
    {
        int x;
        cin >> x;
        numList1.push_back(x);
    }
    for (int i = 0; i < N; ++i)
    {
        int x;
        cin >> x;
        numList2.push_back(x);
    }
    for (int i = 0; i < N; ++i)
    {
        int x;
        cin >> x;
        numList3.push_back(x);
    }
    for (int i = 0; i < N; ++i)
    {
        int x;
        cin >> x;
        numList4.push_back(x);
    }
    for (int i = 0; i < N; ++i)
    {
        int x;
        cin >> x;
        numList5.push_back(x);
    }

    // Init vector final
    vector<int> finalList;
    for (int i = 0; i < N; ++i)
    {
        finalList.push_back(0);
    }


    for (int i = 0; i < N; ++i)
    {
        if (numList5[i] != numList4[i])
        {
            usedNums.push_back(numList5[i]);
            break;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        if (numList4[i] != numList3[i])
        {
            usedNums.push_back(numList4[i]);
            break;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        if (numList3[i] != numList2[i])
        {
            usedNums.push_back(numList3[i]);
            break;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        if (numList2[i] != numList1[i])
        {
            usedNums.push_back(numList2[i]);
            break;
        }
    }

    // Need to reverse numList1 because for loop goes in correct direction
    reverse(numList1.begin(), numList1.end());

    for (auto x: numList1)
    {
        if (find(usedNums.begin(), usedNums.end(), x) == usedNums.end()) usedNums.push_back(x);
    }

    reverse(usedNums.begin(), usedNums.end());


    // C++11 marche pour la competition yay
    for (auto x: usedNums)
        cout << x << endl;


    return 0;
}
