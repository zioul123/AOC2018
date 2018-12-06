#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Hold the date inputs, able to sort by date
struct Date 
{
    int Y, M, D, h, m;
    Date(int _Y, int _M, int _D, int _h, int _m) :
        Y(_Y), M(_M), D(_D), h(_h), m(_m) {}

    bool operator < (const Date& date) const
    {
        return Y != date.Y ? Y < date.Y
             : M != date.M ? M < date.M 
             : D != date.D ? D < date.D 
             : h != date.h ? h < date.h 
             : m < date.m;
    }
};

class Guard 
{
public:
    int id;
    int sleepFor[60] = {0};
    Guard() {}
    Guard(int _id) : id(_id) {}
    int longestMinute();
    int sleptAtMost();
};

int Guard::sleptAtMost()
{
    int result = -1;
    for (int i=0; i<60; i++) 
        if (sleepFor[i] > result) 
            result = sleepFor[i];
    return result;
}

int Guard::longestMinute() 
{
    int result = -1, minute = -1;
    for (int i=0; i<60; i++) 
    {
        if (sleepFor[i] > result) 
        {
            result = sleepFor[i];
            minute = i;
        }
    }
    return minute;
}

// Compare by first element in a pair
bool pairCompare(const std::pair<Date, string>& firstElem, 
                 const std::pair<Date, string>& secondElem) 
{
  return firstElem.first < secondElem.first;
}

int main()
{
    vector<pair<Date, string> > inputs;

    // Read all inputs and store them
    string s;
    while (getline(cin, s))
    {
        if (s.empty()) break;

        Date d(stoi(s.substr(1,4)), stoi(s.substr(6, 2)), stoi(s.substr(9, 2)),
            stoi(s.substr(12, 2)), stoi(s.substr(15, 2)));

        // cout << d.Y << ", " << d.M << ", " << d.D << ", " << d.h << ", " << d.m << endl;
        inputs.push_back(pair<Date, string>(d, s));
    }

    // Sort by date
    sort(inputs.begin(), inputs.end(), pairCompare);

    // Add all the sleeping hours per guard
    unordered_map<int, Guard> guards;
    int currentGuard = -1, sleepSince = -1;
    for (vector<pair<Date, string> >::iterator it = inputs.begin(); it != inputs.end();
        ++it) 
    {
        string s = (*it).second;
        char c = s[19];
        switch(c) 
        {
            case 'G':
                currentGuard = stoi(s.substr(26, 5));
                if (guards.find(currentGuard) == guards.end()) 
                {
                    Guard g(currentGuard);
                    guards[currentGuard] = g;
                }
                break;
            case 'f':
                sleepSince = (*it).first.m;
                break;
            case 'w':
                int sleepTill = (*it).first.m;
                for (int i=sleepSince; i<sleepTill; ++i) 
                    ++guards[currentGuard].sleepFor[i];
                break;
        }
    }

    for (unordered_map<int, Guard>::iterator it = guards.begin(); it != guards.end(); ++it) 
    {
        cout << (*it).first << ": " << (*it).second.sleepFor << endl;
        cout << "Most: " << (*it).second.sleptAtMost() << ", Minute: " << (*it).second.longestMinute() << endl;
    }

    // Check which minute he spent the most sleeping in
    int sleepingGuard = -1; int mostSleep = -1;
    for (unordered_map<int, Guard>::iterator it = guards.begin(); it != guards.end(); ++it) 
    {
        if ((*it).second.sleptAtMost() > mostSleep)
        {
            mostSleep = (*it).second.sleptAtMost();
            sleepingGuard = (*it).first;
        }
    }
    int sleepingMin = guards[sleepingGuard].longestMinute();

    cout << (sleepingGuard * sleepingMin) << endl;
}