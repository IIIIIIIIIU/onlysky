#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=105;
const int INF=0x3f3f3f3f;
const int dx[5]={0,-1,0,1,0};
const int dy[5]={0,0,1,0,-1};
int n,m,s,t,id[maxn][maxn],backx[maxn*maxn],backy[maxn*maxn],tot,cnt=1,deep[maxn*maxn];
int head[maxn*maxn],E[maxn*maxn<<3],V[maxn*maxn<<3],F[maxn*maxn<<3],ans[maxn*maxn];
int que[maxn*maxn<<4],pre[maxn*maxn];
bool vis[maxn*maxn],bel[maxn*maxn],can[maxn*maxn];
char ch[maxn][maxn];
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
            if(tmp) pre[V[i]]=now;
            F[i]-=tmp,F[i^1]+=tmp,oldflow+=tmp,flow-=tmp;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
void dfs(int now,int t)
{
    vis[now]=true;
    if(now!=s&&now!=t)
    {
        if(bel[now]==t) can[now]=true;
    }
    for(int i=head[now];i;i=E[i])
    {
        if(F[i^1^t]&&!vis[V[i]]) dfs(V[i],t);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch[i]+1);
        for(int v=1;v<=m;v++)
        {
            if(ch[i][v]=='#') continue;
            id[i][v]=++tot;
            backx[tot]=i,backy[tot]=v;
        }
    }
    s=0,t=tot+1;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            if(ch[i][v]=='.')
                if((i+v)%2)
                {
                    bel[id[i][v]]=true;
                    edge_add(s,id[i][v],1);
                    for(int e=1;e<=4;e++)
                    {
                        int x=i+dx[e],y=v+dy[e];
                        if(x>0&&x<=n&&y>0&&y<=m&&ch[x][y]=='.')
                            edge_add(id[i][v],id[x][y],1);
                    }
                }
                else edge_add(id[i][v],t,1);
    while(bfs()) flowing(s,INF);
    int pos=tot;tot=0;
    dfs(s,1),dfs(t,0);
//  for(int i=head[s];i;i=E[i])
//      if(F[i]) dfs(i);
//  for(int i=head[t];i;i=E[i])
//      if(!F[i]) dfs(i);
    for(int i=1;i<t;i++) if(can[i]) ans[++tot]=i;
    if(!tot)
    {
        puts("LOSE");
        return 0;
    }
    puts("WIN");
    sort(ans+1,ans+tot+1);
    for(int i=1;i<=tot;i++) printf("%d %d\n",backx[ans[i]],backy[ans[i]]);
    return 0;
}
