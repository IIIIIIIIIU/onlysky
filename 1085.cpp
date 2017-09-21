#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int ans,lit;
const int dx[9]={0,-2,-2,-1,-1,1,1,2,2};
const int dy[9]={0,1,-1,-2,2,-2,2,1,-1};
char T[6][6],ci[6][6];
inline int get()
{
    int res=0;
    for(int i=1;i<=5;i++)
        for(int v=1;v<=5;v++)
            res+=(ci[i][v]!=T[i][v]);
    return res;
}
bool dfs(short x,short y,short now,short pre)
{
    short tmp=get();
    if(!tmp) return true;
    if(tmp+now-1>lit) return false;
    short tmpx,tmpy;
    for(short i=1;i<=8;i++)
    {
        if(i+pre==9) continue;
        tmpx=x+dx[i],tmpy=y+dy[i];
        if(tmpx>0&&tmpx<6&&tmpy>0&&tmpy<6)
        {
            swap(ci[x][y],ci[tmpx][tmpy]);
            if(dfs(tmpx,tmpy,now+1,i))
            {
                swap(ci[x][y],ci[tmpx][tmpy]);
                return true;
            }
            swap(ci[x][y],ci[tmpx][tmpy]);
        }
    }
    return false;
}
int main()
{
    int t;scanf("%d",&t);
    for(int i=1;i<=5;i++)
        for(int v=1;v<=5;v++) T[i][v]='1';
    T[2][1]=T[3][1]=T[3][2]='0',T[3][3]='*';
    for(int i=1;i<=4;i++) T[4][i]='0';
    for(int i=1;i<=5;i++) T[5][i]='0';
    while(t--)
    {
        for(int i=1;i<=5;i++)
            scanf("%s",ci[i]+1);
        int sx,sy;
        for(int i=1;i<=5;i++)
            for(int v=1;v<=5;v++)
                if(ci[i][v]=='*')
                    sx=i,sy=v;
        int l=0,r=15,mid,ans=-1;
        while(l<=r)
        {
            mid=l+r>>1,lit=mid;
            if(dfs(sx,sy,0,233)) ans=mid,r=mid-1;
            else l=mid+1;
        }
        printf("%d\n",ans);
    }
    return 0;
}
