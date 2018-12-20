#include <iostream>
#include <cstdio>

using namespace std;

int main() 
{
    int curr, res = 0;
    while (scanf("%d\n", &curr) != EOF) 
    {
        res += curr;
    }
    printf("%d\n", res);
}
