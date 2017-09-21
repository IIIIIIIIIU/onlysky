#include <bits/stdc++.h>
const int maxn=500005;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();                   
}
namespace P
{
    struct EdgeType
    {
        int u,v;
    };
    struct EdgeType e[maxn];
    int size[maxn],col,bel[maxn],head[maxn],ci[maxn];
    int val[maxn],tag,dfn[maxn],low[maxn],sta[maxn],top,n,m;
    int V[maxn],E[maxn],cnt,S,p,Sg;
    bool has[maxn],had[maxn];
    void dfs(int now)
    {
        dfn[now]=low[now]=++tag,sta[++top]=now;
        for(int i=head[now];i;i=E[i])
        {
            if(bel[V[i]]) continue;
            if(!dfn[V[i]]) dfs(V[i]),low[now]=std::min(low[now],low[V[i]]);
            else low[now]=std::min(low[now],dfn[V[i]]);
        }
        if(low[now]==dfn[now])
        {
            col++;
            while(sta[top]!=now)
            {
                bel[sta[top]]=col;
                had[col]|=has[sta[top]];
                val[col]+=ci[sta[top]];
                if(sta[top]==S) Sg=col;
                top--;
            }
            bel[now]=col;
            had[col]|=has[sta[top]];
            val[col]+=ci[sta[top]];
            if(now==S) Sg=col;
            top--;
        }
    }
    void pre()
    {
        in(n),in(m);int u,v;
        for(int i=1;i<=m;i++)
        {
            in(u),in(v);
            e[i].u=u,e[i].v=v;
            E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        }
        for(int i=1;i<=n;i++) in(ci[i]);
        in(S),in(p);
        while(p--) in(u),has[u]=true;
        for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i);
    }
}
namespace solve
{
    int head[maxn],E[maxn],V[maxn],cnt,ci[maxn],S,f[maxn],n,du[maxn];
    int que[maxn],ans;
    bool can[maxn],has[maxn];
    std::map<int,int>Map[maxn];
    void dfs(int now)
    {
        can[now]=true;
        for(int i=head[now];i;i=E[i])
        {
            du[V[i]]++;
            if(!can[V[i]]) dfs(V[i]);
        }
    }
    void pre()
    {
        n=P::col,S=P::Sg;int u,v;
        for(int i=1;i<=P::m;i++)
        {
            u=P::bel[P::e[i].u],v=P::bel[P::e[i].v];
            if(u!=v&&(Map[u][v]+=1)==1) E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        }
        for(int i=1;i<=n;i++) ci[i]=P::val[i],has[i]=P::had[i];
        dfs(S);
        int h=0,tail=1;que[0]=S;
        while(h<tail)
        {
            int now=que[h++];
            f[now]+=ci[now];
            if(has[now]) ans=std::max(ans,f[now]);
            for(int i=head[now];i;i=E[i])
                if(can[V[i]])
                {
                    f[V[i]]=std::max(f[V[i]],f[now]);
                    if(--du[V[i]]==0) que[tail++]=V[i];
                }
        }
        std::cout<<ans;
    }
}
int main()
{
    P::pre();
    solve::pre();
    return 0;
}
