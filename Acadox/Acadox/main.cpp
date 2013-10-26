//
//  main.cpp
//  Acadox
//
//  Created by Philippe Groarke on 2013-10-25.
//  Copyright (c) 2013 Groarke and co. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <string>
#include <sstream>
#include <iterator>
#include <cctype>
#include <iomanip>

using namespace std;


int main(int argc, const char * argv[])
{

    stack<int> intStack;
    stack<string> stringStack;

    string input;

    getline(cin, input);

//    stringstream ss;
//    ss << hex << input;
//    cout << dec << ss.str() << endl;

    istringstream buf(input);
    istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);

//    for (auto x: tokens)
//    {
//        cout << x << endl;
//    }



    // Convertir en hex
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i] == "+" || tokens[i] == "-"
            || tokens[i] == "&" || tokens[i] == "|"
            || tokens[i] == "~" || tokens[i] == "X")
        {
        }
        else
        {
            tokens[i] = to_string(strtol(tokens[i].c_str(), NULL, 16));
            //cout << tokens[i] << endl;
        }
    }

    // Creer un stack pour pas gerer de compteur
    for(int i = tokens.size() - 1; i >= 0; --i)
    {
        stringStack.push(tokens[i]);
    }

//    for (int i = 0; i < tokens.size(); ++i)
//    {
//        cout << stringStack.top() << endl;
//        stringStack.pop();
//    }


    while (stringStack.size() != 0)
    {
        if(!stringStack.top().compare("+"))
        {
            stringStack.pop();
            int num2 = intStack.top();
            intStack.pop();
            int num1 = intStack.top();
            intStack.pop();
            intStack.push(num1 + num2);
        }

        else if(!stringStack.top().compare("-"))
        {
            stringStack.pop();
            int num2 = intStack.top();
            intStack.pop();
            int num1 = intStack.top();
            intStack.pop();
            intStack.push(num1 - num2);
        }

        else if(!stringStack.top().compare("&"))
        {
            stringStack.pop();
            int num2 = intStack.top();
            intStack.pop();
            int num1 = intStack.top();
            intStack.pop();
            intStack.push(num1 & num2);
        }

        else if(!stringStack.top().compare("|"))
        {
            stringStack.pop();
            int num2 = intStack.top();
            intStack.pop();
            int num1 = intStack.top();
            intStack.pop();
            intStack.push(num1 | num2);
        }

        else if(!stringStack.top().compare("~"))
        {
            stringStack.pop();
            int num1 = intStack.top();
            intStack.pop();
            intStack.push(~num1);
        }

        else if(!stringStack.top().compare("X"))
        {
            stringStack.pop();
            int num2 = intStack.top();
            intStack.pop();
            int num1 = intStack.top();
            intStack.pop();
            intStack.push(num1 ^ num2);
        }

        else if(isdigit(stringStack.top().c_str()[0]))
        {
            intStack.push(atof(stringStack.top().c_str()));
            stringStack.pop();
        }

    }


    cout << setw(4) << setfill('0') << hex << (int)intStack.top();


    return 0;
}
