#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=1005,maxm=30005,INF=0x3f3f3f3f;
struct edge
{
    int u,v,w,f;
};
struct edge Edge[maxm];
int n,m,k,cnt=1,head[maxn],E[maxm],V[maxm],W[maxm],F[maxm],dis[maxn];
int s,t,deep[maxn],que[maxm*15],pre[maxn],ans;
bool vis[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
inline void edge_add(int u,int v,int w,int f)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,W[cnt]=-w,F[cnt]=0,head[v]=cnt;
}
bool bfs()
{
    for(int i=1;i<=n;i++) deep[i]=-1;
    int h=0,tail=1,now;que[0]=1,deep[1]=0;
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
            tmp=flowing(V[i],min(flow,F[i]));
            F[i]-=tmp,F[i^1]+=tmp,oldflow+=tmp,flow-=tmp;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
bool spfa()
{
    for(int i=0;i<=n;i++) dis[i]=INF,pre[i]=-1,vis[i]=false;
    int h=0,tail=1,now;que[0]=s,dis[s]=0,vis[s]=true;
    while(h<tail)
    {
        now=que[h++],vis[now]=false;
        for(int i=head[now];i;i=E[i])
            if(F[i]&&dis[now]+W[i]<dis[V[i]])
            {
                dis[V[i]]=dis[now]+W[i],pre[V[i]]=i;
                if(!vis[V[i]]) vis[V[i]]=true,que[tail++]=V[i];
            }
    }
    return dis[t]!=INF;
}
int main()
{
    in(n),in(m),in(k),s=1,t=n;
    for(int i=1;i<=m;i++)
    {
        in(Edge[i].u),in(Edge[i].v),in(Edge[i].f),in(Edge[i].w);
        edge_add(Edge[i].u,Edge[i].v,0,Edge[i].f);
    }
    ans=0;
    while(bfs()) ans+=flowing(s,INF);
    cout<<ans<<' ';ans=0;
    s=0,edge_add(s,1,0,k);
    for(int i=1;i<=m;i++)
        edge_add(Edge[i].u,Edge[i].v,Edge[i].w,INF);
    while(spfa())
    {
        int pos=INF,now=t;
        while(pre[now]!=-1) pos=min(F[pre[now]],pos),now=V[pre[now]^1];
        now=t;
        while(pre[now]!=-1) F[pre[now]]-=pos,F[pre[now]^1]+=pos,now=V[pre[now]^1];
        ans+=pos*dis[t];
    }
    cout<<ans;
    return 0;
}
