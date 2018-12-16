#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> l;
    l.push_back(3); l.push_back(7); l.push_back(1); l.push_back(0);
    int idx1 = 0, idx2 = 1;
    string numNeeded;
    cout << "Number needed: ";
    cin >> numNeeded;
    
    bool breaker = false;
    while (!breaker) {
        idx1 = (idx1 + l[idx1] + 1) % l.size();
        idx2 = (idx2 + l[idx2] + 1) % l.size();

        int newRecipe = l[idx1] + l[idx2];
        if (newRecipe >= 10) {
            l.push_back(newRecipe / 10);
            l.push_back(newRecipe % 10);
        } else {
            l.push_back(newRecipe);
        }

        // Only check if long enough
        if (l.size() < numNeeded.size()) continue;
        string s = "";
        // 2 Checks. One for immediate, one for second last
        for (int i = numNeeded.size(); i > 0; i--) {
            s += to_string(l[l.size() - i]);
        }
        //cout << l.size() - numNeeded.size() << ", " << s << endl;
        if (s == numNeeded) {
            cout << "Broke after " << l.size() - numNeeded.size() << endl;
            breaker = true;
        }

        if (l.size() < numNeeded.size() + 1) continue;
        s = "";
        for (int i = numNeeded.size(); i > 0; i--) {
            s += to_string(l[l.size() - 1 - i]);
        }
        //cout << l.size() - numNeeded.size() << ", " << s << endl;
        if (s == numNeeded) {
            cout << "Broke after " << l.size() - numNeeded.size() - 1 << endl;
            breaker = true;
        }
    }
}