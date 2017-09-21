#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int num[20],len,pos,tot;
ll dp[20][10][20][2],ans[20];
bool vis[20][10][20][2];
ll dfs(int now,int nu,int cnt,int on)
{
//  printf("%d\n",++tot);
    if(now==1) return cnt;
    if(vis[now][nu][cnt][on]) return dp[now][nu][cnt][on];
    vis[now][nu][cnt][on]=true;
    ll &tmp=dp[now][nu][cnt][on];
    tmp=0;
    if(on)
    {
        tmp+=dfs(now-1,num[now-1],cnt+(num[now-1]==pos),true);
        for(int i=0;i<num[now-1];i++)
            tmp+=dfs(now-1,i,cnt+(i==pos),false);
    }
    else
    {
        for(int i=0;i<=9;i++) tmp+=dfs(now-1,i,cnt+(i==pos),false);
    }
    return tmp;
}
void calc(ll x,int di)
{
    if(x<10)
    {
        for(int i=0;i<=x;i++) ans[i]+=di;
        return;
    }
    len=0;
    while(x) num[++len]=x%10,x/=10;
    for(pos=0;pos<=9;pos++)
    {
        memset(vis,0,sizeof(vis));
        ans[pos]+=di*dfs(len,num[len],num[len]==pos,true);
        for(int i=1;i<num[len];i++)
            ans[pos]+=di*dfs(len,i,i==pos,false);
        for(int i=len-1;i>0;i--)
            for(int v=1;v<=9;v++)
                ans[pos]+=di*dfs(i,v,v==pos,false);
    }
}
int main()
{
    ll a,b;
    cin>>a>>b;
    if(b<a) swap(a,b);
    calc(b,1);
    calc(a-1,-1);
    for(int i=0;i<9;i++) cout<<ans[i]<<' ';
    cout<<ans[9]<<endl;
    return 0;
}
