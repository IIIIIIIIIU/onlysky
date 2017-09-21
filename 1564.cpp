#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e17;
struct node
{
    ll d,v,p;
    bool operator<(const node &pos)const
    {
        return d<pos.d;
    }
};
struct node ai[101];
ll n,k,dp[101][101][101],bi[101],cnt,sum[101];
bool vis[101][101][101];
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
ll dfs(ll l,ll r,ll w)
{
    if(r<l) return 0;
    if(vis[l][r][w]) return dp[l][r][w];
    vis[l][r][w]=true,dp[l][r][w]=INF;
    for(ll v=l;v<=r;v++)
    {
        dp[l][r][w]=min(dp[l][r][w],dfs(l,v-1,w)+dfs(v+1,r,w)+k+sum[r]-sum[l-1]);
        if(ai[v].v>=w) dp[l][r][w]=min(dp[l][r][w],dfs(l,v-1,ai[v].v)+dfs(v+1,r,ai[v].v)+sum[r]-sum[l-1]);
    }
    return dp[l][r][w];
}
int main()
{
    in(n),in(k);
    for(ll i=1;i<=n;i++) in(ai[i].d);
    for(ll i=1;i<=n;i++) in(ai[i].v),bi[++cnt]=ai[i].v;
    for(ll i=1;i<=n;i++) in(ai[i].p);
    sort(ai+1,ai+n+1),sort(bi+1,bi+cnt+1);
    cnt=unique(bi+1,bi+cnt+1)-bi-1;
    for(ll i=1;i<=n;i++)
    {
        ai[i].v=lower_bound(bi+1,bi+cnt+1,ai[i].v)-bi;
        sum[i]=sum[i-1]+ai[i].p;
    }
    ll ans=INF;
    for(ll i=1;i<=n;i++) ans=min(ans,dfs(1,n,i));
    cout<<ans;
    return 0;
}
