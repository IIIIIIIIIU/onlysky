#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
ll dp[13][13][2][2][2][13][2],pos[13],N,len,L,R;
bool vis[13][13][2][2][2][13][2];
ll get(int now,int num,bool lit,bool four,bool eight,int line,bool did)
{
    if(!lit&&vis[now][num][lit][four][eight][line][did])
        return dp[now][num][lit][four][eight][line][did];
    if(four&eight) return 0;
    if(!now)
    {
        if(did) return 1;
        return 0;
    }
    vis[now][num][lit][four][eight][line][did]=true;
    ll &kol=dp[now][num][lit][four][eight][line][did],res=0LL;
    ll lim=(lit?pos[now]:9),st;
    if(now==len) st=1;else st=0;
    for(int i=st;i<=lim;i++)
    {
        bool lit_=lit&(i==lim),eight_=eight|(i==8),four_=four|(i==4);
        int line_=(i==num)?line+1:1;bool did_=did|(line_>=3?1:0);
        res+=get(now-1,i,lit_,four_,eight_,line_,did_);
    }
    kol=res;return res;
}
ll calc(ll x)
{
    memset(vis,0,sizeof(vis));
    len=0;
    while(x)
    {
        pos[++len]=x%10;
        x/=10;
    }
    return get(len,-1,1,0,0,0,0);
}
int main()
{
    cin>>L>>R;
    ll ans;
    if(L==10000000000LL) ans=calc(R);
    else ans=calc(R)-calc(L-1);
    cout<<ans;
    return 0;
}
