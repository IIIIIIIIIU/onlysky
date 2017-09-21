#include <bits/stdc++.h>
using namespace std;
#define maxn 2005
#define ll long long
ll n,k,dp[maxn][maxn],head[maxn],V[maxn<<1],E[maxn<<1],W[maxn<<1],cnt,size[maxn];
ll tmp[maxn];
inline void edge_add(ll u,ll v,ll w)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
}
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void dping(ll now,ll fa)
{
    size[now]=1;
    for(ll i=head[now];i;i=E[i])
    {
        if(V[i]==fa) continue;
        dping(V[i],now);
        ll y=V[i];
        for(ll v=0;v<=k;v++) tmp[v]=0;
        for(ll v=0;v<=min(k,size[now]);v++)
            for(ll e=0;e<=min(k,size[y]);e++)
                if(v+e<=k)
                tmp[v+e]=max(tmp[v+e],dp[now][v]+e*(k-e)*W[i]+(size[y]-e)*(n-k-size[y]+e)*W[i]+dp[y][e]);
        for(ll i=0;i<=k;i++) dp[now][i]=tmp[i];
        size[now]+=size[y];
    }
}
int main()
{
    in(n),in(k);ll u,v,w;
    for(ll i=1;i<n;i++)
    {
        in(u),in(v),in(w);
        edge_add(u,v,w);
    }
    dping(1,0);
    cout<<dp[1][k];
    return 0;
}
