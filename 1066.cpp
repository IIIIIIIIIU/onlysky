#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
  
using namespace std;
  
#define maxn 905
#define INF 0x7ffffff
  
struct NodeType {
    int x,y,hi;
};
struct NodeType ai[maxn];
  
int n,m,cnt=1,tot,map[maxn][maxn],s,t,que[maxn*maxn*4],tott,d;
int head[maxn],deep[maxn],F[maxn*maxn*2],E[maxn*maxn*2],V[maxn*maxn*2];
 
inline void edge_add(int u,int v,int f)
{
//  printf("%d %d %d\n",u,v,f);
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
  
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1;que[h]=s,deep[s]=0;
    while(h<tail)
    {
        int now=que[h++];
        for(int i=head[now];i;i=E[i])
        {
            if(deep[V[i]]<0&&F[i]>0)
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
        if(deep[V[i]]==deep[now]+1&&F[i]>0)
        {
            int pos=flowing(V[i],min(flow,F[i]));
            F[i]-=pos,F[i^1]+=pos;
            flow-=pos,oldflow+=pos;
            if(flow==0) return oldflow;
        }
    }
    if(oldflow==0) deep[now]=-1;
    return oldflow;
}
  
int main()
{
    scanf("%d%d%d",&n,&m,&d);
    char ch[101];
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for(int j=1;j<=m;j++)
        {
            if(ch[j]!='0') ai[++tot].x=i,ai[tot].y=j,ai[tot].hi=ch[j]-'0',map[i][j]=tot;
        }
    }
    t=tot*2+1;
    for(int i=1;i<=tot;i++)
    {
        edge_add(i,i+tot,ai[i].hi);
        for(int j=1;j<=tot;j++)
        {
            if(j==i) continue;
            if(abs(ai[i].x-ai[j].x)+abs(ai[i].y-ai[j].y)<=d) edge_add(i+tot,j,INF);
        }
        if(ai[i].x<=d||ai[i].y<=d||n-ai[i].x+1<=d||m-ai[i].y+1<=d) edge_add(i+tot,t,INF);
    }
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ch+1);
        for(int j=1;j<=m;j++) if(ch[j]=='L') edge_add(s,map[i][j],1),tott++;
    }
    int ans=0;
    while(bfs()) ans+=flowing(s,INF);
    cout<<tott-ans;
    return 0;
}
