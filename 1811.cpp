#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF=1e17;
ll n,Max=INF,Min=-INF,now,x,y;
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++,y=x)
    {
        in(x);
        if(i&1) Max=min(Max,now+=x-y);
        else Min=max(Min,now+=y-x);
    }
    if(Max<Min) cout<<0;
    else cout<<Max-Min+1;
    return 0;
}
