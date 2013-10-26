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

    string input;

    getline(cin, input);

    istringstream buf(input);
    istream_iterator<string> beg(buf), end;
    vector<string> tokens(beg, end);

    // Convertir de hex a dec
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i] == "+" || tokens[i] == "-"
            || tokens[i] == "&" || tokens[i] == "|"
            || tokens[i] == "~" || tokens[i] == "X")
        {
            // Do nothing, operator not number
        }
        else
        {
            tokens[i] = to_string(strtol(tokens[i].c_str(), NULL, 16));
            //cout << tokens[i] << endl;
        }
    }

    for(int i = 0; i < tokens.size(); ++i)
    {
        // If it's a number simply push it on the stack
        if(isdigit(tokens[i].c_str()[0]))
            intStack.push(atoi(tokens[i].c_str()));
        else // Else it's an operator, so just do that shit man
        {
            int result;
            
            if(tokens[i].c_str()[0] == '~') // Only unary operator
            {
                if(intStack.size() < 1)
                {
                    cout << "ERROR" << endl;
                    return 0;
                }

                result = ~(intStack.top());
                intStack.pop();
            }
            else // All binary operators
            {
                if(intStack.size() < 2)
                {
                    cout << "ERROR" << endl;
                    return 0;
                }

                int right = intStack.top();
                intStack.pop();
                int left = intStack.top();
                intStack.pop();
                
                switch(tokens[i].c_str()[0])
                {
                case '+':
                    result = left + right;
                    break;
                case '-':
                    result = left - right;
                    break;
                case '&':
                    result = left & right;
                    break;
                case '|':
                    result = left | right;
                    break;
                case 'X':
                    result = left ^ right;
                    break;
                default:
                    cout << "ERROR" << endl;
                    return 0;
                }
            }

            if(result < 0)
                result = 0;
            else if(result > 65535)
                result = 65535;

            intStack.push(result);
        }
    }

    cout << setw(4) << setfill('0') << uppercase << hex << (int)intStack.top();
    return 0;
}
