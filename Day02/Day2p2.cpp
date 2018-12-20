#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/** Returns true if the two strings differ by 1 letter */
bool isSimilar(string s1, string s2) 
{
    int differences = 0;
    for (int i = 0; i < s1.size(); ++i) 
    {
        if (s1[i] != s2[i]) 
            differences++;
        if (differences > 1) 
            return false;
    }
    return true;
}

/** Returns the common letters in the string */
string similarity(string s1, string s2) 
{
    string result;
    for (int i = 0; i < s1.size(); ++i) 
    {
        if (s1[i] == s2[i])
            result += s1[i];
    }
    return result;
}

int main()
{
    // Input routine
    vector<string> input;
    string s;
    while (getline(cin, s)) 
    {
        if (s.empty()) break;
        input.push_back(s);
    }

    // n^2 loop to find solution
    for (int i = 0; i < input.size(); i++)
        for (int j = i + 1; j < input.size(); j++)
            if (isSimilar(input[i], input[j])) {
                cout << similarity(input[i], input[j]) << endl;
                return 0;
            }

    return 0;
}
