#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 100005
#define ll long long
#define maxtree maxn<<2
ll n,m,L[maxtree],R[maxtree],val[maxtree],sum[maxtree],mid[maxtree];
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
void build(ll now,ll l,ll r)
{
    L[now]=l,R[now]=r;
    if(l==r)
    {
        in(val[now]),sum[now]=val[now];
        return;
    }
    mid[now]=l+r>>1;
    build(now<<1,l,mid[now]);
    build(now<<1|1,mid[now]+1,r);
    val[now]=max(val[now<<1],val[now<<1|1]);
    sum[now]=sum[now<<1]+sum[now<<1|1];
}
void updata(ll now,ll l,ll r)
{
    if(L[now]==R[now])
    {
        val[now]=sqrt(val[now]),sum[now]=val[now];
        return;
    }
    if(l<=mid[now]&&val[now<<1]>1) updata(now<<1,l,r);
    if(r>mid[now]&&val[now<<1|1]>1) updata(now<<1|1,l,r);
    val[now]=max(val[now<<1],val[now<<1|1]);
    sum[now]=sum[now<<1]+sum[now<<1|1];
}
ll query(ll now,ll l,ll r)
{
    if(L[now]>=l&&R[now]<=r) return sum[now];
    ll res=0;
    if(l<=mid[now]) res+=query(now<<1,l,r);
    if(r>mid[now]) res+=query(now<<1|1,l,r);
    return res;
}
int main()
{
    while(scanf("%lld",&n)!=EOF)
    {
        build(1,1,n),in(m);
        ll op,l,r;
        while(m--)
        {
            in(op),in(l),in(r);
            if(l>r) swap(l,r);
            if(op==1) printf("%lld\n",query(1,l,r));
            else updata(1,l,r);
        }
    }
    return 0;
}
