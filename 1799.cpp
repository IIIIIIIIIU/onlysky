#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
int num[20],len;
ll dp[21][163][163][2],mod,ans;
bool vis[21][163][163][2];
ll dfs(int i,int v,int sum,bool lit)
{
    if(i==1) return v==0&&sum==mod;
    if(vis[i][v][sum][lit]) return dp[i][v][sum][lit];
    vis[i][v][sum][lit]=true;
    ll &now=dp[i][v][sum][lit];
    if(lit)
    {
        now+=dfs(i-1,(v*10+num[i-1])%mod,sum+num[i-1],true);
        for(int e=0;e<num[i-1];e++) now+=dfs(i-1,(v*10+e)%mod,sum+e,false);
    }
    else
        for(int e=0;e<=9;e++) now+=dfs(i-1,(v*10+e)%mod,sum+e,false);
    return now;
}
ll calc(ll x)
{
    ll len=0,res=0,litnow=0;
    while(x) num[++len]=x%10,x/=10,litnow+=9;
    for(int i=1;i<=litnow;i++)
    {
        mod=i;
        memset(dp,0,sizeof(dp));
        memset(vis,0,sizeof(vis));
        res+=dfs(len+1,0,0,true);
    }
    return res;
}
int main()
{
    long long a,b;
    cin>>a>>b;
    ans+=calc(b);
    ans-=calc(a-1);
    cout<<ans;
    return 0;
}
