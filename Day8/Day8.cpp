#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <stack>

using namespace std;

void addMeta(int readMeta, int& totalScore) 
{
    for (int i = 0; i < readMeta; i++) {
        int readValue;
        scanf("%d", &readValue);
        //cout << readValue << " ";
        totalScore += readValue;
    }       
    //cout << endl;
}

int main() 
{
    stack<int> children, metas;
    int totalScore = 0;
    int readChildren, readMeta;
    while (scanf("%d %d", &readChildren, &readMeta) != EOF)
    {
        //cout << "Children: " << readChildren << ", meta: " << readMeta << endl;
        // Has children - just add to stack and handle later
        if (readChildren != 0) {
            // Add to the stack
            children.push(readChildren);
            metas.push(readMeta);
            continue;
        }
        
        // Add the meta values of this node
        addMeta(readMeta, totalScore);

        // Decrement parents whever the last one hits 0
        bool ended = false;
        while (!ended && children.size() > 0) 
        {
            // Decrement parent
            int pChildren = children.top();
            children.pop();
            // Parent reached 0 - read meta
            if (pChildren - 1 == 0) {
                addMeta(metas.top(), totalScore);
                metas.pop();
            // Just decrement
            } else {
                children.push(pChildren - 1);
                ended = true;
            }
        }
    }
    cout << totalScore << endl;
}