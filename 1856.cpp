#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=20100403;
ll n,m;
ll poww(ll a,ll mi)
{
    ll res=1;
    while(mi)
    {
        if(mi&1) (res*=a)%=mod;
        mi>>=1,(a*=a)%=mod;
    }
    return res;
}
ll C(ll a,ll b)
{
    ll up=1,down=1;
    for(int i=1;i<=a;i++) (up*=i)%=mod;
    for(int i=1;i<=b;i++) (down*=i)%=mod;
    for(int i=1;i<=(a-b);i++) (down*=i)%=mod;
    return (up*poww(down,mod-2))%mod;
}
int main()
{
    cin>>n>>m;
    cout<<(C(n+m,m)-C(n+m,m-1)+mod)%mod;
    return 0;
}
