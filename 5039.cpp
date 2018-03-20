#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=1e5+5;
const int maxtree=maxn<<2|1;

int n,m,L[maxtree],R[maxtree],mid[maxtree];

ll val[maxtree],tag1[maxtree],tag2[maxtree],mod;

inline void read(int &now)
{
    char Cget;
    now=0;
    int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')
        if(Cget=='-')
            if_z=-1;
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}

inline void read(ll &now)
{
    char Cget;
    now=0;
    int if_z=1;
    while((Cget=getchar())>'9'||Cget<'0')
        if(Cget=='-')
            if_z=-1;
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now*=if_z;
}

void build(int now,int l,int r)
{
    L[now]=l;
    R[now]=r;
    tag2[now]=1;
    if(l==r)
    {
        read(val[now]);
        return;
    }
    mid[now]=l+r>>1;
    build(now<<1,l,mid[now]);
    build(now<<1|1,mid[now]+1,r);
    val[now]=(val[now<<1]+val[now<<1|1])%mod;
}

inline void pushdown(int now)
{
    if(tag2[now]!=1)
    {
        (val[now<<1]*=tag2[now])%=mod;
        (tag1[now<<1]*=tag2[now])%=mod;
        (tag2[now<<1]*=tag2[now])%=mod;
        (val[now<<1|1]*=tag2[now])%=mod;
        (tag1[now<<1|1]*=tag2[now])%=mod;
        (tag2[now<<1|1]*=tag2[now])%=mod;
        tag2[now]=1;
    }
    if(tag1[now])
    {
        (val[now<<1]+=tag1[now]*(R[now<<1]-L[now<<1]+1)%mod)%=mod;
        (val[now<<1|1]+=tag1[now]*(R[now<<1|1]-L[now<<1|1]+1)%mod)%=mod;
        (tag1[now<<1]+=tag1[now])%=mod;
        (tag1[now<<1|1]+=tag1[now])%=mod;
        tag1[now]=0;
    }
}

void updata_add(int now,int l,int r,ll x)
{
    if(L[now]>=l&&R[now]<=r)
    {
        (val[now]+=((R[now]-L[now]+1)*x)%mod)%=mod;
        (tag1[now]+=x)%=mod;
        return;
    }
    pushdown(now);
    if(l<=mid[now])
        updata_add(now<<1,l,r,x);
    if(r>mid[now])
        updata_add(now<<1|1,l,r,x);
    (val[now]=val[now<<1]+val[now<<1|1])%=mod;
}

void updata_mul(int now,int l,int r,ll x)
{
    if(L[now]>=l&&R[now]<=r)
    {
        (val[now]*=x)%=mod;
        (tag2[now]*=x)%=mod;
        (tag1[now]*=x)%=mod;
        return;
    }
    pushdown(now);
    if(l<=mid[now])
        updata_mul(now<<1,l,r,x);
    if(r>mid[now])
        updata_mul(now<<1|1,l,r,x);
    (val[now]=val[now<<1]+val[now<<1|1])%=mod;
}

ll query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r)
        return val[now]%mod;
    pushdown(now);
    ll res=0;
    if(l<=mid[now])
        res=query(now<<1,l,r);
    if(r>mid[now])
        (res+=query(now<<1|1,l,r))%=mod;
    return res;
}

int main()
{
    read(n);
    read(mod);
    build(1,1,n);
    read(m);
    int op,l,r;
    ll x;
    while(m--)
    {
        read(op);
        read(l);
        read(r);
        if(op==1)
        {
            read(x);
            updata_mul(1,l,r,x);
        }
        if(op==2)
        {
            read(x);
            updata_add(1,l,r,x);
        }
        if(op==3)
        {
            printf("%lld\n",query(1,l,r));
        }
    }
    return 0;
}
