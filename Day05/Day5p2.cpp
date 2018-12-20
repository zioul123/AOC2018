#include <iostream>
#include <cstdio>
#include <string>
#include <stack>
#include <ctype.h>

using namespace std;

string filter(string s, char c)
{
    string res;
    for (int i=0; i<s.size(); i++) 
        if (tolower(s[i]) != c)
            res += s[i];
    return res;
}

int main() 
{
    string preinput;
    getline(cin, preinput);
    
    stack<char> s;
    int charScores[26] = {0};
    char chars[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r',
        's','t','u','v','w','x','y','z'};
    
    for (int cha=0; cha<26; cha++)
    {
        char selectedChar = chars[cha];
        string input = filter(preinput, selectedChar);
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
        cout << "Char: " << chars[cha] << ", " << s.size() << endl;
        charScores[cha] = s.size();
        s = stack<char>();
    }

    int min = 50000000; char cha = '!';
    for (int i = 0 ; i < 26; i++) {
        if (charScores[i] < min) {
            min = charScores[i];
            cha = chars[i];
        }
    }
    cout << cha << endl;
}