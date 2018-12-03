#include <iostream>
#include <cstdio>

using namespace std;

int main() 
{
    // Map counts the number of times a quilt is added on a square
    int map[1001][1001] = { 0 }; // Initialize all to 0

    // Input loop
    int id, c, r, w, h;
    while (scanf("#%d @ %d,%d: %dx%d\n", &id, &c, &r, &w, &h) != EOF) 
        for (int i=r; i<r+h; i++) 
            for (int j=c; j<c+w; j++)
                map[i][j]++;
            
    // Count every square that has 2 or more quilts
    int result = 0;
    for (int i=0; i<1001; i++) 
        for (int j=0; j<1001; j++)
            if (map[i][j] > 1) result++;

    printf("%d\n", result);
}