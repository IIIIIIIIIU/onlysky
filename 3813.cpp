#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 100005
#define mod 19961993
#define ll long long
 
struct TreeNodeType {
    ll l,r,mid;
     
    ll dis1,dis2;
};
struct TreeNodeType tree[maxn<<2];
 
ll n,m,cntp;
 
ll bit[61],ans1,ans2,pi_[80],pi[80];
 
bool if_p[300];
 
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
 
ll poww(ll pos)
{
    pos%=mod;
    ll mi=mod-2,res=1;
    while(mi)
    {
        if(mi&1) res=(res*pos)%mod;
        mi>>=1,pos=(pos*pos)%mod;
    }
    return res;
}
 
void tree_build(ll now,ll l,ll r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        tree[now].dis1=bit[2],tree[now].dis2=3;
        return ;
    }
    tree[now].mid=l+r>>1;
    tree_build(now<<1,l,tree[now].mid);
    tree_build(now<<1|1,tree[now].mid+1,r);
    tree[now].dis1=tree[now<<1].dis1|tree[now<<1|1].dis1;
    tree[now].dis2=tree[now<<1].dis2*tree[now<<1|1].dis2%mod;
}
 
void tree_to(ll now,ll to,ll dis1,ll dis2)
{
    if(tree[now].l==tree[now].r)
    {
        tree[now].dis1=dis1,tree[now].dis2=dis2;
        return ;
    }
    if(to<=tree[now].mid) tree_to(now<<1,to,dis1,dis2);
    else tree_to(now<<1|1,to,dis1,dis2);
    tree[now].dis1=tree[now<<1].dis1|tree[now<<1|1].dis1;
    tree[now].dis2=tree[now<<1].dis2*tree[now<<1|1].dis2%mod;
}
 
void tree_query(ll now,ll l,ll r)
{
    if(tree[now].l==l&&tree[now].r==r)
    {
        ans1|=tree[now].dis1;
        ans2=(ans2*tree[now].dis2)%mod;
        return ;
    }
    if(l>tree[now].mid) tree_query(now<<1|1,l,r);
    else if(r<=tree[now].mid) tree_query(now<<1,l,r);
    else tree_query(now<<1,l,tree[now].mid),tree_query(now<<1|1,tree[now].mid+1,r);
}
 
int main()
{
    for(ll i=2;i<=281;i++)
    {
        if(!if_p[i]) pi[++cntp]=i;
        for(ll j=1;pi[j]*i<=281&&j<=cntp;j++)
        {
            if_p[i*pi[j]]=true;
            if(i%pi[j]==0) break;
        }
    }
    for(ll i=1;i<=60;i++)
    {
        pi_[i]=poww(pi[i]);
        if(i==1) bit[i]=1;
        else bit[i]=bit[i-1]<<1;
    }
    in(n);tree_build(1,1,maxn-5);
    ll op,ai,bi;
    for(;n--;)
    {
        in(op),in(ai),in(bi);
        if(op==1)
        {
            ll pos=0;
            for(ll i=1;i<=60;i++) if(bi&&(bi%pi[i]==0)) pos+=bit[i];
            bi%=mod;tree_to(1,ai,pos,bi);
        }
        else
        {
            ll ans;ans1=0,ans2=1,tree_query(1,ai,bi),ans=ans2;
            for(ll i=1;i<=60;i++) if(bit[i]&ans1) ans=(ans*((pi[i]-1)*pi_[i]%mod))%mod;
            printf("%lld\n",ans);
        }
    }
    return 0;
}
