#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define ll long long
#define mod 1000000007
 
ll n,m[6],sum,ai[6],dp[16][16][16][16][16][6];
 
bool if_[16][16][16][16][16][6];
 
ll dfs(ll a,ll b,ll c,ll d,ll e,ll f)
{
    if(a<0||b<0||c<0||d<0||e<0) return 0;
    if(a+b+c+d+e>sum) return 0;
    if(a>m[5]||b>m[4]||c>m[3]||d>m[2]||e>m[1]) return 0;
    if(if_[a][b][c][d][e][f]) return dp[a][b][c][d][e][f];
    if_[a][b][c][d][e][f]=true;
    ll now=0;
    if(f==1)
    {
        now+=dfs(a,b,c,d,e+1,0)*(e+1);
        now+=dfs(a,b,c,d,e+1,1)*(e+1);
        now+=dfs(a,b,c,d,e+1,2)*e;
        now+=dfs(a,b,c,d,e+1,3)*(e+1);
        now+=dfs(a,b,c,d,e+1,4)*(e+1);
        now+=dfs(a,b,c,d,e+1,5)*(e+1);
    }
    else if(f==2)
    {
        now+=dfs(a,b,c,d+1,e-1,0)*(d+1);
        now+=dfs(a,b,c,d+1,e-1,1)*(d+1);
        now+=dfs(a,b,c,d+1,e-1,2)*(d+1);
        now+=dfs(a,b,c,d+1,e-1,3)*d;
        now+=dfs(a,b,c,d+1,e-1,4)*(d+1);
        now+=dfs(a,b,c,d+1,e-1,5)*(d+1);
    }
    else if(f==3)
    {
        now+=dfs(a,b,c+1,d-1,e,0)*(c+1);
        now+=dfs(a,b,c+1,d-1,e,1)*(c+1);
        now+=dfs(a,b,c+1,d-1,e,2)*(c+1);
        now+=dfs(a,b,c+1,d-1,e,3)*(c+1);
        now+=dfs(a,b,c+1,d-1,e,4)*c;
        now+=dfs(a,b,c+1,d-1,e,5)*(c+1);
    }
    else if(f==4)
    {
        now+=dfs(a,b+1,c-1,d,e,0)*(b+1);
        now+=dfs(a,b+1,c-1,d,e,1)*(b+1);
        now+=dfs(a,b+1,c-1,d,e,2)*(b+1);
        now+=dfs(a,b+1,c-1,d,e,3)*(b+1);
        now+=dfs(a,b+1,c-1,d,e,4)*(b+1);
        now+=dfs(a,b+1,c-1,d,e,5)*b;
    }
    else if(f==5)
    {
        now+=dfs(a+1,b-1,c,d,e,0)*(a+1);
        now+=dfs(a+1,b-1,c,d,e,1)*(a+1);
        now+=dfs(a+1,b-1,c,d,e,2)*(a+1);
        now+=dfs(a+1,b-1,c,d,e,3)*(a+1);
        now+=dfs(a+1,b-1,c,d,e,4)*(a+1);
        now+=dfs(a+1,b-1,c,d,e,5)*(a+1);
    }
    now%=mod;
    dp[a][b][c][d][e][f]=now;
//  printf("%d %d %d %d %d %d %lld\n",a,b,c,d,e,f,now);
    return now;
}
 
int main()
{
//  freopen("color.in","r",stdin);
//  freopen("color.out","w",stdout);
    cin>>n;ll pos;
    for(ll i=1;i<=n;i++)
    {
        cin>>pos;
        ai[pos]++;
    }
    for(ll i=1;i<=5;i++)
    {
        for(ll j=i;j<=5;j++) m[i]+=ai[j];
        sum+=ai[i];
    }
    dp[ai[5]][ai[4]][ai[3]][ai[2]][ai[1]][0]=1;
    if_[ai[5]][ai[4]][ai[3]][ai[2]][ai[1]][0]=true;
    cout<<dfs(0,0,0,0,0,1);
    return 0;
}
