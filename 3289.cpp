#include <bits/stdc++.h>
using namespace std;
#define maxn 50005
int bel[maxn],blo;
struct QueryType {
    int l,r,id;
    bool operator<(const QueryType pos)const
    {
        if(bel[l]==bel[pos.l]) return r<pos.r;
        return bel[l]<bel[pos.l];
    }
};
struct QueryType qu[maxn];
int n,m,ai[maxn],bi[maxn],tree[maxn],size,now,ans[maxn];
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
inline int lowbit(int x)
{
    return x&(-x);
}
inline void add(int x,int di)
{
    while(x<=n)
    {
        tree[x]+=di;
        x+=lowbit(x);
    }
}
inline int sum(int l,int r)
{
    int res=0;l--;
    while(r) res+=tree[r],r-=lowbit(r);
    while(l) res-=tree[l],l-=lowbit(l);
    return res;
}
inline void updatar(int x,bool di)
{
    x=ai[x];
    if(di)
    {
        if(x<size) now+=sum(x+1,size);
        add(x,1);
    }
    else
    {
        if(x<size) now-=sum(x+1,size);
        add(x,-1);
    }
}
inline void updatal(int x,bool di)
{
    x=ai[x];
    if(di)
    {
        if(x>1) now+=sum(1,x-1);
        add(x,1);
    }
    else
    {
        if(x>1) now-=sum(1,x-1);
        add(x,-1);
    }
}
int main()
{
    in(n),blo=sqrt(n);
    for(int i=1;i<=n;i++) in(ai[i]),bi[i]=ai[i],bel[i]=(i+1)/blo;
    sort(bi+1,bi+n+1),size=unique(bi+1,bi+n+1)-bi-1;
    for(int i=1;i<=n;i++) ai[i]=lower_bound(bi+1,bi+size+1,ai[i])-bi;
    in(m);
    for(int i=1;i<=m;i++) in(qu[i].l),in(qu[i].r),qu[i].id=i;
    sort(qu+1,qu+m+1);int l=1,r=0;
    for(int i=1;i<=m;i++)
    {
        while(r<qu[i].r) updatar(++r,true);
        while(r>qu[i].r) updatar(r--,false);
        while(l>qu[i].l) updatal(--l,true);
        while(l<qu[i].l) updatal(l++,false);
        ans[qu[i].id]=now;
    }
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
    return 0;
}
