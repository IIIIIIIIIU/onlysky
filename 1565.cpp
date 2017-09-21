#include <bits/stdc++.h>
const int BUF = 10000010;
char Buf[10000010], *buf = Buf;
void in(int &now)
{
    int temp=0;
    for(now=0;!isdigit(*buf);++buf)if(*buf=='-')temp=1;
    for(;isdigit(*buf);now=now*10+*buf-'0',++buf);
    if(temp) now=-now;
}
/*
inline void in(int &now)
{
    char Cget;now=0;int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
    now*=if_z;
}*/
namespace P
{
    using std::min;
    int val[605],ci[605],n,m,id[50][50],cnt,head[605];
    int E[200005],V[200005],size[605],bel[605],col;
    int dfn[605],low[605],tag,sta[605],top,edge[605][605];
    bool can[605],vis[605];
    void tarjan(int now)
    {
        dfn[now]=low[now]=++tag,sta[++top]=now;
        for(int i=head[now];i;i=E[i])
            if(!bel[V[i]])
                if(dfn[V[i]]) low[now]=min(low[now],dfn[V[i]]);
                else tarjan(V[i]),low[now]=min(low[now],low[V[i]]);
        if(dfn[now]==low[now])
        {
            col++;
            while(sta[top]!=now) bel[sta[top]]=col,size[col]++,top--;
            bel[now]=col,size[col]++,top--;
        }
    }
    void dfs(int now)
    {
        if(vis[now]) return;
        vis[now]=true,can[now]=true;
        for(int i=1;i<=n*m;i++)
            if(edge[i][now]) dfs(i);
    }
    void Main()
    {
        in(n),in(m);
        for(int i=1;i<=n;i++)
            for(int v=1;v<=m;v++) id[i][v]=++cnt;
        cnt=0;int u,v;
        for(int i=1;i<=n;i++)
            for(int e=1;e<m;e++)
            {
                u=id[i][e],v=id[i][e+1];
                E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
                edge[u][v]=1;
            }
        int num,x,y;
        for(int i=1;i<=n*m;i++)
        {
            in(ci[i]),in(num);
            while(num--)
            {
                in(x),in(y);
                u=id[x+1][y+1],v=i;
                E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
                edge[u][v]=1;
            }
        }
        for(int i=1;i<=n*m;i++)
            if(!dfn[i]) tarjan(i);
//      for(int i=1;i<=n*m;i++) printf("%d ",size[bel[i]]);
        for(int i=1;i<=n;i++)
            for(int e=m;e>=1;e--)
                if(size[bel[id[i][e]]]>1||can[id[i][e]])
                {
                    for(int t=e;t>=1;t--) can[id[i][t]]=true,dfs(id[i][t]);
                    break;
                }
    }
}
namespace S
{
    using P::n;
    using P::m;
    using P::ci;
    using P::can;
    using P::edge;
    using std::min;
    using std::cout;
    const int INF=0x3f3f3f3f;
    int head[605],V[300005],E[300005],F[300005],s,t,cnt=1,ans,que[605];
    int deep[605];
    inline void edge_add(int u,int v,int f)
    {
        E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
        E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
    }
    bool bfs()
    {
        for(int i=s;i<=t;i++) deep[i]=-1;
        int h=0,tail=1,now;que[0]=s,deep[s]=0;
        while(h<tail)
            for(int i=head[now=que[h++]];i;i=E[i])
                if(F[i]&&deep[V[i]]<0)
                {
                    deep[V[i]]=deep[now]+1;
                    if(V[i]==t) return true;
                    que[tail++]=V[i];
                }
        return false;
    }
    int flowing(int now,int flow)
    {
        if(now==t||flow<=0) return flow;
        int oldflow=0,tmp;
        for(int i=head[now];i;i=E[i])
            if(F[i]&&deep[V[i]]==deep[now]+1)
            {
                tmp=flowing(V[i],min(F[i],flow));
                flow-=tmp,oldflow+=tmp,F[i]-=tmp,F[i^1]+=tmp;
                if(!flow) return oldflow;
            }
        if(flow) deep[now]=-1;
        return oldflow;
    }
    void Main()
    {
        s=0,t=n*m+1;
        for(int i=1;i<=n*m;i++)
            for(int e=1;e<=n*m;e++)
            {
                if(can[i]||can[e]) continue;
                if(edge[i][e])
                    edge_add(i,e,INF);
            }
        for(int i=1;i<=n*m;i++)
        {
            if(can[i]) continue;
//          cout<<ci[i]<<' ';
            if(ci[i]>=0) edge_add(s,i,ci[i]),ans+=ci[i];
            else edge_add(i,t,-ci[i]);
        }
        while(bfs()) ans-=flowing(s,INF);
        cout<<ans;
    }
}
int main()
{
//  freopen("data.txt","r",stdin);
//  freopen("pvz.in","r",stdin);
//  freopen("pvz.out","w",stdout);
    fread(buf,1,BUF,stdin);
    P::Main();
    S::Main();
    return 0;
}
