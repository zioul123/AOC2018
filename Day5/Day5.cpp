#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <ctype.h>

using namespace std;

int main() 
{
    string input;
    getline(cin, input);
    
    stack<char> s;

    for (int i=0; i<input.size(); i++) 
    {
        char c = input[i];
        if (s.size() == 0) 
            s.push(c);
        else if (tolower(c) == tolower(s.top()))
        {
            char c2 = s.top();
            if ((islower(c) && islower(c2))
                    || (isupper(c) && isupper(c2)))
                s.push(c);
            else
                s.pop();
        }
        else
            s.push(c);
    }
    cout << s.size() << endl;
}