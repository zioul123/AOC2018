#include <cstdio>
#include <iostream>

using namespace std;

const int NONE   = 0;
const int GROUND = 1;
const int TREE   = 2;
const int LUMBER = 3;

bool testing = false;

int main()  
{
    string s;
    int map[52][52];
    for (int i = 0; i <= 51; i++) {
        if (i == 0 || i == 51) {
            for (int j = 1; j <= 50; j++)
                map[i][j] = NONE;
            continue;
        }

        getline(cin, s);
        for (int j = 0; j <= 51; j++) {
            if (0 < j && j < 51)
                switch (s[j-1]) {
                case '.':
                    map[i][j] = GROUND;
                    break;
                case '|':
                    map[i][j] = TREE;
                    break;
                case '#':
                    map[i][j] = LUMBER;
                    break;
                }
            else map[i][j] = NONE;
        }
    }

    // // Output preview
    // for (int i = 0; i <= (testing ? 10 : 51); i++) {
    //     for (int j = 0; j <= (testing ? 10 : 51); j++) 
    //         cout << (map[i][j] == GROUND ? '.' :
    //                  map[i][j] == TREE   ? '|' :
    //                  map[i][j] == LUMBER ? '#' : ' ');
    //     cout << endl;
    // }
    // cout << endl;

    int prev = 0;

    for (int n = 0; n < 10000; n++) {
        int copyMap[52][52] = { { 0 } };
        for (int i = 1; i <= (testing ? 10 : 50); i++) {
        for (int j = 1; j <= (testing ? 10 : 50); j++) {
            int numTrees = 0, numGround = 0, numLumber = 0;
            for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                if (k == 0 && l == 0) continue;
                switch (map[i+k][j+l]) {
                case GROUND:
                    numGround++;
                    break;
                case TREE:
                    numTrees++;
                    break;
                case LUMBER:
                    numLumber++;
                    break;
                default:
                    break;
                }
            }
            }

            if (map[i][j] == GROUND) {
                if (numTrees >= 3) {
                    copyMap[i][j] = TREE;
                } else {
                    copyMap[i][j] = map[i][j];
                }
            } else if (map[i][j] == TREE) {
                if (numLumber >= 3) {
                    copyMap[i][j] = LUMBER;
                } else {
                    copyMap[i][j] = map[i][j];
                }
            } else {
                if (numLumber >= 1 && numTrees >= 1) {
                    copyMap[i][j] = LUMBER;
                } else {
                    copyMap[i][j] = GROUND;
                }
            }
        }
        }

        // // Output preview
        // for (int i = 0; i <= (testing ? 10 : 51); i++) {
        //     for (int j = 0; j <= (testing ? 10 : 51); j++) 
        //         cout << (copyMap[i][j] == GROUND ? '.' :
        //                  copyMap[i][j] == TREE   ? '|' :
        //                  copyMap[i][j] == LUMBER ? '#' : ' ');
        //     cout << endl;
        // }         
        // cout << endl;

        // Copy the buffer
        for (int i = 0; i < 52; i++) {
            for (int j = 0; j < 52; j++) {
                map[i][j] = copyMap[i][j];
            }
        }

        // Print this one
        int wooded = 0, lumber = 0;
        for (int i = 1; i <= (testing ? 10 : 50); i++) {
            for (int j = 1; j <= (testing ? 10 : 50); j++) {
                switch (map[i][j]) {
                case TREE:
                    wooded++;
                    break;
                case LUMBER:
                    lumber++;
                    break;
                default:
                    break;
                }
            }
        }
        int resource = wooded * lumber;
        int diff = resource - prev;
        prev = resource;
        cout << n+1 << ": " << wooded << ", " << lumber << ": " << resource << ", Diff: " << diff << endl;
        //cout << diff << endl;
    }
}