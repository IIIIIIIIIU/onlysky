#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
const int dx[5]={0,-1,0,1,0};
const int dy[5]={0,0,1,0,-1};
 
int n,m,sx,sy,ex,ey,dis[1005][1005];
int quex[1000005],quey[1000005];
 
char map[1005][1005];
 
bool if_[1005][1005];
 
int main()
{
    scanf("%d%d",&n,&m);
    while(n!=0&&m!=0)
    {
        for(int i=1;i<=n;i++) scanf("%s",map[i]+1);
        scanf("%d%d%d%d",&sx,&sy,&ex,&ey);sx++,sy++,ex++,ey++;
        int h=0,tail=1;memset(dis,0x7f,sizeof(dis)),memset(if_,false,sizeof(if_));
        quex[0]=sx,quey[0]=sy,dis[sx][sy]=0,if_[sx][sy]=true;
        while(h<tail)
        {
            int x=quex[h],y=quey[h++],xx,yy,w;
            if_[x][y]=false;
            for(int v=1;v<=4;v++)
            {
                xx=x+dx[v],yy=y+dy[v];
                if(xx>0&&xx<=n&&yy>0&&yy<=m)
                {
                    w=(map[xx][yy]==map[x][y]?0:1);
                    if(dis[x][y]+w<dis[xx][yy])
                    {
                        dis[xx][yy]=dis[x][y]+w;
                        if(!if_[xx][yy]) if_[xx][yy]=true,quex[tail]=xx,quey[tail++]=yy;
                    }
                }
            }
        }
        printf("%d\n",dis[ex][ey]);
        scanf("%d%d",&n,&m);
    }
    return 0;
}
