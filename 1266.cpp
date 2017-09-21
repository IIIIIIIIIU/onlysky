#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
const int maxm=500005;
const int INF=0x7fffffff;
struct EdgeType
{
    int u,v,t,c;
};
struct EdgeType e[maxm];
int n,m,dis[maxn][maxn],head[maxn],E[maxm],V[maxm],F[maxm],cnt=1;
int ans,deep[maxn],que[maxn],S,T;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
bool bfs()
{
    for(int i=S;i<=T;i++) deep[i]=-1;
    deep[S]=0,que[0]=S;int h=0,tail=1,now;
    while(h<tail)
        for(int i=head[now=que[h++]];i;i=E[i])
            if(F[i]&&deep[V[i]]<0)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==T) return true;
                que[tail++]=V[i];
            }
    return false;
}
int flowing(int now,int flow)
{
    if(now==T||flow<=0) return flow;
    int oldflow=0,tmp;
    for(int i=head[now];i;i=E[i])
        if(F[i]&&deep[V[i]]==deep[now]+1)
        {
            tmp=flowing(V[i],min(flow,F[i]));
            F[i]-=tmp,F[i^1]+=tmp,oldflow+=tmp,flow-=tmp;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
int main()
{
    in(n),in(m),S=1,T=n;
    memset(dis,127/3,sizeof(dis));
    for(int i=1;i<=m;i++)
    {
        in(e[i].u),in(e[i].v),in(e[i].t),in(e[i].c);
        dis[e[i].u][e[i].v]=dis[e[i].v][e[i].u]=min(dis[e[i].v][e[i].u],e[i].t);
    }
    for(int i=1;i<=n;i++) dis[i][i]=0;
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int v=1;v<=n;v++)
                dis[i][v]=min(dis[i][v],dis[i][k]+dis[k][v]);
    for(int i=1;i<=m;i++)
    {
        if(dis[1][e[i].u]+dis[e[i].v][n]+e[i].t==dis[1][n])
            edge_add(e[i].u,e[i].v,e[i].c);
        if(dis[1][e[i].v]+dis[e[i].u][n]+e[i].t==dis[1][n])
            edge_add(e[i].v,e[i].u,e[i].c);
    }
    while(bfs()) ans+=flowing(S,INF);
    cout<<dis[1][n]<<endl<<ans;
    return 0;
}
