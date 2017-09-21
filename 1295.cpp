#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int INF=0x3f3f3f3f;
const int dx[5]={0,-1,0,1,0};
const int dy[5]={0,0,1,0,-1};
int n,m,k,cnt,head[10005],E[40005],V[40005],W[40005];
int que[40005],backx[10005],backy[10005],dis[10005],id[40][40];
char ch[105][105];
bool vis[10005];
real ans;
inline void edge_add(int u,int v,int w)
{
    E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
}
inline real dist(int ida,int idb)
{
    real x=backx[ida]-backx[idb];
    real y=backy[ida]-backy[idb];
    return sqrt(x*x+y*y);
}
void spfa(int s)
{
    for(int i=1;i<=n*m;i++) dis[i]=INF;
    int h=0,tail=1,now;que[0]=s,vis[s]=true,dis[s]=ch[backx[s]][backy[s]]-'0';
    while(h<tail)
    {
        now=que[h++],vis[now]=false;
        for(int i=head[now];i;i=E[i])
            if(dis[now]+W[i]<dis[V[i]])
            {
                dis[V[i]]=dis[now]+W[i];
                if(!vis[V[i]]) vis[V[i]]=true,que[tail++]=V[i];
            }
    }
    for(int i=1;i<=n*m;i++)
        if(dis[i]<=k)
            ans=max(ans,dist(s,i));
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch[i]+1);
        for(int v=1;v<=m;v++)
        {
            id[i][v]=++cnt;
            backx[cnt]=i;
            backy[cnt]=v;
        }
    }
    int x,y;
    cnt=0;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            for(int e=1;e<=4;e++)
            {
                x=i+dx[e],y=v+dy[e];
                if(x>0&&x<=n&&y>0&&y<=m)
                    edge_add(id[i][v],id[x][y],ch[x][y]-'0');
            }
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++) spfa(id[i][v]);
    printf("%.6lf\n",ans);
    return 0;
}
