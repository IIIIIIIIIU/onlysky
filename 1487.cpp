#include <bits/stdc++.h>
using namespace std;
const int maxn=100005,maxm=400005,INF=0x3f3f3f3f;
int n,m,head[maxn],E[maxm],V[maxm],W[maxm],cnt=1,f[maxn],g[maxn];
int dfn[maxn],ci[maxn],fa[maxn],tag;
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}
void dping(int now,int tmp)
{
    int ans0=0,ans1=0,now0=0,now1=0;
    for(int i=tmp;i!=now;i=fa[i])
    {
        now0=ans0+g[i],now1=ans1+f[i];
        ans0=max(now0,now1);ans1=now0;
    }
    g[now]+=ans0,ans0=0,ans1=-INF;
    for(int i=tmp;i!=now;i=fa[i])
    {
        now0=ans0+g[i],now1=ans1+f[i];
        ans0=max(now0,now1);ans1=now0;
    }
    f[now]+=ans1;
}
void dfs(int now)
{
    dfn[now]=++tag;
    for(int i=head[now];i;i=E[i])
    {
        int v=V[i];
        if(!dfn[v]) fa[v]=now,dfs(v);
    }
    f[now]=ci[now];
    for(int i=head[now];i;i=E[i])
    {
        int v=V[i];
        if(fa[v]!=now&&dfn[now]<dfn[v]) dping(now,v);
    }
}
int main()
{
    in(n),in(m);int u,v;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v);
        E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
    }
    for(int i=1;i<=n;i++) in(ci[i]);
    dfs(1);
    cout<<max(f[1],g[1]);
    return 0;
}
