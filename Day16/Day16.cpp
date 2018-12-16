#include <iostream>
#include <vector>

using namespace std;

int ini[4] = {0};
int cmd[4] = {0};
int fin[4] = {0};

bool addr() { // 0
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] + ini[cmd[2]]) == fin[cmd[3]];
}
bool addi() { // 1
    return (ini[cmd[1]] + cmd[2]) == fin[cmd[3]];
}

bool mulr() { // 2
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] * ini[cmd[2]]) == fin[cmd[3]];
}
bool muli() { // 3
    return (ini[cmd[1]] * cmd[2]) == fin[cmd[3]];
}

bool banr() { // 4
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] & ini[cmd[2]]) == fin[cmd[3]];
}
bool bani() { // 5
    return (ini[cmd[1]] & cmd[2]) == fin[cmd[3]];
}

bool borr() { // 6
    if (cmd[2] < 0 || cmd[2] > 3) return false;
    return (ini[cmd[1]] | ini[cmd[2]]) == fin[cmd[3]];
}
bool bori() { // 7
    return (ini[cmd[1]] | cmd[2]) == fin[cmd[3]];
}

bool setr() { // 8
    return ini[cmd[1]] == fin[cmd[3]];
}
bool seti() { // 9
    return cmd[1] == fin[cmd[3]];
}

bool gtrr() { // 10
    return (ini[cmd[1]] > ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool gtir() { // 11
    return (cmd[1] > ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool gtri() { // 12
    return (ini[cmd[1]] > cmd[2]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}

bool eqrr() { // 13
    return (ini[cmd[1]] == ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool eqir() { // 14
    return (cmd[1] == ini[cmd[2]]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}
bool eqri() { // 15
    return (ini[cmd[1]] == cmd[2]) 
            ? fin[cmd[3]] == 1
            : fin[cmd[3]] == 0;
}

int main() 
{
    int total = 0;

    std::vector<bool(*)()> op;
    op.push_back(addr); op.push_back(addi); op.push_back(mulr); op.push_back(muli);
    op.push_back(banr); op.push_back(bani); op.push_back(borr); op.push_back(bori);
    op.push_back(setr); op.push_back(seti); op.push_back(gtrr); op.push_back(gtir);
    op.push_back(gtri); op.push_back(eqrr); op.push_back(eqir); op.push_back(eqri);

    while (scanf("Before: [%d, %d, %d, %d]\n", &ini[0],&ini[1],&ini[2],&ini[3]) != EOF)
    {
        scanf("%d %d %d %d\n", &cmd[0],&cmd[1],&cmd[2],&cmd[3]);
        scanf("After: [%d, %d, %d, %d]\n", &fin[0],&fin[1],&fin[2],&fin[3]);
        scanf("\n");

        int num = 0;
        for (int i = 0; i < 16; i++) {
            if (op[i]()) num++;
        }

        if (num >= 3) total++;
    }
    cout << "Total: " << total << endl;
}
