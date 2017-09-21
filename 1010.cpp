#include <bits/stdc++.h>
using namespace std;
#define maxn 50005
#define ll long long
ll que[maxn],sum[maxn],dp[maxn],n,l,ai[maxn],a;
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
ll G(ll now)
{
    return sum[now]+now;
}
ll Y(ll x,ll y)
{
    return dp[x]+pow(G(x)+a,2)-dp[y]-pow(G(y)+a,2);
}
ll X(ll x,ll y)
{
    return 2*(G(x)-G(y));
}
int main()
{
    in(n),in(l),a=l+1;ll h=0,tail=0;
    for(ll i=1;i<=n;i++) in(ai[i]),sum[i]=sum[i-1]+ai[i];
    for(ll i=1;i<=n;i++)
    {
        while(h<tail&&Y(que[h+1],que[h])<=G(i)*X(que[h+1],que[h])) ++h;
        dp[i]=dp[que[h]]+(G(i)-G(que[h])-a)*(G(i)-G(que[h])-a);
        while(h<tail&&Y(i,que[tail])*X(que[tail],que[tail-1])<=Y(que[tail],que[tail-1])*X(i,que[tail])) --tail;
        que[++tail]=i;
    }
    cout<<dp[n];
    return 0;
}
