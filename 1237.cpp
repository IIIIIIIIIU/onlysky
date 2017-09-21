#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=100005,INF=0x3f3f3f3f;
ll n,dp[maxn],ai[maxn],bi[maxn];
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
ll get(ll x,ll y)
{
    return (x==y)?INF:abs(x-y);
}
int main()
{
    in(n);ll tmp;
    for(ll i=1;i<=n;i++) in(ai[i]),in(bi[i]);
    sort(ai+1,ai+n+1),sort(bi+1,bi+n+1);
    dp[1]=get(ai[1],bi[1]),dp[2]=min(dp[1]+get(ai[2],bi[2]),get(ai[1],bi[2])+get(ai[2],bi[1]));
    for(ll i=3;i<=n;i++)
    {
        tmp=min(dp[i-1]+get(ai[i],bi[i]),dp[i-2]+get(ai[i-1],bi[i])+get(ai[i],bi[i-1]));
        tmp=min(min(dp[i-3]+get(ai[i-2],bi[i-1])+get(ai[i-1],bi[i])+get(ai[i],bi[i-2]),
                dp[i-3]+get(ai[i],bi[i-1])+get(ai[i-1],bi[i-2])+get(ai[i-2],bi[i])),tmp);
        dp[i]=tmp;
    }
    cout<<dp[n];
    return 0;
}
