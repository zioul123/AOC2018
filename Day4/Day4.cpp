#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

// Hold the date inputs, able to sort by date
struct Date {
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

// Compare by first element in a pair
bool pairCompare(const std::pair<Date, string>& firstElem, 
                 const std::pair<Date, string>& secondElem) {
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
    unordered_map<int, int> hoursSleeping;
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
                break;
            case 'f':
                sleepSince = (*it).first.m;
                break;
            case 'w':
                int sleepFor = (*it).first.m - sleepSince;
                hoursSleeping[currentGuard] = hoursSleeping[currentGuard] + sleepFor;
                break;
        }
    }

    // Get the guard who slept the longest
    int longestMins = -1, longestGuard = -1;
    for (unordered_map<int,int>::iterator it = hoursSleeping.begin(); it != hoursSleeping.end();
        ++it) 
    {
        if ((*it).second > longestMins) {
            longestMins = (*it).second;
            longestGuard = (*it).first;
        }
    }
    cout << longestGuard << ", " << longestMins << endl;

    // Iterate through inputs and add total days per minute
    currentGuard = -1; sleepSince = -1;
    int sleepFor[60] = { 0 };   
    for (vector<pair<Date, string> >::iterator it = inputs.begin(); it != inputs.end();
        ++it) 
    {
        string s = (*it).second;
        char c = s[19];
        switch(c) 
        {
            case 'G':
                currentGuard = stoi(s.substr(26, 5));
                break;
            case 'f':
                if (currentGuard != longestGuard) continue;
                sleepSince = (*it).first.m;
                break;
            case 'w':
                if (currentGuard != longestGuard) continue;
                int sleepTill = (*it).first.m;
                for (int i = sleepSince; i < sleepTill; i++) {
                    sleepFor[i]++;
                }
                break;
        }
    }

    // Check which minute he spent the most sleeping in
    int sleepingMin = -1; int mostSleep = -1;
    for (int i = 0; i < 60; i++) {
        if (sleepFor[i] > mostSleep) {
            mostSleep = sleepFor[i];
            sleepingMin = i;
        }
    }

    cout << (longestGuard * sleepingMin) << endl;


}