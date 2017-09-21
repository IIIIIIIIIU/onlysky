#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxtree maxn<<2
int val[maxtree],L[maxtree],R[maxtree],mid[maxtree];
int len[maxtree],tag[maxtree],n,ai[maxn],bi[maxn];
int op[maxn],ql[maxn],qr[maxn],q,m;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r,len[now]=r-l+1,tag[now]=0;
    if(l==r)
    {
        val[now]=bi[l];
        return;
    }
    mid[now]=l+r>>1,build(now<<1,l,mid[now]);
    build(now<<1|1,mid[now]+1,r),val[now]=val[now<<1]+val[now<<1|1];
}
void pushdown(int now)
{
    if(tag[now]==1)
    {
        tag[now<<1]=1,tag[now<<1|1]=1;
        val[now<<1]=0,val[now<<1|1]=0;
    }
    else
    {
        tag[now<<1]=2,tag[now<<1|1]=2;
        val[now<<1]=len[now<<1],val[now<<1|1]=len[now<<1|1];
    }
    tag[now]=0;
}
void change(int now,int l,int r,int x)
{
    if(L[now]>=l&&R[now]<=r)
    {
        tag[now]=x;
        if(x==1) val[now]=0;
        else val[now]=len[now];
        return;
    }
    if(tag[now]) pushdown(now);
    if(l<=mid[now]) change(now<<1,l,r,x);
    if(r>mid[now]) change(now<<1|1,l,r,x);
    val[now]=val[now<<1]+val[now<<1|1];
}
int query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r) return val[now];
    if(tag[now]) pushdown(now);int res=0;
    if(l<=mid[now]) res+=query(now<<1,l,r);
    if(r>mid[now]) res+=query(now<<1|1,l,r);
    return res;
}
bool check(int x)
{
    for(int i=1;i<=n;i++) bi[i]=(ai[i]>=x);
    build(1,1,n);int tmp;
    for(int i=1;i<=m;i++)
    {
        tmp=query(1,ql[i],qr[i]);
        if(!op[i])
        {
            if(tmp!=qr[i]-ql[i]+1&&tmp) change(1,ql[i],qr[i]-tmp,1),change(1,qr[i]-tmp+1,qr[i],2);
            else if(tmp==qr[i]-ql[i]+1) change(1,ql[i],qr[i],2);
            else change(1,ql[i],qr[i],1);
        }
        else
        {
            if(tmp!=qr[i]-ql[i]+1&&tmp) change(1,ql[i],ql[i]+tmp-1,2),change(1,ql[i]+tmp,qr[i],1);
            else if(tmp==qr[i]-ql[i]+1) change(1,ql[i],qr[i],2);
            else change(1,ql[i],qr[i],1);
        }
    }
    return query(1,q,q);
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++) in(ai[i]);
    for(int i=1;i<=m;i++) in(op[i]),in(ql[i]),in(qr[i]);
    int l=1,r=n,mid,ans;in(q);
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) l=mid+1,ans=mid;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
