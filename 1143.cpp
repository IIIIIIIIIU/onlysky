#include <bits/stdc++.h>
using namespace std;
const int maxn=1005;
const int maxm=20005;
const int INF=0x3f3f3f3f;
int n,m,head[maxn],E[maxm],V[maxm],F[maxm],cnt=1;
int deep[maxn],que[maxm],s,t,ans;
bool can[maxn][maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1,now;deep[s]=0,que[0]=s;
    while(h<tail)
    {
        now=que[h++];
        for(int i=head[now];i;i=E[i])
            if(deep[V[i]]==-1&&F[i])
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
            F[i]-=pos,F[i^1]+=pos,oldflow+=pos,flow-=pos;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
int main()
{
    in(n),in(m);int u,v;
    ans=n,s=0,t=n*2+1;
    while(m--)
    {
        in(u),in(v);
        can[u][v]=true;
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int v=1;v<=n;v++)
                can[i][v]|=can[i][k]&&can[k][v];
    for(int i=1;i<=n;i++)
    {
        for(int v=1;v<=n;v++)
            if(can[i][v]) edge_add(i,v+n,1);
        edge_add(s,i,1),edge_add(i+n,t,1);
    }
    while(bfs())
        ans-=flowing(s,INF);
    cout<<ans;
    return 0;
}
