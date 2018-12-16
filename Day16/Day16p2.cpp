#include <iostream>
#include <vector>

using namespace std;

int ini[4] = {0};
int cmd[4] = {0};
int fin[4] = {0};
int reg[4] = {0};

int UNKNOWN = 0, IMPOSSIBLE = 2, POSSIBLE = 3;
 
/*
 * Calculators
 */
void addr() { // 0
    reg[cmd[3]] = reg[cmd[1]] + reg[cmd[2]];
}
void addi() { // 1
    reg[cmd[3]] = reg[cmd[1]] + cmd[2];
}

void mulr() { // 2
    reg[cmd[3]] = reg[cmd[1]] * reg[cmd[2]];
}
void muli() { // 3
    reg[cmd[3]] = reg[cmd[1]] * cmd[2];
}

void banr() { // 4
    reg[cmd[3]] = reg[cmd[1]] & reg[cmd[2]];
}
void bani() { // 5
    reg[cmd[3]] = reg[cmd[1]] & cmd[2];
}

void borr() { // 6
    reg[cmd[3]] = reg[cmd[1]] | reg[cmd[2]];
}
void bori() { // 7
    reg[cmd[3]] = reg[cmd[1]] | cmd[2];
}

void setr() { // 8
    reg[cmd[3]] = reg[cmd[1]];
}
void seti() { // 9
    reg[cmd[3]] = cmd[1];
    cout << "9 success." << endl;
}

void gtrr() { // 10
    reg[cmd[3]] = (reg[cmd[1]] > reg[cmd[2]]) ? 1 : 0;
}
void gtir() { // 11
    reg[cmd[3]] = (cmd[1] > reg[cmd[2]]) ? 1 : 0;
}
void gtri() { // 12
    reg[cmd[3]] = (reg[cmd[1]] > cmd[2]) ? 1 : 0;
}

void eqrr() { // 13
    reg[cmd[3]] = (reg[cmd[1]] == reg[cmd[2]]) ? 1 : 0;
}
void eqir() { // 14
    reg[cmd[3]] = (cmd[1] == reg[cmd[2]]) ? 1 : 0;
}
void eqri() { // 15
    reg[cmd[3]] = (reg[cmd[1]] == cmd[2]) ? 1 : 0;
}

/*
 * Checkers
 */
bool c_addr() { // 0
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] + ini[cmd[2]]) == fin[cmd[3]];
}
bool c_addi() { // 1
    return (ini[cmd[1]] + cmd[2]) == fin[cmd[3]];
}

bool c_mulr() { // 2
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] * ini[cmd[2]]) == fin[cmd[3]];
}
bool c_muli() { // 3
    return (ini[cmd[1]] * cmd[2]) == fin[cmd[3]];
}

bool c_banr() { // 4
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] & ini[cmd[2]]) == fin[cmd[3]];
}
bool c_bani() { // 5
    return (ini[cmd[1]] & cmd[2]) == fin[cmd[3]];
}

bool c_borr() { // 6
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] | ini[cmd[2]]) == fin[cmd[3]];
}
bool c_bori() { // 7
    return (ini[cmd[1]] | cmd[2]) == fin[cmd[3]];
}

bool c_setr() { // 8
    return ini[cmd[1]] == fin[cmd[3]];
}
bool c_seti() { // 9
    return cmd[1] == fin[cmd[3]];
}

