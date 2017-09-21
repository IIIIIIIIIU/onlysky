#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 10005
#define maxm 2000005
#define INF 0x7fffffff
 
int n,s,t,head[maxn<<2],E[maxm],V[maxm],F[maxm],cnt=1;
int ai[maxn],bi[maxn],m,que[maxm<<2],deep[maxn<<2],ans;
 
bool if_[maxn<<2];
 
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
 
inline bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1,if_[i]=false;
    int h=0,tail=1;deep[s]=0,que[0]=s,if_[s]=true;
    while(h<tail)
    {
        int now=que[h++];if_[now]=false;
        for(int i=head[now];i;i=E[i])
        {
            if(F[i]>0&&deep[V[i]]<0)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                if(!if_[V[i]]) que[tail++]=V[i],if_[V[i]]=true;
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
        if(F[i]<=0||deep[V[i]]!=deep[now]+1) continue;
        int pos=flowing(V[i],min(F[i],flow));
        F[i]-=pos,F[i^1]+=pos;
        flow-=pos,oldflow+=pos;
        if(flow==0) return oldflow;
    }
    if(oldflow==0) deep[now]=-1;
    return oldflow;
}
 
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(ai[i]),ans+=ai[i];
    for(int i=1;i<=n;i++) in(bi[i]),ans+=bi[i];
    in(m),t=n+m*2+1;
    for(int i=1;i<=m;i++)
    {
        int ki,cia,cib,pos;
        in(ki),in(cia),in(cib),ans+=cia,ans+=cib;
        edge_add(s,n+i,cia);
        edge_add(n+m+i,t,cib);
        for(int j=1;j<=ki;j++)
        {
            in(pos);
            edge_add(n+i,pos,INF);
            edge_add(pos,n+m+i,INF);
        }
    }
    for(int i=1;i<=n;i++)
    {
        edge_add(s,i,ai[i]);
        edge_add(i,t,bi[i]);
    }
    while(bfs()) ans-=flowing(s,INF);
    cout<<ans;
    return 0;
}
