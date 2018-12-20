#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

int main() 
{
    // Map counts the number of times a quilt is added on a square
    int map[1001][1001] = { 0 }; // Initialize all to 0
    vector< vector<int> > inputs; // All the inputs will be recorded for second pass

    // Input loop
    int id, c, r, w, h;
    while (scanf("#%d @ %d,%d: %dx%d\n", &id, &c, &r, &w, &h) != EOF) 
    {
        // Save input
        vector<int> input; 
        input.push_back(id);
        input.push_back(c);
        input.push_back(r);
        input.push_back(w);
        input.push_back(h);
        inputs.push_back(input);

        for (int i=r; i<r+h; i++) 
            for (int j=c; j<c+w; j++)
                map[i][j]++;
    }

    // Count every square that has 2 or more quilts
    for (vector< vector<int> >::iterator it = inputs.begin(); it != inputs.end(); ++it)
    {
        c = (*it)[1];
        r = (*it)[2];
        w = (*it)[3];
        h = (*it)[4];

        bool correct = true;
        for (int i=r; i<r+h && correct; i++) 
            for (int j=c; j<c+w && correct; j++)
                if (map[i][j] > 1) correct = false;

        if (correct) 
        {
            printf("%d\n", (*it)[0]);
        }    
    }
}