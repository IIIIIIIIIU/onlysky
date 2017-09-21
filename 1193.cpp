#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int dx[9]={0,-2,-1,1,2,2,1,-1,-2};
const int dy[9]={0,1,2,2,1,-1,-2,-2,-1};
int sx,sy,ex,ey,disx,disy,ans,ai[1005][1005];
queue<int>quex,quey;
int main()
{
    scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
    disx=abs(ex-sx),disy=abs(ey-sy);
    if(disx<disy) swap(disx,disy);
    while(disx>50)
    {
        if(disx-4>disy*2) disx-=4,ans+=2;
        else disx-=2,--disy,++ans;
        if(disx<disy) swap(disx,disy);
    }
    sx=505,sy=505;
    ex=sx+disx,ey=sy+disy;
    ai[sx][sy]=1,quex.push(sx),quey.push(sy);
    int x,y,px,py;
    while(!quex.empty())
    {
        x=quex.front(),y=quey.front(),quex.pop(),quey.pop();
        for(int i=1;i<=8;i++)
        {
            px=x+dx[i],py=y+dy[i];
            if(!ai[px][py])
            {
                if(px==ex&&py==ey)
                {
                    printf("%d\n",ans+ai[x][y]);
                    return 0;
                }
                ai[px][py]=ai[x][y]+1;
                quex.push(px),quey.push(py);
            }
        }
    }
    return 0;
}
