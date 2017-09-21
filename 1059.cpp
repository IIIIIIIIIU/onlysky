#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
const int INF=10000009;
int T,n,deep[maxn],s,t,head[maxn],E[maxn],V[maxn],F[maxn];
int ai[233][233],que[maxn],cnt;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1,now;deep[s]=0,que[0]=s;
    while(h<tail)
    {
        now=que[h++];
        for(int i=head[now];i;i=E[i])
        {
            if(F[i]&&deep[V[i]]<0)
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
    int oldflow=0,pos;
    for(int i=head[now];i;i=E[i])
    {
        if(!F[i]||deep[V[i]]!=deep[now]+1) continue;
        pos=flowing(V[i],min(flow,F[i]));
        F[i]-=pos,F[i^1]+=pos,flow-=pos,oldflow+=pos;
        if(!flow) return oldflow;
    }
    if(flow) deep[now]=-1;
    return oldflow;
}
int main()
{
    in(T);
    while(T--)
    {
        in(n),s=0,t=n*2+1,cnt=1;
        for(int i=s;i<=t;i++) head[i]=0;
        for(int i=1;i<=n;i++)
        {
            edge_add(s,i,1);
            edge_add(i+n,t,1);
            for(int v=1;v<=n;v++)
            {
                in(ai[i][v]);
                if(ai[i][v]==1) edge_add(i,v+n,1);
            }
        }
        int now=0;
        while(bfs()) now+=flowing(s,INF);
        if(now==n) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
