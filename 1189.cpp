#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxm 3000001
#define INF 0x7fffffff
 
const int dx[5]={0,-1,0,1,0};
const int dy[5]={0,0,1,0,-1};
 
int n,m,d[100][500],tot,s,t,quex[maxm],quey[maxm],qued[maxm];
int head[500050],cnt,deep[500050],E[maxm],V[maxm],F[maxm],size,iap;
 
char map[25][25];
 
bool if_[25][25];
 
void bfs(int sx,int sy)
{
    int h=0,tail=1;
    memset(if_,false,sizeof(if_));
    quex[0]=sx,quey[0]=sy,qued[0]=0,if_[sx][sy]=true;
    while(h<tail)
    {
        int nowx=quex[h],nowy=quey[h],nowd=qued[h++];
        for(int i=1;i<=4;i++)
        {
            int x=nowx+dx[i],y=nowy+dy[i],dd=nowd+1;
            if(x>0&&x<=n&&y>0&&y<=m&&map[x][y]=='.'&&!if_[x][y])
            {
                if_[x][y]=true,d[tot][(x-1)*m+y]=dd;
                quex[tail]=x,quey[tail]=y,qued[tail++]=dd;
            }
        }
    }
}
 
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
 
bool BFS()
{
    memset(deep,-1,sizeof(deep));
    deep[s]=0;queue<int>que;que.push(s);
    while(!que.empty())
    {
        int now=que.front();que.pop();
        for(int i=head[now];i;i=E[i])
        {
            if(F[i]>0&&deep[V[i]]<0)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que.push(V[i]);
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
        if(F[i]>0&&deep[V[i]]==deep[now]+1)
        {
            int pos=flowing(V[i],min(flow,F[i]));
            flow-=pos,oldflow+=pos;
            F[i]-=pos,F[i^1]+=pos;
            if(flow==0) return oldflow;
        }
    }
    if(oldflow==0) deep[now]=-1;
    return oldflow;
}
 
bool check(int k)
{
    memset(head,0,sizeof(head));cnt=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(map[i][j]=='.') edge_add(s,(i-1)*m+j,1);
        }
    }
    for(int i=1;i<=tot;i++)
    {
        int kop=size*i+tot;
        edge_add(size+i,t,k);
        for(int j=1;j<=k;j++)
        {
            if(j!=1) edge_add(kop+j-1,kop+j,INF);
            edge_add(kop+j,size+i,1);
        }
        for(int j=1;j<=size;j++) if(d[i][j]<=k) edge_add(j,kop+d[i][j],1);
    }
    int pos=0;
    while(BFS())
    pos+=flowing(s,INF);
    if(pos>=iap) return true;
    else return false;
}
 
int main()
{
    scanf("%d%d",&n,&m);
    memset(d,127/3,sizeof(d));
    for(int i=1;i<=n;i++) scanf("%s",map[i]+1);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(map[i][j]=='D')
            {
                tot++;
                bfs(i,j);
            }
            if(map[i][j]=='.') iap++;
        }
    }
    t=500049,size=n*m;
    int l=0,r=size,ans=-1;
    while(l<=r)
    {
        int mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    if(ans==-1) cout<<"impossible";
    else cout<<ans;
    return 0;
}
