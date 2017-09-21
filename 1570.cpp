#include <bits/stdc++.h>
using namespace std;
const int maxn=5505,maxm=500505,INF=0x3f3f3f3f;
struct edge
{
    int u,v,f;
    edge(int u_=0,int v_=0,int f_=0)
    {
        u=u_,v=v_,f=f_;
    }
};
struct edge e[maxm];
int n,m,t,deep[maxn],que[maxn],head[maxn],E[maxm],V[maxm],F[maxm],cnt=1,S,T;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
bool bfs()
{
    memset(deep,-1,sizeof(deep));
    int h=0,tail=1,now;que[0]=S,deep[S]=0;
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
        if(F[i]&&deep[now]+1==deep[V[i]])
        {
            tmp=flowing(V[i],min(flow,F[i]));
            F[i]-=tmp,F[i^1]+=tmp,oldflow+=tmp,flow-=tmp;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
int main()
{
    in(n),in(m),in(t),T=(n+t)*n+1,S=0;
    int u,v,f;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),in(f);
        e[i]=edge(u,v,f);
    }
    int res=0;
    edge_add(S,1,t);
    for(int i=1;i<=n+t;i++)
    {
        for(int v=1;v<=m;v++)
            edge_add(i*n-n+e[v].u,i*n+e[v].v,e[v].f);
        for(int v=1;v<=n;v++)
            edge_add(i*n-n+v,i*n+v,INF);
        edge_add(i*n+n,T,INF);
        while(bfs())
            res+=flowing(S,INF);
        if(res==t)
        {
            cout<<i;
            return 0;
        }
    }
    return 0;
}
