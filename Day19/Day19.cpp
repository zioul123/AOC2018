#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

long long reg[6] = {0}; // Initialize to 0 0 0 0 0 0

void execute(string command) {
    istringstream in(command);
    string cmd;
    long long a, b, dest;
    in >> cmd >> a >> b >> dest;
    if (cmd == "addi") {
        reg[dest] = reg[a] + b;
    } else if (cmd == "addr") {
        reg[dest] = reg[a] + reg[b];
    } else if (cmd == "seti") {
        reg[dest] = a;
    } else if (cmd == "setr") {
        reg[dest] = reg[a];
    } else if (cmd == "mulr") {
        reg[dest] = reg[a] * reg[b];
    } else if (cmd == "muli") {
        reg[dest] = reg[a] * b;
    } else if (cmd == "eqrr") {
        reg[dest] = (reg[a] == reg[b]) ? 1 : 0;
    } else if (cmd == "gtrr") {
        reg[dest] = (reg[a] > reg[b]) ? 1 : 0;
    } else {
        cout << "No such command" << endl;
    }
}

int main() 
{
    string s;
    vector<string> in;
    getline(cin, s);
    int instructionReg = s[4] - '0';

    // Store all input
    while (getline(cin, s)) 
    {
        in.push_back(s);
    }

    // Run commands until the end
    while (reg[instructionReg] < in.size()) { 
        // Pre
        cout << "ip=" << reg[instructionReg] << ", [";
        for (int i = 0; i < 6; i++) cout << reg[i] << ", ";
        
        // The command
        cout << "] " << in[reg[instructionReg]] << ", ";

        // Post
        execute(in[reg[instructionReg]]);
        cout << "[";
        for (int i = 0; i < 6; i++) cout << reg[i] << ", ";
        cout << "]" << endl;

        // Increment      
        reg[instructionReg]++;
    }
    cout << reg[0] << endl;
}