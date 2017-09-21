#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 100005
#define ll long long
ll n,m,ai[maxn];
inline void in(ll &now)
{
    ll if_z=1;now=0;
    char Cget=getchar();
    while(Cget>'9'||Cget<'0')
    {
        if(Cget=='-') if_z=-1;
        Cget=getchar();
    }
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}
ll check(ll x)
{
    ll now=0,res=0;
    for(ll i=1;i<=n;i++)
    {
        now+=ai[i];
        now=max(0LL,now);
        if(now>=x) now=0,res++;
    }
    return res;
}
int main()
{
    in(n),in(m);ll a,b;
    for(ll i=1;i<=n;i++) in(ai[i]);
    ll l=1,r=1e17,mid,ans=-1;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(check(mid)<=m) ans=mid,r=mid-1;
        else l=mid+1;
    }
    a=ans;
    l=1,r=1e17,ans=-1;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(check(mid)>=m) ans=mid,l=mid+1;
        else r=mid-1;
    }
    b=ans;
    if(a>0&&b>0&&check(a)==m&&check(b)==m) cout<<a<<' '<<b;
    else cout<<-1;
    return 0;
}
