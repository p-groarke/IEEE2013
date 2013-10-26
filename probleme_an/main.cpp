//
//  main.cpp
//  probleme_an
//
//  Created by Philippe Groarke on 2013-10-26.
//  Copyright (c) 2013 Groarke and co. All rights reserved.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>


#include <unistd.h>
#include <signal.h>

using namespace std;


vector<string> generatePermutations(vector<string> vec)
{
    vector<string> newVec;

    for (auto x : vec)
    {
        for (auto y : vec)
        {
            newVec.push_back(x+y);
        }
    }
    return newVec;
}


string decipherCaesar(string text, int k)
{
    for (int y = 0; y < k; ++y)
    {
        //cout << text << endl;

        for (int i = 0; i < text.length(); ++i)
        {

            ++text.at(i);

            if (text.at(i) == 91) text.at(i) -= 26;

        }
    }
    return text;
}



int main(int argc, const char * argv[])
{

    //Wait for debugger to attach
    kill(getpid(), SIGSTOP);

    // Pipe inside tool instead
    //(void) freopen("/path/to/file", "r", stdin);

    int blocklength = 1; //1 <= block <= 10
    map<int, int> blocklengthCandidates; //blocklength, weight

    map<int, int> k1Candidates;
    map<int, int> k2Candidates;
    map<int, int> k3Candidates;


    string code, input;
    int numWords;

    vector<string> tokens;

    getline(cin, code);

    getline(cin, input);

    cin >> numWords;

    for (int i = 0; i < numWords; ++i)
    {
        string temp;
        cin >> temp;
        tokens.push_back(temp);
    }

        //decipherCaesar(code);


    //vector<string> permutations = generatePermutations(tokens);

    map<char, int> poidsChars;

    for (auto x : tokens)
    {
        for (int i = 0; i < x.size(); ++i)
        {
            poidsChars[x[i]] += 1;
        }
    }

    int positionInSentence = 0;

    // blocklength
    for (int i = 1; i <= 10; ++i)
    {
        for (int k1 = 0; k1 < 26; ++k1)
        {
            string testString = decipherCaesar(code.substr(positionInSentence, i), k1);

            int stringWheight = 0;

            for (int i = 0; i < testString.size(); ++i)
            {
                stringWheight += poidsChars[testString[i]];
            }
            stringWheight /= testString.size();

            blocklengthCandidates[i] += stringWheight;
        }
    }




//
//    // Initial stuff (k1 and blocklength
//    for (int i = 1; i <= 10; ++i)
//    {
//        for (int k1 = 0; k1 < 26; ++k1)
//        {
//            string testString = decipherCaesar(code.substr(positionInSentence, i), k1);
//
//            for (auto x : permutations)
//            {
//
//                // Does it match a part of a word
//                if (!testString.compare(x.substr(0, testString.size())))
//                {
//                    cout << x.substr(0, testString.size()) << endl;
//                    blocklengthCandidates[i] += 1;
//                    k1Candidates[k1] += 1;
//                }
//            }
//        }
//    }



    // Check best k1

//    cout << endl << endl;
//
//    // Now we have a bettre idea of blocklength
//    for (auto x : blocklengthCandidates)
//    {
//        for (auto k1 : k1Candidates)
//        {
//            for (int k2 = 0; k2 < 26; ++k2)
//            {
//                string testString = decipherCaesar(code.substr(0, x.first), k1.first) + decipherCaesar(code.substr(x.first, x.first * 2), k2);
//
//                string createSentence;
//
//
//                // Now check for blocklengths
//                for (auto y : permutations)
//                {
//                    if (!testString.compare(y.substr(0, testString.size())))
//                    {
//                        cout << y << endl;
//                        blocklengthCandidates[x.first] += 1;
//                        k2Candidates[k2] += 1;
//                    }
//                    
//                }
//            }
//        }
//    }



//
//    // Now we have a bettre idea of blocklength
//    for (auto x : blocklengthCandidates)
//    {
//        for (auto k1 : k1Candidates)
//        {
//            for (int k2 = 0; k2 < 26; ++k2)
//            {
//                string testString = decipherCaesar(code.substr(0, x.first), k1.first) + decipherCaesar(code.substr(x.first, x.first * 2), k2);
//
//                string createSentence;
//
//
//                // Now check for blocklengths
//                for (auto y : permutations)
//                {
//                    if (!testString.compare(y.substr(0, testString.size())))
//                    {
//                        cout << y << endl;
//                        blocklengthCandidates[x.first] += 1;
//                        k2Candidates[k2];
//                    }
//
//                }
//            }
//        }
//    }


    cout << "done";


    return 0;
}

