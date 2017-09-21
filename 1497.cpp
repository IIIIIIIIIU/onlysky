#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 55005
#define maxm 1005005
#define INF 0x7fffffff
 
int deep[maxn],que[maxm],F[maxm],cnt=1;
int n,m,s,t=maxn-1,head[maxn],E[maxm],V[maxm];
 
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
    memset(deep,-1,sizeof(deep));
    int h=0,tail=1;que[0]=s,deep[s]=0;
    while(h<tail)
    {
        int now=que[h++];
        for(int i=head[now];i;i=E[i])
        {
            if(F[i]>0&&deep[V[i]]<0)
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
        if(F[i]>0&&deep[V[i]]==deep[now]+1)
        {
            int pos=flowing(V[i],min(flow,F[i]));
            flow-=pos,oldflow+=pos;
            F[i]-=pos,F[i^1]+=pos;
            if(flow==0) return oldflow;
        }
    }
    if(oldflow==0) deep[now]=-1;
    return oldflow;
}
 
int main()
{
    in(n),in(m);int pos,u,v,sum=0;
    for(int i=1;i<=n;i++) in(pos),edge_add(s,i,pos);
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),in(pos);
        sum+=pos;
        edge_add(u,i+n,INF);
        edge_add(v,i+n,INF);
        edge_add(i+n,t,pos);
    }
    pos=0;while(bfs()) pos+=flowing(s,INF);
    cout<<sum-pos;
    return 0;
}
