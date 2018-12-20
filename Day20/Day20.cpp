#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

int map[1000][1000] = { {0} }; // This is safe through experiment.

stack<int> colStack, rowStack; // Store the last location before a bracket

int startCol = 500,    startRow = 500;
int minCol   = 499,    minRow   = 499;
int maxCol   = 501,    maxRow   = 501;

int currCol  = startCol, currRow = startRow;

const int IRRELEVANT = 0;
const int DOOR = 1;
const int ROOM = 2;
const int WALL = 3;
const int UNKN = 4;
const int BEGN = 5;

// A struct to hold coordinates
struct Coord {
    int row, col, dist;
    Coord(int _row, int _col, int _dist): row(_row), col(_col), dist(_dist) {}
};

// Used to print doors
bool isHorizontal(int row) {
    return (abs(row - startRow) % 2 != 0);
}

// Used to preview the map
void printMap() {
    for (int i = minRow; i <= maxRow; i++) {
        for (int j = minCol; j <= maxCol; j++) {
            cout << (map[i][j] == IRRELEVANT ? " " :
                     map[i][j] == ROOM ? "." :
                     map[i][j] == WALL ? "#" : 
                     map[i][j] == UNKN ? "?" :
                     map[i][j] == BEGN ? "X" :
                     isHorizontal(i)   ? "-" : "|");
        }
        cout << endl;
    }
}

void convertUnknownToWalls() {
    for (int i = minRow; i <= maxRow; i++) {
        for (int j = minCol; j <= maxCol; j++) {
             if (map[i][j] == UNKN) {
                map[i][j] = WALL;
             }  
        }
    }
}

int main() 
{
    // Get input
    string input;
    cin >> input;

    // Initialize the map
    map[startRow][startCol] = BEGN;
    map[startRow+1][startCol+1] = (map[startRow+1][startCol-1]
                                = (map[startRow-1][startCol-1]
                                = (map[startRow-1][startCol+1]
                                = (WALL))));
    map[startRow  ][startCol+1] = (map[startRow  ][startCol-1]
                                = (map[startRow+1][startCol  ]
                                = (map[startRow-1][startCol  ]
                                = (UNKN))));

    // For preview
    // printMap();

    for (int i = 1; i < input.size()-1; i++) {
        switch (input[i]) {
        case 'N':
            // Only mark the others as unknown if not visited before
            if (map[currRow-2][currCol] == IRRELEVANT) {
                map[currRow-2][currCol+1] = UNKN;
                map[currRow-2][currCol-1] = UNKN;
                map[currRow-3][currCol  ] = UNKN;
            }

            map[currRow-1][currCol  ] = DOOR;
            map[currRow-2][currCol  ] = ROOM;
            map[currRow-3][currCol+1] = WALL;
            map[currRow-3][currCol-1] = WALL;
            
            currRow -= 2;
            minRow   = min(minRow, currRow - 1);
            break;
        case 'S':
            if (map[currRow+2][currCol  ] == IRRELEVANT) {
                map[currRow+2][currCol+1] = UNKN;
                map[currRow+2][currCol-1] = UNKN;
                map[currRow+3][currCol  ] = UNKN;
            }

            map[currRow+1][currCol  ] = DOOR;
            map[currRow+2][currCol  ] = ROOM;
            map[currRow+3][currCol+1] = WALL;
            map[currRow+3][currCol-1] = WALL;

            currRow += 2;
            maxRow   = max(maxRow, currRow + 1);
            break;
        case 'E':
            if (map[currRow  ][currCol+2] == IRRELEVANT) {
                map[currRow+1][currCol+2] = UNKN;
                map[currRow-1][currCol+2] = UNKN;
                map[currRow  ][currCol+3] = UNKN;
            }

            map[currRow  ][currCol+1] = DOOR;
            map[currRow  ][currCol+2] = ROOM;
            map[currRow+1][currCol+3] = WALL;
            map[currRow-1][currCol+3] = WALL;
            
            currCol += 2;
            maxCol   = max(maxCol, currCol + 1);
            break;
        case 'W':
            if (map[currRow  ][currCol-2] == IRRELEVANT) {
                map[currRow+1][currCol-2] = UNKN;
                map[currRow-1][currCol-2] = UNKN;
                map[currRow  ][currCol-3] = UNKN;
            }

            map[currRow  ][currCol-1] = DOOR;
            map[currRow  ][currCol-2] = ROOM;
            map[currRow+1][currCol-3] = WALL;
            map[currRow-1][currCol-3] = WALL;

            currCol -= 2;
            minCol   = min(minCol, currCol - 1);
            break;
        case '(':
            rowStack.push(currRow);
            colStack.push(currCol);
            break;
        case '|':
            currRow = rowStack.top();
            currCol = colStack.top();
            break;
        case ')':
            currRow = rowStack.top();
            rowStack.pop();
            currCol = colStack.top();
            colStack.pop();
            break;
        }
        // cout << endl;
        // printMap();
        // cout << endl;
    }

    cout << "Ended. Final map:" << endl;
    convertUnknownToWalls();
    printMap();

    // BFS
    // Queue
    queue<Coord> q;
    Coord coord(startRow, startCol, 0);
    q.push(coord);
    // Visited check
    bool visited[1000][1000] = { {false} };
    visited[startRow][startCol] = true;
    // Final result
    int maxDist = 0;
    while (q.size() > 0) {
        Coord c = q.front();
        q.pop();

        if (c.dist > maxDist) {
            maxDist = c.dist;
        }

        // Visit all four neighbours
        if (map[c.row+1][c.col  ] == DOOR && !visited[c.row+2][c.col  ]) {
            Coord neighbour(c.row+2, c.col  , c.dist+1);
            q.push(neighbour);
            visited[c.row+2][c.col  ] = true;
        }
        if (map[c.row-1][c.col  ] == DOOR && !visited[c.row-2][c.col  ]) {
            Coord neighbour(c.row-2, c.col  , c.dist+1);
            q.push(neighbour);
            visited[c.row-2][c.col  ] = true;
        }
        if (map[c.row  ][c.col+1] == DOOR && !visited[c.row  ][c.col+2]) {
            Coord neighbour(c.row  , c.col+2, c.dist+1);
            q.push(neighbour);
            visited[c.row  ][c.col+2] = true;
        }
        if (map[c.row  ][c.col-1] == DOOR && !visited[c.row  ][c.col-2]) {
            Coord neighbour(c.row  , c.col-2, c.dist+1);
            q.push(neighbour);
            visited[c.row  ][c.col-2] = true;
        }
    }
    cout << "Requires " << maxDist << endl;
}
