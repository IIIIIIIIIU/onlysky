#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 100005
#define ll long long
#define maxtree maxn<<2
ll n,m,val[maxtree],val1[maxtree],val2[maxtree],len[maxtree],len2[maxtree];
ll L[maxtree],R[maxtree],mid[maxtree],size[maxtree],tag[maxtree];
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
void build(ll now,ll l,ll r)
{
    L[now]=l,R[now]=r,size[now]=r-l+1;
    if(l==r)
    {
        len[now]=l,len2[now]=l*l;
        return;
    }
    mid[now]=l+r>>1;
    build(now<<1,l,mid[now]);
    build(now<<1|1,mid[now]+1,r);
    len[now]=len[now<<1]+len[now<<1|1];
    len2[now]=len2[now<<1]+len2[now<<1|1];
}
void pushdown(ll now)
{
    val[now<<1]+=size[now<<1]*tag[now];
    val[now<<1|1]+=size[now<<1|1]*tag[now];
    val1[now<<1]+=len[now<<1]*tag[now];
    val1[now<<1|1]+=len[now<<1|1]*tag[now];
    val2[now<<1]+=len2[now<<1]*tag[now];
    val2[now<<1|1]+=len2[now<<1|1]*tag[now];
    tag[now<<1]+=tag[now],tag[now<<1|1]+=tag[now],tag[now]=0;
}
void add(ll now,ll l,ll r,ll x)
{
    if(L[now]>=l&&R[now]<=r)
    {
        val[now]+=size[now]*x;
        val1[now]+=len[now]*x;
        val2[now]+=len2[now]*x;
        tag[now]+=x;
        return;
    }
    if(tag[now]) pushdown(now);
    if(l<=mid[now]) add(now<<1,l,r,x);
    if(r>mid[now]) add(now<<1|1,l,r,x);
    val[now]=val[now<<1]+val[now<<1|1];
    val1[now]=val1[now<<1]+val1[now<<1|1];
    val2[now]=val2[now<<1]+val2[now<<1|1];
}
ll query(ll now,ll l,ll r,ll to)
{
    if(L[now]>=l&&R[now]<=r)
    {
        if(to==0) return val[now];
        else if(to==1) return val1[now];
        else return val2[now];
    }
    if(tag[now]) pushdown(now);ll res=0;
    if(l<=mid[now]) res+=query(now<<1,l,r,to);
    if(r>mid[now]) res+=query(now<<1|1,l,r,to);
    return res;
}
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}
int main()
{
    in(n),in(m),build(1,1,n-1);
    char op[3];ll tmp,tmp1,tmp2,l,r,x,g;
    while(m--)
    {
        scanf("%s",op),in(l),in(r);
        if(op[0]=='C')
        {
            in(x);
            add(1,l,r-1,x);
        }
        else
        {
            x=((r-l+1)*(r-l))>>1,tmp=query(1,l,r-1,0)*(r-l*r);
            tmp1=query(1,l,r-1,1)*(l+r-1),tmp2=-query(1,l,r-1,2);
            tmp+=tmp1+tmp2,g=gcd(tmp,x),tmp/=g,x/=g;
            printf("%lld/%lld\n",tmp,x);
        }
    }
    return 0;
}
