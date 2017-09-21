#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll gcd(ll x,ll y)
{
    return y?gcd(y,x%y):x;
}
ll n,n2,ans;
void makeit(ll x)
{
    ll y=n2/x,v;
    for(ll i=1;i*i<=y;++i)
    {
        v=(int)(sqrt(y-i*i*1.0)+0.5);
        if(i>=v) break;
        ans+=(v*v==y-i*i & gcd(i,v)==1);
    }
}
int main()
{
    cin>>n;
    n2=n<<1;
    ll N=(ll)sqrt(n*2.0);
    for(ll i=1;i<=N;++i)
        if(!(n2%i))
        {
            makeit(i);
            if(i*i!=n) makeit(n2/i);
        }
    cout<<ans*4+4;
    return 0;
}
