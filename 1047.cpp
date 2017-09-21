#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct ReType {
    int mi,ma;
};
 
struct TreeNodeType {
    int l,r,lc,rc,ma,mi,mid;
};
struct TreeNodeType tree[(1005<<2)*1005];
 
int tot=0,a,b,n,root[1005],blo[1005],ans=0x7fffffff,X;
 
inline ReType node(int k,int f)
{
    ReType no;
    no.mi=k,no.ma=f;
    return no;
}
 
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
 
inline void tree_build(int &now,int l,int r)
{
    now=++tot,tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        in(tree[now].mi);
        tree[now].ma=tree[now].mi;
        return ;
    }
    tree[now].mid=l+r>>1;
    tree_build(tree[now].lc,l,tree[now].mid);
    tree_build(tree[now].rc,tree[now].mid+1,r);
    tree[now].mi=min(tree[tree[now].lc].mi,tree[tree[now].rc].mi);
    tree[now].ma=max(tree[tree[now].lc].ma,tree[tree[now].rc].ma);
}
 
inline ReType tree_query(int now,int l,int r)
{
    if(tree[now].l==l&&tree[now].r==r) return node(tree[now].mi,tree[now].ma);
    if(r<=tree[now].mid) return tree_query(tree[now].lc,l,r);
    else if(l>tree[now].mid) return tree_query(tree[now].rc,l,r);
    else
    {
        ReType la=tree_query(tree[now].lc,l,tree[now].mid);
        ReType ra=tree_query(tree[now].rc,tree[now].mid+1,r);
        return node(min(la.mi,ra.mi),max(la.ma,ra.ma));
    }
}
 
inline void tree_build_(int &now,int l,int r)
{
    now=++tot,tree[now].l=l,tree[now].r=r;
    if(l==r)
    {
        ReType an=tree_query(root[l],X-n+1,X);
        tree[now].mi=an.mi,tree[now].ma=an.ma;
        return ;
    }
    tree[now].mid=l+r>>1;
    tree_build_(tree[now].lc,l,tree[now].mid);
    tree_build_(tree[now].rc,tree[now].mid+1,r);
    tree[now].mi=min(tree[tree[now].lc].mi,tree[tree[now].rc].mi);
    tree[now].ma=max(tree[tree[now].lc].ma,tree[tree[now].rc].ma);
}
 
int main()
{
    in(a),in(b),in(n);
    for(int i=1;i<=a;i++) tree_build(root[i],1,b);
    int pos=tot;
    for(int i=n;i<=b;i++)
    {
        tot=pos,X=i,tree_build_(blo[i],1,a);
        for(int j=n;j<=a;j++)
        {
            ReType an=tree_query(blo[i],j-n+1,j);
            ans=min(ans,an.ma-an.mi);
        }
    }
    cout<<ans;
    return 0;
}
