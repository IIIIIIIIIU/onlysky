#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=200005;
ll n,m,dp[maxn][4],head[maxn],E[maxn<<1],V[maxn<<1],W[maxn<<1],f[maxn],ans;
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void dfs(ll now,ll fa)
{
    f[now]=fa;
    for(ll i=head[now];i;i=E[i])
        if(V[i]!=fa)
        {
            dfs(V[i],now);
            for(ll v=1;v<=3;v++)
            {
                ll tmp=dp[V[i]][v]+W[i];
                if(v>1&&dp[V[i]][v]==0) break;
                if(tmp>dp[now][1])
                {
                    dp[now][3]=dp[now][2];
                    dp[now][2]=dp[now][1];
                    dp[now][1]=tmp;
                    break;
                }
                else if(tmp>dp[now][2])
                {
                    dp[now][3]=dp[now][2];
                    dp[now][2]=tmp;
                    break;
                }
                else if(tmp>dp[now][3])
                {
                    dp[now][3]=tmp;
                    break;
                }
            }
        }
        ans=max(ans,dp[now][3]*2+dp[now][2]+dp[now][1]);
        ans=max(ans,dp[now][2]*2+dp[now][3]+dp[now][1]);
}
void dfs2(ll now,ll fa)
{
    ans=max(ans,f[now]+dp[now][1]+dp[now][2]*2);
    if(f[now]>=dp[now][1]) ans=max(ans,dp[now][1]*2+dp[now][2]+f[now]);
    if(dp[now][1]>f[now]) ans=max(ans,dp[now][1]+dp[now][2]+f[now]*2);
    ll tmp[5],bel[5];
    for(ll i=1;i<=4;i++) tmp[i]=bel[i]=0;
    for(ll i=head[now];i;i=E[i])
        if(fa!=V[i])
        {
            for(ll e=1;e<=3;e++)
            {
                ll pos=dp[V[i]][e]+W[i];
                if(!dp[V[i]][e]&&e>1) break;
                for(ll v=1;v<=4;v++)
                if(pos>=tmp[v])
                {
                    for(ll e=4;e>v;e--)
                    {
                        bel[e]=bel[e-1];
                        tmp[e]=tmp[e-1];
                    }
                    tmp[v]=pos,bel[v]=V[i];
                    break;
                }
            }
        }
    for(ll i=head[now];i;i=E[i])
        if(fa!=V[i])
        {
            f[V[i]]=W[i];
            for(ll v=1;v<=4;v++)
            {
                if(!bel[v]) break;
                if(bel[v]!=V[i])
                {
                    f[V[i]]+=tmp[v];
                    break;
                }
            }
            f[V[i]]=max(f[now]+W[i],f[V[i]]);
            dfs2(V[i],now);
        }
}
int main()
{
    in(n),in(m);
    ll u,v,w,cnt=0;
    for(ll i=1;i<=m;i++)
    {
        in(u),in(v),in(w);
        E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
    }
    dfs(1,0),dfs2(1,0);
    cout<<ans;
    return 0;
}
