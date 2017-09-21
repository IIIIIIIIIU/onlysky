#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
  
using namespace std;
  
#define INF 0x7ffffff
  
struct NodeType {
    int x,y,s;
};
struct NodeType pre[15][15][10005];
  
const int dx[5]={0,-1,0,1,0};
const int dy[5]={0,0,1,0,-1};
  
int n,m,map[15][15],num,bi[15],all,dp[15][15][10005],ans;
  
bool if_[15][15],cho[15][15];
  
queue<NodeType>que;
  
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
  
void read()
{
//  freopen("wc2008_trip.in","r",stdin);
//  freopen("wc2008_trip.out","w",stdout);
    in(n),in(m),bi[0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            in(map[i][j]);
            if(!map[i][j]) num++;
        }
    }
    for(int i=1;i<=num;i++) bi[i]=bi[i-1]<<1;
    all=bi[num]-1;
}
  
void spfa(int f)
{
    while(!que.empty())
    {
        NodeType now=que.front();que.pop(),if_[now.x][now.y]=false;
        for(int i=1;i<=4;i++)
        {
            int x=now.x+dx[i],y=now.y+dy[i];
            if(x>0&&x<=n&&y>0&&y<=m)
            {
                if(dp[x][y][f]>dp[now.x][now.y][f]+map[x][y])
                {
                    dp[x][y][f]=dp[now.x][now.y][f]+map[x][y];
                    pre[x][y][f]=(NodeType){now.x,now.y,now.s};
                    if(!if_[x][y]) que.push((NodeType){x,y,f}),if_[x][y]=true;
                }
            }
        }
    }
}
 
void dfs(int x,int y,int s)
{
    if(x>INF||pre[x][y][s].s==0) return ;
    cho[x][y]=true;
    dfs(pre[x][y][s].x,pre[x][y][s].y,pre[x][y][s].s);
    if(x==pre[x][y][s].x&&y==pre[x][y][s].y) dfs(x,y,s-pre[x][y][s].s);
}
 
void solve()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int v=1;v<=all;v++) dp[i][j][v]=INF;
        }
    }
    int F=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!map[i][j]) dp[i][j][bi[F++]]=0;
        }
    }
    for(int S=1;S<=all;S++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                for(int s=S&(S-1);s;s=S&(s-1))
                {
                    int tmp=dp[i][j][s]+dp[i][j][S-s]-map[i][j];
                    if(tmp<dp[i][j][S])
                    {
                        dp[i][j][S]=tmp;
                        pre[i][j][S]=(NodeType){i,j,s};
                    }
                }
                if(dp[i][j][S]<INF) que.push((NodeType){i,j,S}),if_[i][j]=true;
            }
        }
        spfa(S);
    }
    int ex,ey;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!map[i][j])
            {
                ex=i,ey=j,ans=dp[i][j][all];
                break;
            }
        }
    }
    dfs(ex,ey,all);
}
 
void print()
{
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(!map[i][j]) putchar('x');
            else if(cho[i][j]) putchar('o');
            else putchar('_');
        }
        putchar('\n');
    }
}
 
int main()
{
    read();
    solve();
    print();
    return 0;
}
