#include <iostream>
#include <cstdio>

using namespace std;

int grid[301][301];

int getHundreds(int x) 
{
    // e.g. (1231 - 1000 - 31) / 100
    return (x - x % 100 - (x / 1000) * 1000) / 100;
}

int main() 
{
    int serialNumber;
    cout << "Serial number: ";
    cin >> serialNumber;

    // Calculate the power of every cell
    for (int x=1; x<=300; x++) {
        for (int y=1; y<=300; y++) {
            int rackId = x + 10;
            int powerLevel = getHundreds((rackId * y + serialNumber) * rackId) - 5;
            grid[x][y] = powerLevel;
        }
    }

    // Iterate through every group of 9
    int maxSoFar = 0, mX = 0, mY = 0;
    for (int x = 1; x <= 298; x++) {
        for (int y=1; y <= 298; y++) {
            int sum = grid[x][y]   + grid[x+1][y]   + grid[x+2][y]
                    + grid[x][y+1] + grid[x+1][y+1] + grid[x+2][y+1]
                    + grid[x][y+2] + grid[x+1][y+2] + grid[x+2][y+2];
            if (sum > maxSoFar) {
                maxSoFar = sum;
                mX = x;
                mY = y;
            }
        }
    }

    cout << mX << "," << mY << endl;
}