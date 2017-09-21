#include <bits/stdc++.h>
using namespace std;
#define maxn 2005
#define ll long long
#define mod 100000007
struct poll
{
    ll x,y;
    poll(ll a=0,ll b=0):x(a),y(b){}
    bool operator<(const poll &b) const
    {
        return x<b.x||(x==b.x&&y<b.y);
    }
    bool operator==(const poll &b) const
    {
        return x==b.x&&y==b.y;
    }
};
struct poll poi[maxn];
ll n,m,k;
set<poll>mp;
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
ll once0(ll l,ll r,ll h)
{
    ll z=min(l+r,h);
    if(z==0) return 0;
    ll ans=z*(z+3)/2;
    if(z>l) ans-=(z-l)*(z-l+1)/2;
    if(z>r) ans-=(z-r)*(z-r+1)/2;
    return ans;
}
ll once(ll x,ll y)
{
    ll t=x,b=n-x,l=y,r=m-y;
    return (once0(t,b,l)+once0(t,b,r)+once0(l,r,t)+once0(l,r,b)-min(l,t)-min(t,r)-min(r,b)-min(b,l))%mod;
}
bool inmap(ll x,ll y)
{
    return 0<=x&&x<=n&&0<=y&&y<=m;
}
void count(poll a,poll b,ll &cnt2,ll &cnt3,ll &cnt4)
{
    if(inmap(a.x,a.y)&&inmap(b.x,b.y))
    {
        ll t=mp.count(a)+mp.count(b);
        ++cnt2;
        if(t>0) ++cnt3;
        if(t>1) ++cnt4,++cnt3;
    }
}
int main()
{
    in(n),in(m),in(k);ll ans=0;
    for(ll i=1;i<=min(n,m);++i) (ans+=(n-i+1)*(m-i+1)%mod*i)%=mod;
    for(ll i=0;i<k;++i)
    {
        in(poi[i].x),in(poi[i].y);
        mp.insert(poi[i]);(ans-=once(poi[i].x,poi[i].y))%=mod;
    }
    ll cnt2=0,cnt3=0,cnt4=0;
    for(ll i=0;i<k;++i)
    {
        poll p=poi[i];
        for(ll v=i+1;v<k;++v)
        {
            poll q=poi[v];
            ll dx=p.x-q.x,dy=p.y-q.y;
            count(poll(p.x+dy,p.y-dx),poll(q.x+dy,q.y-dx),cnt2,cnt3,cnt4);
            count(poll(p.x-dy,p.y+dx),poll(q.x-dy,q.y+dx),cnt2,cnt3,cnt4);
            if(abs(dx)+abs(dy) &1) continue;
            ll x=dx-dy >>1,y=dx+dy>>1;
            count(poll(p.x-x,p.y-y),poll(q.x+x,q.y+y),cnt2,cnt3,cnt4);
        }
    }
    ans=(ans+cnt2-cnt3/3+cnt4/6)%mod;
    if(ans<0) ans+=mod;
    printf("%lld\n",ans);
    return 0;
}
