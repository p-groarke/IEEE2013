#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

typedef unsigned long long ull;

ull countPalindromesHelper (const char* str, const size_t len, const size_t begin, const size_t end, const ull count) {
    if (begin <= 0 || end >= len) {
        return count;
    }
    const char pred = str [begin - 1];
    const char succ = str [end];
    if (pred == succ) {
        const ull newCount = count == 0 ? 1 : count * 2;
        return countPalindromesHelper (str, len, begin - 1, end + 1, newCount);
    }
    return count;
}

ull countPalindromes (const char* str) {
    ull count = 0;
    size_t len = strlen (str);
    size_t i;
    for (i = 0; i < len; ++i) {
        count += countPalindromesHelper (str, len, i, i, 0);  // even length palindromes
        count += countPalindromesHelper (str, len, i, i + 1, 1); // odd length palindromes
    }
    return count;
}

int main (int argc, char* argv[]) {

    int patate;
    string temp;

    cin >> patate;
    cin >> temp;

    const char* str = "";

    str = temp.c_str();

    ull count = countPalindromes (str);
    printf ("%llu\n", count % 12345678);
    return 0;
}