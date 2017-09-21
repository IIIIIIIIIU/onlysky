#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 64005
#define INF 0x3f3f3f3f
const int dx[5]={0,-1,0,1,0};
const int dy[5]={0,0,1,0,-1};
int deep[maxn],head[maxn],E[maxn<<4],V[maxn<<4],F[maxn<<4],ans;
int n,m,r,d,ai[45][45][45],id[45][45][45],s,t,cnt,que[maxn];
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
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    deep[s]=0,que[0]=s;int h=0,tail=1,now;
    while(h<tail)
    {
        now=que[h++];
        for(int i=head[now];i;i=E[i])
            if(F[i]&&deep[V[i]]<0)
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
    {
        if(deep[V[i]]!=deep[now]+1||!F[i]) continue;
        pos=flowing(V[i],min(flow,F[i]));
        F[i]-=pos,F[i^1]+=pos,flow-=pos,oldflow+=pos;
        if(!flow) return oldflow;
    }
    if(!oldflow) deep[now]=-1;
    return oldflow;
}
int main()
{
    in(n),in(m),in(r),in(d);
    for(int i=1;i<=r;i++)
        for(int v=1;v<=n;v++)
            for(int e=1;e<=m;e++) in(ai[i][v][e]),id[i][v][e]=++cnt;
    s=0,t=cnt+1,cnt=1;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            edge_add(s,id[1][i][v],ai[1][i][v]),edge_add(id[r][i][v],t,INF);
    for(int z=2;z<=r;z++)
    {
        for(int i=1;i<=n;i++)
            for(int v=1;v<=m;v++) edge_add(id[z-1][i][v],id[z][i][v],ai[z][i][v]);
        if(z>d)
        {
            for(int i=1;i<=n;i++)
                for(int v=1;v<=m;v++)
                    for(int e=1;e<=4;e++)
                        if(i+dx[e]>0&&i+dx[e]<=n&&v+dy[e]>0&&v+dy[e]<=m)
                            edge_add(id[z][i][v],id[z-d][i+dx[e]][v+dy[e]],INF);
        }
    }
    while(bfs()) ans+=flowing(s,INF);
    printf("%d\n",ans);
    return 0;
}
