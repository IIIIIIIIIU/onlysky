#include <cstdio>
#include <cstring>
#include <iostream>
 
using namespace std;
 
#define maxn 20005
#define maxm 200005
#define INF 0x7ffffff
 
const int dx[5]={0,-1,0,1,0};
const int dy[5]={0,0,1,0,-1};
 
int s,t,cnt=1,size,que[maxm],deep[maxn],n,m;
int head[maxn],E[maxm],V[maxm],F[maxm],map[105][105];
 
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
 
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1;que[h]=s,deep[s]=0;
    while(h<tail)
    {
        int now=que[h++];
        for(int i=head[now];i;i=E[i])
        {
            if(deep[V[i]]<0&&F[i]>0)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que[tail++]=V[i];
            }
        }
    }
    return false;
}
 
int flowing(int now,int flow)
{
    if(now==t||flow<=0) return flow;
    int oldflow=0;
    for(int i=head[now];i;i=E[i])
    {
        if(deep[V[i]]==deep[now]+1&&F[i]>0)
        {
            int pos=flowing(V[i],min(flow,F[i]));
            F[i]-=pos,F[i^1]+=pos;
            flow-=pos,oldflow+=pos;
            if(flow==0) return oldflow;
        }
    }
    if(oldflow==0) deep[now]=-1;
    return oldflow;
}
 
int main()
{
    scanf("%d%d",&n,&m);
    size=n*m,t=size+1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++) scanf("%d",&map[i][j]);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(map[i][j]==1) edge_add(s,(i-1)*m+j,INF);
            if(map[i][j]==2) edge_add((i-1)*m+j,t,INF);
            for(int v=1;v<=4;v++)
            {
                int xx=i+dx[v],yy=j+dy[v];
                if(xx>0&&xx<=n&&yy>0&&yy<=m)
                {
                    if(map[i][j]!=1||map[xx][yy]!=1) edge_add((i-1)*m+j,(xx-1)*m+yy,1);
                }
            }
        }
    }
    int ans=0;
    while(bfs()) ans+=flowing(s,INF);
    cout<<ans;
    return 0;
}
