#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=10005,maxm=2505;
struct edge
{
    int u,v;
};
struct edge Edge[maxn];
int bel[maxn],n,m,col,hi[maxn],yi[maxn],head[maxn],tag,dp[maxn][maxm];
int E[maxn<<1],V[maxn<<1],cnt,ci[maxn],vi[maxn],dfn[maxn],low[maxn];
int sta[maxn],top,num;
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void tarjan(int now)
{
    dfn[now]=low[now]=++tag,sta[++top]=now;
    for(int i=head[now];i;i=E[i])
        if(!bel[V[i]])
            if(dfn[V[i]]) low[now]=min(low[now],dfn[V[i]]);
            else tarjan(V[i]),low[now]=min(low[now],low[V[i]]);
    if(low[now]==dfn[now])
    {
        col++;
        while(sta[top]!=now)
        {
            bel[sta[top]]=col;
            vi[col]+=yi[sta[top]];
            ci[col]+=hi[sta[top]];
            top--;
        }
        bel[now]=col,vi[col]+=yi[now],ci[col]+=hi[now],top--;
    }
}
/*
void dfs(int now)
{
    for(int i=head[now];i;i=E[i])
    {
        dfs(V[i]);
        for(int v=m-vi[now];v>=0;v--)
            for(int e=0;e<=v;e++)
                dp[now][v]=max(dp[now][v],dp[now][e]+dp[V[i]][v-e]);
    }
    for(int v=m;v>=vi[now];v--)
        dp[now][v]=dp[now][v-vi[now]]+ci[now];
    if(vi[now]) for(int v=vi[now]-1;v>=0;v--) dp[now][v]=0;
}
*/
void dfs(int now,int lit)
{
    if(lit<=0) return;
    int v;
    for(int i=head[now];i;i=E[i])
        if(lit>=vi[V[i]])
        {
            v=V[i];
            for(int e=0;e<=lit;e++)
                dp[v][e]=dp[now][e];
            dfs(v,lit-vi[v]);
            for(int e=lit;e>=vi[v];e--)
                dp[now][e]=max(dp[now][e],dp[v][e-vi[v]]+ci[v]);
        }
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++) in(yi[i]);
    for(int i=1;i<=n;i++) in(hi[i]);
    int u,v;
    for(int i=1;i<=n;i++)
    {
        in(u),v=i;
        if(u!=0)
        {
            E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        }
        Edge[i].u=u,Edge[i].v=v;
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
    num=n,cnt=0;
    memset(head,0,sizeof(head));
    for(int i=1;i<=num;i++)
        if(bel[Edge[i].u]!=bel[Edge[i].v])
        {
            if(Edge[i].u!=0)
            {
                E[++cnt]=head[bel[Edge[i].u]];
                V[cnt]=bel[Edge[i].v];
                head[bel[Edge[i].u]]=cnt;
                vis[bel[Edge[i].v]]=true;
            }
            else
            {
                E[++cnt]=head[n+1];
                V[cnt]=bel[Edge[i].v];
                vis[bel[Edge[i].v]]=true;
                head[n+1]=cnt;
            }
        }
    for(int i=1;i<=col;i++)
        if(!vis[i])
        {
            E[++cnt]=head[n+1];
            V[cnt]=i;
            head[n+1]=cnt;
        }
//  dfs(n+1);
    dfs(n+1,m);
    cout<<dp[n+1][m];
    return 0;
}
