#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
int n;
 
inline int R()
{
    int now=0;char Cget=getchar();
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    return now;
}
 
int main()
{
    while(n=R()) n&1?printf("Bob\n"):printf("Alice\n");
    return 0;
}
