#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 50005
#define ll long long
 
struct QueryType {
    ll l,r,id;
};
struct QueryType qu[maxn];
 
ll n,m,col[maxn],ans[maxn],pos=0,fa[maxn],num[maxn],bel[maxn],size;
 
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
 
bool cmp(QueryType iposa,QueryType iposb)
{
    if(bel[iposa.l]==bel[iposb.l]) return iposa.r<iposb.r;
    else return iposa.l<iposb.l;
}
 
inline void updata(ll now,ll dis)
{
    now=col[now];
    pos-=num[now]*num[now];
    num[now]+=dis;
    pos+=num[now]*num[now];
}
 
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
 
int main()
{
    in(n),in(m);size=sqrt(n);
    for(ll i=1;i<=n;i++) in(col[i]),bel[i]=(i-1)/size;
    for(ll i=1;i<=m;i++) in(qu[i].l),in(qu[i].r),qu[i].id=i;
    sort(qu+1,qu+m+1,cmp);
    ll li=1,ri=0;
    for(ll j=1;j<=m;j++)
    {
        if(ri>qu[j].r) for(ll i=ri;i>qu[j].r;i--) updata(i,-1);
        else for(ll i=ri+1;i<=qu[j].r;i++) updata(i,1);
        if(li>qu[j].l) for(ll i=li-1;i>=qu[j].l;i--) updata(i,1);
        else for(ll i=li;i<qu[j].l;i++) updata(i,-1);
        ri=qu[j].r,li=qu[j].l,ans[qu[j].id]=pos-(ri-li+1);
        if(qu[j].r-qu[j].l>=2) fa[qu[j].id]=(ri-li+1)*(ri-li);
    }
    for(ll i=1;i<=m;i++)
    {
        if(fa[i]==0||ans[i]==0)
        {
            printf("0/1\n");
            continue;
        }
        ll o=gcd(fa[i],ans[i]);
        printf("%lld/%lld\n",ans[i]/o,fa[i]/o);
    }
    return 0;
}
