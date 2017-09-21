#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
struct DataType
{
    int p,w;
};
struct DataType q[maxn];
int head[maxn],E[maxn<<3],V[maxn<<3],cnt,n,m,ans,ai[maxn];
int dfn[maxn],low[maxn],f[maxn],fa[maxn],g[maxn],tag;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dp()
{
    int h=1,t=1;
    for(int i=1;i<=tag;i++) ai[tag+i]=ai[i];
    for(int i=1;i<=(tag<<1);i++)
    {
        while(h<t&&i-q[h].p>(tag>>1)) h++;
        while(h<t&&q[t].w<=f[ai[i]]-i) t--;
        q[++t].p=i,q[t].w=f[ai[i]]-i,ans=max(f[ai[i]]+i+q[h].w,ans);
    }
}
void dfs(int now)
{
    low[now]=dfn[now];
    for(int i=head[now];i;i=E[i])
    {
        int v=V[i];
        if(fa[v]&&v!=fa[now]) low[now]=min(low[now],dfn[v]);
        if(!fa[v]) fa[v]=now,dfn[v]=dfn[now]+1,dfs(v),low[now]=min(low[now],low[v]);
    }
    for(int i=head[now];i;i=E[i])
    {
        int v=V[i];
        if(fa[v]==now&&low[v]>dfn[now])
        {
            ans=max(ans,f[v]+1+f[now]);
            f[now]=max(f[now],f[v]+1);
        }
        if(fa[v]!=now&&dfn[now]<dfn[v])
        {
            tag=0;
            while(v!=fa[now]) ai[++tag]=v,v=fa[v];
            dp();
            for(int e=1;e<tag;e++) f[now]=max(f[now],f[ai[e]]+min(e,tag-e));
        }
    }
}
int main()
{
    in(n),in(m);int u,v,num;
    for(int i=1;i<=m;i++)
    {
        in(num),in(u);
        for(int e=2;e<=num;e++)
        {
            in(v);
            E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
            E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
            u=v;
        }
    }
    fa[1]=-1,dfs(1);
    cout<<ans;
    return 0;
}
