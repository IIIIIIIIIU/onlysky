#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define maxn 105
#define INF 0x7fffffff
 
using namespace std;
 
struct EdgeType {
    int v,f,e;
};
struct EdgeType edge[maxn*maxn*4];
 
int n,home[maxn],s,t=maxn-1,deep[maxn],head[maxn],cnt,T;
 
char Cget;
 
inline void in(int &now)
{
    now=0,Cget=getchar();
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
inline void edge_add(int u,int v,int f)
{
    edge[++cnt].v=v,edge[cnt].f=f,edge[cnt].e=head[u],head[u]=cnt;
    edge[++cnt].v=u,edge[cnt].f=0,edge[cnt].e=head[v],head[v]=cnt;
}
 
bool bfs()
{
    queue<int>que;
    for(int i=s;i<=t;i++) deep[i]=-1;
    que.push(s),deep[s]=0;
    while(!que.empty())
    {
        int now=que.front();que.pop();
        for(int i=head[now];i;i=edge[i].e)
        {
            if(deep[edge[i].v]<0&&edge[i].f>0)
            {
                deep[edge[i].v]=deep[now]+1;
                if(edge[i].v==t) return true;
                que.push(edge[i].v);
            }
        }
    }
    return false;
}
 
int flowing(int now,int flow)
{
    if(now==t||flow<=0) return flow;
    int oldflow=0;
    for(int i=head[now];i;i=edge[i].e)
    {
        if(deep[edge[i].v]!=deep[now]+1||edge[i].f<=0) continue;
        int pos=flowing(edge[i].v,min(flow,edge[i].f));
        if(pos>0)
        {
            flow-=pos;
            oldflow+=pos;
            edge[i].f-=pos;
            edge[i^1].f+=pos;
            if(flow==0) return oldflow;
        }
    }
    if(oldflow==0) deep[now]=-1;
    return oldflow;
}
 
int main()
{
    in(T);
    while(T--)
    {
        in(n);int lit=n;cnt=1;
        for(int i=s;i<=t;i++) head[i]=0;
        for(int i=1;i<=n;i++)
        {
            in(home[i]);
            if(home[i]) edge_add(i+n,t,1);
        }
        int pos;
        for(int i=1;i<=n;i++)
        {
            in(pos);
            if(home[i])
            {
                if(!pos) edge_add(s,i,1);
                else lit--;
            }
            else edge_add(s,i,1);
        }
        for(int i=1;i<=n;i++)
        {
            if(home[i]) edge_add(i,i+n,1);
            for(int j=1;j<=n;j++)
            {
                in(pos);
                if(pos) edge_add(i,j+n,1);
            }
        }
        pos=0;
        while(bfs()) pos+=flowing(s,INF);
        if(pos>=lit) printf("^_^\n");
        else printf("T_T\n");
    }
    return 0;
}
