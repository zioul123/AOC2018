#include <iostream>
#include <cstdio>

using namespace std;

int grid[301][301];
int cGrid[301][301];

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

    // Preprocess the grid
    for (int y = 1; y < 301; y++) {
        for (int x = 1; x < 301; x++) {
            // Don't add bottom row
            if (y == 1 && x == 1) {
                cGrid[x][y] = grid[x][y];
            } else if (y == 1) {
                cGrid[x][y] = grid[x][y] + cGrid[x-1][y];
            } else if (x == 1) {
                cGrid[x][y] = grid[x][y] + cGrid[x][y-1];
            } else {
                cGrid[x][y] = grid[x][y] + cGrid[x][y-1]
                            + cGrid[x-1][y] - cGrid[x-1][y-1];
            }
        }
    }

    // Iterate through every group of 9
    int maxSoFar = 0, mX = 0, mY = 0, mR = 0;
    int r = 1;
    for (; r <= 300; r++)
    // Every Left corner
    for (int x = 1; x <= 301-r; x++) {
        for (int y=1; y <= 301-r; y++) {
            // Find the power of the RxR box based on preprocessed grid
            int sum;
            if (x == 1 && y == 1)
                sum = cGrid[x+r-1][y+r-1];
            else if (x == 1) 
                sum = cGrid[x+r-1][y+r-1] - cGrid[x+r-1][y-1];
            else if (y == 1) 
                sum = cGrid[x+r-1][y+r-1] - cGrid[x-1][y+r-1];
            else 
                sum = cGrid[x+r-1][y+r-1] - cGrid[x+r-1][y-1]
                    - cGrid[x-1][y+r-1] + cGrid[x-1][y-1];

            // Update max if necessary
            if (sum > maxSoFar) {
                maxSoFar = sum;
                mX = x;
                mY = y;
                mR = r;
            }
        }
    }

    cout << mX << "," << mY << "," << mR << endl;
}