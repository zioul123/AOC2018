#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

// 0 index of the vector
int idx0 = 50;

// Generates a bitmask from vector array.
// e.g. <[0,1,1,0,0,1], 1> will return 0..011001 = 25
int getSignature(vector<bool> v, int idx) {
    int result = 0;
    for (int i = 0; i < 5; i++) {
        // If true, add to the mask
        result |= (v[idx+i] ? (1 << (4-i)) : 0);
    }
    return result;
}
int getSignature(string s) {
    int result = 0;
    for (int i = 0; i < 5; i++) {
        // If true, add to the mask
        result |= (s[i] == '#' ? (1 << (4-i)) : 0);
    }
    return result;
}

int main() 
{
    // Get input
    string initialState;
    getline(cin, initialState);
    initialState = initialState.substr(15);

    // Create state array
    vector<bool> state(idx0 * 2 + initialState.size(), false); // Start from -50 to size+50
    for (int i = 0; i < initialState.size(); i++) {
        // . is false, # is true
        state[idx0 + i] = initialState[i] != '.';
    }

    // Read all the inputs and put into a 'map'
    bool map[32] = {false};
    string mask, arrow, final;
    while (cin >> mask >> arrow >> final) {
        map[getSignature(mask)] = (final == "#");
    }

    // Grow the plants
    for (int i = 0; i < 20; i++) {
        // Create new one
        vector<bool> newState(idx0 * 2 + initialState.size(), false); 

        // Only grow the plants from 2 of both the boundaries
        for (int i = 0; i < state.size(); i++) {
            if (i < 2 || i >= state.size() - 2) {
                newState[i] = state[i];
            } else {
                newState[i] = map[getSignature(state, i-2)];
            }
        }
        state = newState;
    }

    // Generate the result
    int sum = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state[i]) {
            sum += i - idx0;
        }
    }
    
    cout << sum << endl;
}