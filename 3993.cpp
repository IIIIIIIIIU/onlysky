#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
#define maxn 101
#define INF 9999999.99
#define EFlit 10000.0
 
using namespace std;
 
struct EdgeType {
    int v,e;
     
    double f;
};
struct EdgeType edge[maxn*maxn<<1];
 
int if_z,n,m,head[maxn<<2],s,t=(maxn<<2)-1;
int ai[maxn],bi[maxn],tota,totb,map[maxn][maxn];
int deep[maxn<<2],cnt;
 
double dai[maxn],dbi[maxn];
 
char Cget;
 
inline void in(int &now)
{
    now=0,if_z=1,Cget=getchar();
    while(Cget>'9'||Cget<'0')
    {
        if(Cget=='-') if_z=-1;
        Cget=getchar();
    }
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
    return ;
}
 
bool bfs()
{
    queue<int>que;
    memset(deep,-1,sizeof(deep));
    que.push(s);deep[s]=0;
    while(!que.empty())
    {
        int pos=que.front();que.pop();
        for(int i=head[pos];i;i=edge[i].e)
        {
            if(deep[edge[i].v]<0&&edge[i].f>0)
            {
                deep[edge[i].v]=deep[pos]+1;
                if(edge[i].v==t) return true;
                que.push(edge[i].v);
            }
        }
    }
    return false;
}
 
double flowing(int now,double flow)
{
    if(now==t||flow==0) return flow;
    double oldflow=0;
    for(int i=head[now];i;i=edge[i].e)
    {
        if(deep[edge[i].v]==deep[now]+1&&edge[i].f>0)
        {
            double pos=flowing(edge[i].v,min(flow,edge[i].f));
            if(pos>0)
            {
                flow-=pos;
                oldflow+=pos;
                edge[i].f-=pos;
                edge[i^1].f+=pos;
                if(flow==0) return oldflow;
            }
        }
    }
    if(oldflow==0) deep[now]=-1;
    return oldflow;
}
 
inline void edge_add(int u,int v,double f)
{
    edge[++cnt].v=v,edge[cnt].f=f,edge[cnt].e=head[u],head[u]=cnt;
    edge[++cnt].v=u,edge[cnt].f=0,edge[cnt].e=head[v],head[v]=cnt;
}
 
bool check(double ans_)
{
    cnt=1;
    memset(head,0,sizeof(head));
    for(int i=1;i<=m;i++) edge_add(s,i,dbi[i]*ans_);
    for(int i=1;i<=n;i++) edge_add(i+m,t,dai[i]);
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(map[i][j]) edge_add(i,j+m,INF);
        }
    }
    double pos=0;
    while(bfs()) pos+=flowing(s,INF);
    if(pos>=(double)tota-0.001) return true;
    else return false;
}
 
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++)
    {
        in(ai[i]);
        tota+=ai[i];
        dai[i]=ai[i];
    }
    for(int i=1;i<=m;i++)
    {
        in(bi[i]);
        totb+=bi[i];
        dbi[i]=bi[i];
    }
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++) in(map[i][j]);
    }
    double l=(double)tota/(double)totb,r=EFlit,mid,ans;
//  double l=0,r=EFlit,mid,ans;
    while(l<r)
    {
        mid=(l+r)/2.0;
        if(check(mid)) ans=mid,r=mid-0.0001;
        else l=mid+0.0001;
    }
    printf("%lf\n",ans);
    return 0;
}
