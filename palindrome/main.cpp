#include <iostream>
#include <string>
#include <cstring>

using namespace std;



#define MAX_SIZE 1000
unsigned long long numFound[MAX_SIZE][MAX_SIZE]; //intermediate results, indexed by [startPosition][endPosition]

unsigned long long countPalindromes(const char *str) {
    int len = strlen(str);
    for (int startPos=0; startPos<=len; startPos++)
        for (int endPos=0; endPos<=len; endPos++)
            numFound[startPos][endPos] = 0;

    for (int spanSize=1; spanSize<=len; spanSize++) {
        for (int startPos=0; startPos<=len-spanSize; startPos++) {
            int endPos = startPos + spanSize;
            unsigned long long count = numFound[startPos+1][endPos];   //if str[startPos] is not in the palindrome, this will be the count
            char ch = str[startPos];

            //if str[startPos] is in the palindrome, choose a matching character for the palindrome end
            for (int searchPos=startPos; searchPos<endPos; searchPos++) {
                if (str[searchPos] == ch)
                    count += 1 + numFound[startPos+1][searchPos];
            }

            numFound[startPos][endPos] = count;
        }
    }
    return numFound[0][len];
}

int main()
{
    int patato;
    string temp;

    cin >> patato;
    cin >> temp;

    if (temp.size() > 20) temp = temp.substr(0, 21);

    const char* str = "";

    str = temp.c_str();

    cout << countPalindromes(str) % 12345678;


    return 0;
}