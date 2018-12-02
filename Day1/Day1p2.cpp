#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <vector>

using namespace std;

int main() 
{
    unordered_set<int> visited;
    vector<int> freqs;
    visited.insert(0);

    // First pass
    int curr, res = 0;
    while (scanf("%d\n", &curr) != EOF) 
    {
        res += curr;
        if (visited.find(res) != visited.end()) 
        {
            printf("%d\n", res); 
            return 0;
        }
        visited.insert(res);
        freqs.push_back(curr);
    }

    // Infinite passes until a repeat occurs
    while (true) 
    {
        for (int i = 0; i < freqs.size(); i++) 
        {
            res += freqs[i];
            if (visited.find(res) != visited.end())
            {
                printf("%d\n", res);
                return 0;
            }
            visited.insert(res);
        }
    }
}
