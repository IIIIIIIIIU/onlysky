#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
typedef long long ll;
const ll maxn=1000005;
ll n,xi[maxn],pi[maxn],ci[maxn],sumv[maxn],sump[maxn];
ll que[maxn],h=1,tail=1,dp[maxn];
inline void in(ll &now)
{
    char Cget;now=0;ll if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
real get(ll a,ll b)
{
    real up=dp[a]-dp[b]+sumv[a]-sumv[b];
    real down=sump[a]-sump[b];
    return up/down;
}
int main()
{
    in(n);
    for(ll i=1;i<=n;i++)
    {
        in(xi[i]),in(pi[i]),in(ci[i]);
        sumv[i]=sumv[i-1]+xi[i]*pi[i];
        sump[i]=sump[i-1]+pi[i];
    }
    for(ll i=1;i<=n;i++)
    {
        while(h<tail&&get(que[h],que[h+1])<xi[i]) h++;
        ll now=que[h];
        dp[i]=dp[now]+sumv[now]-sump[now]*xi[i]+sump[i]*xi[i]-sumv[i]+ci[i];
        while(tail>h&&get(que[tail-1],i)>get(que[tail],i)) tail--;
        que[++tail]=i;
    }
    cout<<dp[n];
    return 0;
}
