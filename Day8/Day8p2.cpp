#include <iostream>
#include <cstdio>
#include <string>
#include <cmath>
#include <climits>
#include <vector>
#include <stack>

using namespace std;

struct Tree {
    int val, childrenNo, metasNo, treeId;
    vector<Tree> children;
    vector<int> metas;
    Tree() {}
    Tree(int _treeId, int _val, int _childrenNo, int _metasNo):
        treeId(_treeId), val(_val), childrenNo(_childrenNo), metasNo(_metasNo) {}
};

string toString(vector<int> vec) {
    string s;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        s += std::to_string(*it) + " ";
    }
    return s;
}

string toString(Tree t) {
    string s;
    s += to_string(t.treeId) + ": " + to_string(t.val);
    return s;
}
string toString(vector<Tree> vec) {
    string s;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        s += toString(*it) + ", ";
    }
    return s;
}

void addMeta(Tree& tree) 
{
    for (int i = 0; i < tree.metasNo; i++) {
        int readValue;
        scanf("%d", &readValue);
        tree.metas.push_back(readValue);
        if (tree.childrenNo == 0) {
            tree.val += readValue;
        }
    }       
    if (tree.childrenNo == 0) {
        cout << tree.treeId << " Value: " << tree.val << endl;
    }
}

void addChildren(Tree& tree) 
{
    cout << "Adding children " << toString(tree.metas) << "from children\n" << toString(tree.children) << endl;
    for (auto it = tree.metas.begin(); it != tree.metas.end(); ++it) {
        if (1 <= (*it) && (*it) <= tree.children.size()) {
            tree.val += tree.children[(*it)-1].val;
        }
    }
}

int main() 
{
    int treeId = 0;
    stack<Tree> trees;
    int readChildren, readMeta;
    while (scanf("%d %d", &readChildren, &readMeta) != EOF)
    {
        cout << treeId << " Children: " << readChildren << ", meta: " << readMeta << endl;
        // Has children - just add to stack and handle later
        if (readChildren != 0) {
            // Add to the stack
            trees.push(Tree(treeId++, 0, readChildren, readMeta));
            continue;
        }
        
        // No children
        Tree curr(treeId++, 0, 0, readMeta);
        // Add the meta values up for this node
        addMeta(curr);

        bool ended = false;
        while (!ended && trees.size() != 0) {
            Tree parent = trees.top(); trees.pop();
            cout << "Parent: " << parent.treeId << " " << parent.children.size() << "/" << parent.childrenNo << endl;
            parent.children.push_back(curr);
            if (parent.children.size() != parent.childrenNo) {
                trees.push(parent);
                cout << "Added child (incomplete)" << endl;
                ended = true;
            } else {
                addMeta(parent);
                addChildren(parent);
                cout << "Complete " << parent.treeId << ": " << parent.val << endl;
                curr = parent;
            }
        }
    }
}