bool c_gtrr() { // 10
    return (ini[cmd[1]] > ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool c_gtir() { // 11
    return (cmd[1] > ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool c_gtri() { // 12
    return (ini[cmd[1]] > cmd[2]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}

bool c_eqrr() { // 13
    return (ini[cmd[1]] == ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool c_eqir() { // 14
    return (cmd[1] == ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool c_eqri() { // 15
    return (ini[cmd[1]] == cmd[2]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}

int main() 
{
    vector<bool(*)()> op;
    op.push_back(c_addr); op.push_back(c_addi); op.push_back(c_mulr); op.push_back(c_muli);
    op.push_back(c_banr); op.push_back(c_bani); op.push_back(c_borr); op.push_back(c_bori);
    op.push_back(c_setr); op.push_back(c_seti); op.push_back(c_gtrr); op.push_back(c_gtir);
    op.push_back(c_gtri); op.push_back(c_eqrr); op.push_back(c_eqir); op.push_back(c_eqri);

    int possible[16][16]; // actual opcode => placeholder op number
    for (int i = 0; i < 16; i++) 
        for (int j = 0; j < 16; j++) 
            possible[i][j] = UNKNOWN;

    string s;
    while (getline(cin, s))
    {   
        if (s.empty()) break;
        sscanf(s.c_str(), "Before: [%d, %d, %d, %d]\n", &ini[0],&ini[1],&ini[2],&ini[3]);
        getline(cin, s);
        sscanf(s.c_str(), "%d %d %d %d\n", &cmd[0],&cmd[1],&cmd[2],&cmd[3]);
        getline(cin, s);
        sscanf(s.c_str(), "After: [%d, %d, %d, %d]\n", &fin[0],&fin[1],&fin[2],&fin[3]);
        getline(cin, s); // Clear the blank line

        int num = 0;
        cout << "Command " << cmd[0];
        for (int i = 0; i < 16; i++) {
            if (!op[i]()) {
                possible[cmd[0]][i] = IMPOSSIBLE;
                cout << " is not " << i << ", ";
            } else if (possible[cmd[0]][i] == UNKNOWN) {
                    cout << " could be " << i << ", ";
                    possible[cmd[0]][i] = POSSIBLE;
            }
        }
        cout << endl;
    }

    cout << "Ended loop" << endl;

    int opcodeToOp[16];
    for (int it = 0; it < 16; it++) {
        // printloop
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                if (possible[i][j] == POSSIBLE) {
                    cout << 1;
                    //break;
                } else {
                    cout << 0;
                }
            }
            cout << endl;
        }
        cout << endl;

        int theUnambiguousOpCode, theOp;
        // Find the unambiguous one
        for (int i = 0; i < 16; i++) {
            int total = 0; 
            int op = -1;
            // Check all entries if there's only one 
            for (int j = 0; j < 16 && total <= 1; j++) {
                if (possible[i][j] == POSSIBLE) {
                    total++;
                    op = j;
                }
            }
            // There's only one, store it.
            if (total == 1) {
                theUnambiguousOpCode = i;
                theOp = op;
                break;
            }
        }

        opcodeToOp[theUnambiguousOpCode] = theOp;
        cout << "The opcode: " << theUnambiguousOpCode << ", Op: " << theOp << endl;
        // Eliminate the rest
        for (int i = 0; i < 16; i++) {
            possible[i][theOp] = IMPOSSIBLE;
        }
    }

    cout << "Opcode map: ";
    for (int i = 0; i < 16; i++) {
        cout << opcodeToOp[i] << " ";
    }
    cout << endl;

    // Run the program
    vector<void(*)()> opcode;
    opcode.push_back(addr); opcode.push_back(addi); opcode.push_back(mulr); opcode.push_back(muli);
    opcode.push_back(banr); opcode.push_back(bani); opcode.push_back(borr); opcode.push_back(bori);
    opcode.push_back(setr); opcode.push_back(seti); opcode.push_back(gtrr); opcode.push_back(gtir);
    opcode.push_back(gtri); opcode.push_back(eqrr); opcode.push_back(eqir); opcode.push_back(eqri);
    
    getline(cin, s);
    while (getline(cin, s)) {
        cout << s.c_str() << endl;
        sscanf(s.c_str(), "%d %d %d %d\n", &cmd[0],&cmd[1],&cmd[2],&cmd[3]);
        cout << cmd[0] << " " << cmd[1] << " " << cmd[2] << " " << cmd[3] << endl;
        cout << "Opcode executed: " << opcodeToOp[cmd[0]] << endl;
        opcode[opcodeToOp[cmd[0]]]();
        cout << reg[0] << " " << reg[1] << " " << reg[2] << " " << reg[3] << endl;
    }
    cout << reg[0] << endl;
}
