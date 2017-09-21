#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 100005
#define ll long long
 
struct TreeNodeType {
    ll l,r,fa,fm,dis,mid;
};
struct TreeNodeType tree[maxn<<2];
 
ll n,p,t,X;
 
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
 
void tree_build(ll now,ll l,ll r)
{
    tree[now].l=l,tree[now].r=r,tree[now].fm=1;
    if(l==r)
    {
        in(tree[now].dis);
        tree[now].dis%=p;
        return ;
    }
    tree[now].mid=l+r>>1;
    tree_build(now<<1,l,tree[now].mid);
    tree_build(now<<1|1,tree[now].mid+1,r);
    tree[now].dis=(tree[now<<1].dis+tree[now<<1|1].dis)%p;
}
 
inline void tree_down(ll now)
{
    tree[now<<1].dis=((tree[now<<1].dis*tree[now].fm)%p+(tree[now<<1].r-tree[now<<1].l+1)*tree[now].fa%p)%p;
    tree[now<<1|1].dis=((tree[now<<1|1].dis*tree[now].fm)%p+(tree[now<<1|1].r-tree[now<<1|1].l+1)*tree[now].fa%p)%p;
    tree[now<<1].fm=(tree[now<<1].fm*tree[now].fm)%p;
    tree[now<<1|1].fm=(tree[now<<1|1].fm*tree[now].fm)%p;
    tree[now<<1].fa=(tree[now<<1].fa*tree[now].fm%p+tree[now].fa)%p;
    tree[now<<1|1].fa=(tree[now<<1|1].fa*tree[now].fm%p+tree[now].fa)%p;
    tree[now].fa=0,tree[now].fm=1;
}
 
void tree_do(ll now,ll l,ll r)
{
    if(tree[now].l==l&&tree[now].r==r)
    {
        if(t==1)
        {
            tree[now].fm=(tree[now].fm*X)%p;
            tree[now].fa=(tree[now].fa*X)%p;
            tree[now].dis=(tree[now].dis*X)%p;
            return ;
        }
        else if(t==2)
        {
            tree[now].fa=(tree[now].fa+X)%p;
            tree[now].dis=(tree[now].dis+(tree[now].r-tree[now].l+1)*X)%p;
        }
        else X=(X+tree[now].dis)%p;
        return ;
    }
    if(tree[now].fa||tree[now].fm!=1) tree_down(now);
    if(l>tree[now].mid) tree_do(now<<1|1,l,r);
    else if(r<=tree[now].mid) tree_do(now<<1,l,r);
    else
    {
        tree_do(now<<1,l,tree[now].mid);
        tree_do(now<<1|1,tree[now].mid+1,r);
    }
    tree[now].dis=(tree[now<<1].dis+tree[now<<1|1].dis)%p;
}
 
int main()
{
    in(n),in(p);
    tree_build(1,1,n);
    ll m,u,v;
    in(m);
    while(m--)
    {
        in(t),in(u),in(v);
        if(t==1||t==2) in(X),tree_do(1,u,v);
        else X=0,tree_do(1,u,v),printf("%lld\n",X);
    }
    return 0;
}
