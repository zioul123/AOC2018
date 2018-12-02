#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

/** Count the total number of strings in in that have at least one character with exactly
    total occurrences. */
int count(vector<string> in, int total)
{
    int totalRes = 0;
    for (vector<string>::iterator it = in.begin(); it != in.end(); ++it)
    {
        string s = *it;
        int res = 0; // The number of characters that have exactly total occurrences
        unordered_map<char, int> count; // Number of occurences of a char

        for (int i = 0; i < s.size(); ++i)
        {
            // If count does not contain char at s[i]
            if (count.find(s[i]) == count.end())
            {
                count[s[i]] = 1; 
                continue;
            }

            // Only add to res when it hits the total required
            if (count[s[i]] == total - 1) 
            {
                ++res;
            } 
            // Decrement res if it exceeds total required
            else if (count[s[i]] == total) 
            {
                --res;
            }
            // Add to the count
            ++count[s[i]];
        }

        // Add to the total result
        if (res > 0) ++totalRes; 
    }
    return totalRes;
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

    // Generate result
    int hasTwo = count(input, 2);
    int hasThree = count(input, 3);
    cout << (hasTwo * hasThree) << endl;
}