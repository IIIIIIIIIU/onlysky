#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
const int maxm=1000005;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
namespace Tarjan
{
    struct EdgeType
    {
        int u,v;
    };
    struct EdgeType e[maxm];
    int head[maxn],E[maxm],V[maxm],cnt,size[maxn],bel[maxn];
    int dfn[maxn],low[maxn],sta[maxn],top,tag,n,m,mod,col;
    void tarjan(int now)
    {
        dfn[now]=low[now]=++tag,sta[++top]=now;
        for(int i=head[now];i;i=E[i])
        {
            if(!bel[V[i]])
            {
                if(dfn[V[i]]) low[now]=min(low[now],dfn[V[i]]);
                else tarjan(V[i]),low[now]=min(low[now],low[V[i]]);
            }
        }
        if(low[now]==dfn[now])
        {
            col++;
            while(sta[top]!=now)
            {
                bel[sta[top]]=col;
                size[col]++,top--;
            }
            bel[now]=col,size[col]++;
            top--;
        }
    }
    void pre()
    {
        in(n),in(m),in(mod);int u,v;
        for(int i=1;i<=m;i++)
        {
            in(e[i].u),in(e[i].v),u=e[i].u,v=e[i].v;
            E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
        }
        for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    }
}
namespace Top
{
    int head[maxn],E[maxm],V[maxm],cnt,size[maxn],du[maxn];
    int que[maxn],n,mod,ans1,ans2,f[maxn],du2[maxn],deep[maxn];
    int dp[maxn];
    map<int,int>has[maxn];
    void pre()
    {
        int u,v;
        n=Tarjan::col;
        mod=Tarjan::mod;
        for(int i=1;i<=n;i++) size[i]=Tarjan::size[i];
        for(int i=1;i<=Tarjan::m;i++)
        {
            u=Tarjan::bel[Tarjan::e[i].u];
            v=Tarjan::bel[Tarjan::e[i].v];
            if(u!=v&&(has[u][v]+=1)==1)
                E[++cnt]=head[u],V[cnt]=v,head[u]=cnt,du[v]++;
        }
        int h=0,tail=0;
        for(int i=1;i<=n;i++) if(!(du2[i]=du[i])) que[tail++]=i;
        while(h<tail)
        {
            int now=que[h++];f[now]+=size[now];
            for(int i=head[now];i;i=E[i])
            {
                f[V[i]]=max(f[V[i]],f[now]),du[V[i]]--;
                if(!du[V[i]]) que[tail++]=V[i];
            }
        }
        for(int i=1;i<=n;i++) ans1=max(ans1,f[i]);
        h=0,tail=0;
        for(int i=1;i<=n;i++) if(!du2[i]) que[tail++]=i,dp[i]=1;
        while(h<tail)
        {
            int now=que[h++];deep[now]+=size[now];
            for(int i=head[now];i;i=E[i])
            {
                du2[V[i]]--;
                if(!du2[V[i]]) que[tail++]=V[i];
                if(deep[V[i]]==deep[now]) dp[V[i]]=(dp[V[i]]+dp[now])%mod;
                else if(deep[V[i]]<deep[now]) dp[V[i]]=dp[now],deep[V[i]]=deep[now];
            }
        }
        for(int i=1;i<=n;i++) if(ans1==f[i]) ans2=(ans2+dp[i])%mod;
        std::cout<<ans1<<endl<<ans2;
    }
}
int main()
{
    Tarjan::pre();
    Top::pre();
    return 0;
}
