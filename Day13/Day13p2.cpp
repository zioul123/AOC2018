#include <vector>
#include <cstdio>
#include <iostream>

using namespace std;

vector<vector<char> > map;

int NONE = -1, LEFT = 0, UP = 1, RIGHT = 2;
vector<vector<int> > direction;

bool isCart(char initiallyThere) {
    return initiallyThere == 'v' || initiallyThere == '>' || initiallyThere == '^' || initiallyThere == '<';
}

int main() 
{
    int width;
    // Get input
    string s;
    getline(cin, s);
    width = s.size() + 2;

    {   // Add buffer line
        vector<char> empty;
        for (int i = 0; i < width; i++) {
            empty.push_back(' ');
        }
        map.push_back(empty);

        // Add direction tracker
        vector<int> dirRow(width, NONE);
        direction.push_back(dirRow);
    }

    int j = 1;
    do {
        // Add direction tracker
        vector<int> dirRow(width, NONE);
        direction.push_back(dirRow);
        
        // Read the map
        vector<char> curr;
        curr.push_back(' '); // Buffer space
        for (int i = 0; i < s.size(); i++) {
            curr.push_back(s[i]);

            // Direction tracker
            if (s[i] == 'v' || s[i] == '>' || s[i] == '^' || s[i] == '<') {
                direction[j][i+1] = LEFT;
            }
        }
        curr.push_back(' '); // Buffer space
        map.push_back(curr);

        j++;
    } while (getline(cin, s));

    {   // Add buffer line
        vector<char> empty;
        for (int i = 0; i < width; i++) {
            empty.push_back(' ');
        }
        map.push_back(empty);

        // Add direction tracker
        vector<int> dirRow(s.size(), NONE);
        direction.push_back(dirRow);
    }
        
    // Test input
    // for (auto it = map.begin(); it != map.end(); ++it) {
    //     vector<char> l = *it;
    //     for (auto it2 = l.begin(); it2 != l.end(); ++it2) {
    //         cout << *it2;
    //     }
    //     cout << endl;
    // }
    // for (int i = 0; i < direction.size(); i++) {
    //     for (int j=0; j<direction[i].size(); j++) {
    //         cout << direction[i][j];
    //     }    
    //     cout <<endl;
    // }

    // Copy the map first
    vector<vector<char> > prevMap;
    for (int i = 0; i < map.size(); i++) {
        vector<char> row(map[i]);
        prevMap.push_back(row);
    }

    // Preprocess the  true map to remove carts
    for (int i = 0; i < map.size(); i++) 
        for (int j = 0; j < map[i].size(); j++) 
            switch (map[i][j]) {
                case 'v':
                    map[i][j] = map[i][j-1] == '-' ? '\\' :  // Left has a - => '\'
                                map[i][j+1] == '-' ? '/' :   // Right has  - => '/'
                                '|';
                    break;
                case '^':
                    map[i][j] = map[i][j-1] == '-' ? '/' :   // Left has a - => '/'
                                map[i][j+1] == '-' ? '\\' :  // Right has  - => '\'
                                '|';
                    break;
                case '<':
                    map[i][j] = map[i-1][j] == '|' ? '/' :   // Above has  | => '/'
                                map[i+1][j] == '|' ? '\\' :  // Below has  | => '\'
                                '-';
                    break;
                case '>':
                    map[i][j] = map[i-1][j] == '|' ? '\\' :  // Above has  | => '\'
                                map[i+1][j] == '|' ? '/' :   // Below has  | => '/'
                                '-';
                    break;
                default:
                    // Do nothing.
                    break;
            }

    // Update map
    int count = 2; 
    while (count > 0) 
    {
        count = 0; // Becomes true if there was a single cart

        // Premake the result map - a copy of the previous map
        vector<vector<char> > updatedMap;
        for (int i = 0; i < prevMap.size(); i++) {
            vector<char> row(prevMap[i]);
            updatedMap.push_back(row);
        }

        for (int i = 0; i < prevMap.size(); i++) {
            for (int j = 0; j < prevMap[i].size(); j++) {
                char initiallyThere;
                switch (prevMap[i][j]) {
                // Move down
                case 'v':
                    count++;
                    updatedMap[i][j] = map[i][j];
                    
                    initiallyThere = updatedMap[i+1][j]; 
                    if (isCart(initiallyThere)) {
                        cout << "Collision at " << j-1 << "," << i << endl;
                        prevMap[i+1][j] = map[i+1][j];
                        updatedMap[i+1][j] = map[i+1][j];
                        break;
                    }

                    switch (updatedMap[i+1][j]) {
                    case '|':
                        updatedMap[i+1][j] = 'v';
                        break;
                    case '\\':
                        updatedMap[i+1][j] = '>';
                        break;
                    case '/':
                        updatedMap[i+1][j] = '<';
                        break;
                    case '+':
                        updatedMap[i+1][j] = 
                            direction[i][j] == LEFT  ? '>' :
                            direction[i][j] == UP    ? 'v' :
                            direction[i][j] == RIGHT ? '<' : '@' ;
                        direction[i][j] = (direction[i][j] + 1) % 3;
                        break;
                    }
                    // Track direction
                    direction[i+1][j] = direction[i][j];
                    cout << "Direction of " << j-1 << "," << i << ": " << direction[i+1][j] << endl;
                    // Remove direction from previous position
                    direction[i][j] = NONE;
                    break;
                case '^':
                    count++;
                    updatedMap[i][j] = map[i][j];

                    initiallyThere = updatedMap[i-1][j]; 
                    if (isCart(initiallyThere)) {
                        cout << "Collision at " << j-1 << "," << i-2 << endl;
                        prevMap[i-1][j] = map[i-1][j];
                        updatedMap[i-1][j] = map[i-1][j];
                        break;
                    }

                    switch (updatedMap[i-1][j]) {
                    case '|':
                        updatedMap[i-1][j] = '^';
                        break;
                    case '\\':
                        updatedMap[i-1][j] = '<';
                        break;
                    case '/':
                        updatedMap[i-1][j] = '>';
                        break;
                    case '+':
                        updatedMap[i-1][j] = 
                            direction[i][j] == LEFT  ? '<' :
                            direction[i][j] == UP    ? '^' :
                            direction[i][j] == RIGHT ? '>' : '@' ;
                        direction[i][j] = (direction[i][j] + 1) % 3;
                        break;
                    } 
                    direction[i-1][j] = direction[i][j];
                    cout << "Direction of " << j-1 << "," << i-2 << ": " << direction[i-1][j] << endl;
                    direction[i][j] = NONE;
                    break;
                case '<':
                    count++;
                    updatedMap[i][j] = map[i][j];
                        
                    initiallyThere = updatedMap[i][j-1]; 
                    if (isCart(initiallyThere)) {
                        cout << "Collision at " << j-2 << "," << i-1 << endl;
                        prevMap[i][j-1] = map[i][j-1];
                        updatedMap[i][j-1] = map[i][j-1];
                        break;
                    }

                    switch (updatedMap[i][j-1]) {
                    case '-':
                        updatedMap[i][j-1] = '<';
                        break;
                    case '\\':
                        updatedMap[i][j-1] = '^';
                        break;
                    case '/':
                        updatedMap[i][j-1] = 'v';
                        break;
                    case '+':
                        updatedMap[i][j-1] = 
                            direction[i][j] == LEFT  ? 'v' :
                            direction[i][j] == UP    ? '<' :
                            direction[i][j] == RIGHT ? '^' : '@' ;
                        direction[i][j] = (direction[i][j] + 1) % 3;
                        break;
                    } 
                    direction[i][j-1] = direction[i][j];
                    cout << "Direction of " << j-2 << "," << i-1 << ": " << direction[i][j-1] << endl;
                    direction[i][j] = NONE;
                    break;
                case '>':
                    count++;
                    updatedMap[i][j] = map[i][j];
                    
                    initiallyThere = updatedMap[i][j+1]; 
                    if (isCart(initiallyThere)) {
                        cout << "Collision at " << j << "," << i-1 << endl;
                        prevMap[i][j+1] = map[i][j+1];
                        updatedMap[i][j+1] = map[i][j+1];
                        break;
                    }

                    switch (updatedMap[i][j+1]) {
                    case '-':
                        updatedMap[i][j+1] = '>';
                        break;
                    case '\\':
                        updatedMap[i][j+1] = 'v';
                        break;
                    case '/':
                        updatedMap[i][j+1] = '^';
                        break;
                    case '+':
                        updatedMap[i][j+1] = 
                            direction[i][j] == LEFT  ? '^' :
                            direction[i][j] == UP    ? '>' :
                            direction[i][j] == RIGHT ? 'v' : '@' ;
                        direction[i][j] = (direction[i][j] + 1) % 3;
                        break;
                    } 
                    direction[i][j+1] = direction[i][j];
                    cout << "Direction of " << j << "," << i-1 << ": " << direction[i][j+1] << endl;
                    direction[i][j] = NONE;
                    break;
                default:
                    // Do nothing.
                    break;
                }
            }
        }

        // Swap buffer
        prevMap = updatedMap;

        // cout << "After changes:" << endl;
        // // Test print
        // cout << endl;
        // for (auto it = prevMap.begin(); it != prevMap.end(); ++it) {
        //     vector<char> l = *it;
        //     for (auto it2 = l.begin(); it2 != l.end(); ++it2) {
        //         cout << *it2;
        //     }
        //     cout << endl;
        // }
        if (count == 1) {
            cout << "Look at the SECOND LAST RESULT." << endl;
            break;
        }
    }
}