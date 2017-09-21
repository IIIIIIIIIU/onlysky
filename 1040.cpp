#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN=1000005;
ll n,f[MAXN],head[MAXN],V[MAXN<<1],E[MAXN<<1],cnt=1;
ll val[MAXN],dfn[MAXN],low[MAXN],tag,dp[MAXN][2],ai[MAXN];
ll sta[MAXN],top,num,bi[MAXN][2],ans=0,ans2;
bool vis[MAXN];
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs(ll now,ll last)
{
    dfn[now]=low[now]=++tag,sta[++top]=now;
    for(ll i=head[now];i;i=E[i])
    {
        if(i==last||i==(last^1)) continue;
        if(!dfn[V[i]]) dfs(V[i],i),low[now]=min(low[now],low[V[i]]);
        else low[now]=min(low[now],dfn[V[i]]),vis[V[i]]=true;
    }
    if(low[now]==dfn[now])
        if(!vis[now]) top--;
        else
        {
            while(sta[top]!=now) ai[++num]=sta[top--],vis[ai[num]]=true;
            top--,ai[++num]=now;
        }
}
void dping(ll now,ll fa)
{
    dp[now][0]=0,dp[now][1]=val[now];
    for(ll i=head[now];i;i=E[i])
    {
        if(vis[V[i]]||V[i]==fa) continue;
        dping(V[i],now);
        dp[now][0]+=max(dp[V[i]][1],dp[V[i]][0]);
        dp[now][1]+=dp[V[i]][0];
    }
    vis[now]=true;
}
int main()
{
    in(n);ll u,v;
    for(ll i=1;i<=n;i++)
    {
        in(val[i]),in(v),u=i;
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    for(int i=1;i<=n;i++)
    {
        if(vis[i]) continue;
        top=0,num=0,dfs(i,0),ans=0;
        for(ll i=1;i<=num;i++) dping(ai[i],0);
        bi[1][0]=dp[ai[1]][0],bi[1][1]=0;
        for(ll i=2;i<=num;i++)
        {
            bi[i][0]=dp[ai[i]][0];
            bi[i][1]=dp[ai[i]][1];
            bi[i][0]+=max(bi[i-1][0],bi[i-1][1]);
            bi[i][1]+=bi[i-1][0];
        }
        ans=max(bi[num][1],bi[num][0]);
        bi[1][0]=0,bi[1][1]=dp[ai[1]][1];
        for(ll i=2;i<=num;i++)
        {
            bi[i][0]=dp[ai[i]][0];
            bi[i][1]=dp[ai[i]][1];
            bi[i][0]+=max(bi[i-1][0],bi[i-1][1]);
            bi[i][1]+=bi[i-1][0];
        }
        ans=max(ans,bi[num][0]);
        ans2+=ans;
    }
    cout<<ans2;
    return 0;
}
