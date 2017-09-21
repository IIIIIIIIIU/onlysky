#include <bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define maxm 200005
#define maxn_ maxn<<2
#define INF 0x7fffffff
struct TreeNodeType {
    int l,r,dis,mid,flag;
};
struct TreeNodeType tree[maxn_];
struct QueryType {
    int l,r,len;
    bool operator <(const QueryType pos)const
    {
        return pos.len>len;
    }
};
struct QueryType qu[maxn];
int n,m,bi[maxn_],cnt,size,ans=INF;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0')Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
void build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r;
    if(l==r) return;tree[now].mid=l+r>>1;
    build(now<<1,l,tree[now].mid);
    build(now<<1|1,tree[now].mid+1,r);
}
inline void pushdata(int now)
{
    tree[now<<1].dis+=tree[now].flag;
    tree[now<<1].flag+=tree[now].flag;
    tree[now<<1|1].dis+=tree[now].flag;
    tree[now<<1|1].flag+=tree[now].flag;
    tree[now].flag=0;
}
void updata(int now,int l,int r,int x)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        tree[now].dis+=x,tree[now].flag+=x;
        return;
    }
    if(tree[now].flag!=0) pushdata(now);
    if(l<=tree[now].mid) updata(now<<1,l,r,x);
    if(r>tree[now].mid) updata(now<<1|1,l,r,x);
    tree[now].dis=max(tree[now<<1].dis,tree[now<<1|1].dis);
}
int query(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r) return tree[now].dis;
    if(tree[now].flag!=0) pushdata(now);
    int res=0;
    if(l<=tree[now].mid) res=max(res,query(now<<1,l,r));
    if(r>tree[now].mid) res=max(res,query(now<<1|1,l,r));
    return res;
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++)
    {
        in(qu[i].l),in(qu[i].r);
        qu[i].len=qu[i].r-qu[i].l+1;
        bi[++cnt]=qu[i].l,bi[++cnt]=qu[i].r;
    }
    sort(qu+1,qu+n+1);
    sort(bi+1,bi+cnt+1);
    size=unique(bi+1,bi+cnt+1)-bi-1;
    int now=0,pos;build(1,1,size);
    for(int i=1;i<=n;i++)
    {
        qu[i].l=lower_bound(bi+1,bi+size+1,qu[i].l)-bi;
        qu[i].r=lower_bound(bi+1,bi+size+1,qu[i].r)-bi;
        updata(1,qu[i].l,qu[i].r,1);
        while(tree[1].dis>=m)
        {
            now++,pos=query(1,qu[now].l,qu[now].r);
            if(pos>=m) ans=min(qu[i].len-qu[now].len,ans);
            updata(1,qu[now].l,qu[now].r,-1);
        }
    }
    printf("%d\n",ans==INF?-1:ans);
    return 0;
}
