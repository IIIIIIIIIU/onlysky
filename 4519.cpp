#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 2005
#define maxm 40005
#define INF 0x3f3f3f3f
int n,m,head[maxn],V[maxm],F[maxm],E[maxm],cnt=1;
int s,t,deep[maxn],que[maxn],ai[maxn],bi[maxn];
bool has[maxn];
set<int>Set;
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
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=f,head[v]=cnt;
}
bool bfs()
{
    for(int i=1;i<=n;i++) deep[i]=-1;
    deep[s]=0,que[0]=s;int h=0,tail=1,now;
    while(h<tail)
    {
        now=que[h++];
        for(int i=head[now];i;i=E[i])
            if(deep[V[i]]<0&&F[i])
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que[tail++]=V[i];
            }
    }
    return false;
}
int flowing(int now,int flow)
{
    if(now==t||flow<=0) return flow;
    int oldflow=0,pos;
    for(int i=head[now];i;i=E[i])
        if(deep[V[i]]==deep[now]+1&&F[i])
        {
            pos=flowing(V[i],min(flow,F[i]));
            F[i]-=pos,F[i^1]+=pos,flow-=pos,oldflow+=pos;
            if(!flow) return oldflow;
        }
    if(!oldflow) deep[now]=-1;
    return oldflow;
}
void dfs(int now)
{
    has[now]=true;
    for(int i=head[now];i;i=E[i]) if(F[i]&&!has[V[i]]) dfs(V[i]);
}
void get(int l,int r)
{
    if(l>=r) return;
    for(int i=2;i<=cnt;i+=2) F[i]=F[i^1]=(F[i]+F[i^1])>>1;
    int pos=0;s=ai[l],t=ai[r];
    while(bfs()) pos+=flowing(s,INF);
    Set.insert(pos);
    for(int i=1;i<=n;i++) has[i]=false;
    dfs(s);int L=l,R=r;
    for(int i=l;i<=r;i++)
        if(has[ai[i]]) bi[L++]=ai[i];
        else bi[R--]=ai[i];
    for(int i=l;i<=r;i++) ai[i]=bi[i];
    get(l,L-1),get(R+1,r);
}
int main()
{
    in(n),in(m),cnt=1;int u,v,w;
    for(int i=1;i<=m;i++)
    {
        in(u),in(v),in(w);
        edge_add(u,v,w);
    }
    for(int i=1;i<=n;i++) ai[i]=i;
    get(1,n);cout<<Set.size();
    return 0;
}
