#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int pi[14]={0,2,3,5,7,11,13,17,19,23,29,31,37};
ll ans,n,res;
void dfs(ll x,ll num,ll sum,ll cnt,ll p)
{
    if(res==cnt*(num+1)&&ans>sum) ans=sum;
    if(res<cnt*(num+1)) ans=sum,res=cnt*(num+1);
    if(num+1<=p&&sum*pi[x]<=n) dfs(x,num+1,sum*pi[x],cnt,p);
    for(int i=x+1;i<=12;i++)
        if(sum*pi[i]<=n) dfs(i,1,sum*pi[i],cnt*(num+1),num);
}
int main()
{
    scanf("%lld",&n);
    dfs(1,0,1,1,100);
    cout<<ans;
    return 0;
}
