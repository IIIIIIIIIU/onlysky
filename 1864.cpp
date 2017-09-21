#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=500005;
int len,sta[maxn],sta2[maxn],top,n,ch[maxn][2];
int dp[maxn][3],ans1,ans2;
char str[maxn];
void dfs(int fa,int w)
{
    int now=++n,tmp=str[n]-'0';
    if(fa) ch[fa][w]=now;
    if(tmp>=1) dfs(now,0);
    if(tmp>=2) dfs(now,1);
}
void dfs1(int now)
{
     
    if(ch[now][0]&&ch[now][1])
    {
        dfs1(ch[now][0]),dfs1(ch[now][1]);
        dp[now][0]=max(dp[ch[now][0]][1]+dp[ch[now][1]][2],dp[ch[now][0]][2]+dp[ch[now][1]][1])+1;
        dp[now][1]=max(dp[ch[now][0]][0]+dp[ch[now][1]][2],dp[ch[now][0]][2]+dp[ch[now][1]][0]);
        dp[now][2]=max(dp[ch[now][0]][0]+dp[ch[now][1]][1],dp[ch[now][0]][1]+dp[ch[now][1]][0]);
    }
    else if(ch[now][0])
    {
        dfs1(ch[now][0]);
         
        dp[now][0]=max(dp[ch[now][0]][1],dp[ch[now][0]][2])+1;
        dp[now][1]=max(dp[ch[now][0]][0],dp[ch[now][0]][2]);
        dp[now][2]=max(dp[ch[now][0]][0],dp[ch[now][0]][1]);
    }
    else
    {
        dp[now][0]=1;
        dp[now][1]=0;
        dp[now][2]=0;
    }
//  if(now==433)
//      {
//          int dowda=0;
//      }
//  if(dp[now][1]>100000||dp[now][0]>100000||dp[now][2]>100000)
//  {
//      cout<<now<<endl;
//  }
}
void dfs2(int now)
{
    if(ch[now][0]&&ch[now][1])
    {
        dfs2(ch[now][0]),dfs2(ch[now][1]);
        dp[now][0]=min(dp[ch[now][0]][1]+dp[ch[now][1]][2],dp[ch[now][0]][2]+dp[ch[now][1]][1])+1;
        dp[now][1]=min(dp[ch[now][0]][0]+dp[ch[now][1]][2],dp[ch[now][0]][2]+dp[ch[now][1]][0]);
        dp[now][2]=min(dp[ch[now][0]][0]+dp[ch[now][1]][1],dp[ch[now][0]][1]+dp[ch[now][1]][0]);
    }
    else if(ch[now][0])
    {
        dfs2(ch[now][0]);
        dp[now][0]=min(dp[ch[now][0]][1],dp[ch[now][0]][2])+1;
        dp[now][1]=min(dp[ch[now][0]][0],dp[ch[now][0]][2]);
        dp[now][2]=min(dp[ch[now][0]][0],dp[ch[now][0]][1]);
    }
    else
    {
        dp[now][0]=1;
        dp[now][1]=0;
        dp[now][2]=0;
    }
}
int main()
{
//  freopen("out1.txt","w",stdout);
    cin>>str+1;
    len=strlen(str+1);
    dfs(0,0);
    dfs1(1);
    ans1=max(dp[1][0],max(dp[1][1],dp[1][2]));
    dfs2(1);
    ans2=min(dp[1][0],min(dp[1][1],dp[1][2]));
    cout<<ans1<<' '<<ans2;
    return 0;
}
