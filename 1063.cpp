#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=100005;
ll n,m,mod,head[maxn],E[maxn<<1],V[maxn<<1],dp[maxn][11][3],cnt;
inline ll get(ll x)
{
    if(x==0) return 0;
    if(x%mod==0) return mod;
    return x%mod;
}
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs(ll now,ll fa)
{
    bool did=true;
    for(ll i=head[now];i;i=E[i])
    {
        if(fa==V[i]) continue;
        dfs(V[i],now),did=false;
    }
    for(ll i=0;i<=10;i++) dp[now][i][0]=1;
    if(did) return;
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        ll to=V[i];
        for(ll v=0;v<=10;v++)
        {
            ll tmp1=0,tmp2,tmp3;
            if(v) tmp1=dp[to][v-1][0]+dp[to][v-1][1]+dp[to][v-1][2];
            tmp2=dp[to][v][0]+dp[to][v][1];
            tmp3=dp[now][v][2]*tmp1+dp[now][v][1]*tmp2;
            dp[now][v][2]=get(tmp3);
            tmp3=dp[now][v][1]*tmp1+dp[now][v][0]*tmp2;
            dp[now][v][1]=get(tmp3);
            tmp3=dp[now][v][0]*tmp1;
            dp[now][v][0]=get(tmp3);
        }
    }
}
int main()
{
    in(n),in(m),in(mod);
    if(m<n-1)
    {
        printf("-1\n-1");
        return 0;
    }
    ll u,v;
    for(ll i=1;i<=m;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    dfs(1,0);
    ll tmp;
    for(ll i=0;i<=10;i++)
    {
        tmp=get(dp[1][i][0]+dp[1][i][1]+dp[1][i][2]);
        if(tmp)
        {
            printf("%lld\n%lld\n",i,tmp%mod);
            return 0;
        }
    }
    return 0;
}
