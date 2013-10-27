#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <map>

using namespace std;

bool less_vectors(const string& a, const string& b) {
   return a.size() > b.size();
}

bool candidate(string word, string code, map<char, char> result)
{
	if(word.size() == code.size())
	{
		for(int i = 0; i < word.size(); ++i)
		{
			if(result.count(code[i]) == 0)
				result[code[i]] = word[i];
			else
			{
				if(word[i] != result[code[i]])
					return false;
			}
		}

		return true;
	}

	return false;
}

pair<bool, map<char, char>>  compareWord(vector<string> dict, vector<string> message, map<char, char> result)
{
	for(int i = 0; i < dict.size(); ++i)
	{
		string word = dict[i];
		for(int j = 0; j < message.size(); ++j)
		{
			string code = message[j];

			if(!candidate(word, code, result))
				continue;

			map<char, char> lol = result;
			for(int i = 0; i < code.size(); ++i)
				lol[code[i]] = word[i];

			vector<string> temp = dict;
			temp.erase(temp.begin() + i);

			vector<string> temp2 = message;
			temp2.erase(temp2.begin() + j);

			pair<bool, map<char, char>> out = compareWord(temp, temp2, lol);
			if(out.first)
				return out;
		}
	}

	return make_pair(true, result);
}

int main() {
	int N;
	
	string input;
	getline(cin, input);
	N = atoi(input.c_str());

    vector<string> dict;
    string message;
    
    for(int i = 0; i < N; ++i)
    {
	    getline(cin, input);
	    
	    for(int j = 0; j < input.size(); ++j)
	 	   input[j] = toupper(input[j]);

		input = input.substr(0, input.size() - 1);
    
	    dict.push_back(input);
    }
    
    sort(dict.begin(), dict.end(), less_vectors);

	getline(cin, message);
    getline(cin, message);

	istringstream buf(message);
	istream_iterator<string> beg(buf), end;
	vector<string> tokens(beg, end); 

	map<char, char> key;
	pair<bool, map<char, char> > result = compareWord(dict, tokens, key);
	if(result.first)
	{
		key = result.second;
		for(int i = 0; i < message.size(); ++i)
		{
			if(key.count(message[i]) == 0)
				cout << message[i];
			else
				cout << key[message[i]];
		}
	}
	else
		cout << "Caliss";

    return 0;
}
