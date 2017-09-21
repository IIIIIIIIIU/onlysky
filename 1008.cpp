#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod=100003;
ll n,m;
ll poww(ll x,ll mi)
{
    ll res=1;
    while(mi)
    {
        if(mi&1) res=(res*x)%mod;
        mi>>=1,x=(x*x)%mod;
    }
    return res;
}
int main()
{
    cin>>m>>n;
    ll n1=n,m1=m;
    cout<<(poww(m,n)-(poww(m-1,n-1)*m)%mod+mod)%mod;
    return 0;
}
