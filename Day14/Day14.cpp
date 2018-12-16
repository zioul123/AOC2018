#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> l;
    l.push_back(3); l.push_back(7); l.push_back(1); l.push_back(0);
    int idx1 = 0, idx2 = 1;
    int numNeeded;
    cout << "Number needed:";
    cin >> numNeeded;
    
    while (l.size() < numNeeded + 10) {
        // cout << "Looping" << endl;
        // for (int i = 0; i < l.size(); i++) {
        //     if (i == idx1) {
        //         cout << "(" << l[i] << ")";
        //     } else if (i == idx2) {
        //         cout << "[" << l[i] << "]";
        //     } else
        //         cout << " " << l[i] << " ";
        //     // 1- indexed
        // }
        // cout << endl;

        idx1 = (idx1 + l[idx1] + 1) % l.size();
        idx2 = (idx2 + l[idx2] + 1) % l.size();

        int newRecipe = l[idx1] + l[idx2];
        if (newRecipe >= 10) {
            l.push_back(newRecipe / 10);
            l.push_back(newRecipe % 10);
        } else {
            l.push_back(newRecipe);
        }
    }

    // for (int i = 0; i < l.size(); i++) {
    //     cout << l[i] << " ";
    // }
    // cout << endl;

    for (int i = numNeeded; i < numNeeded+10; i++) {
        cout << l[i];
    }
    cout << endl;

}