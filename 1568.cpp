#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real eps=1e-6;
const int maxn=500005;
const int maxtree=maxn<<2;
struct node
{
    int l,r,mid;
    double a,b;
    bool tag;
};
struct node tree[maxtree];
int n;
void build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r;
    tree[now].mid=l+r>>1;if(l==r) return;
    build(now<<1,l,tree[now].mid);
    build(now<<1|1,tree[now].mid+1,r);
}
inline real getpos(real a1,real b1,real a2,real b2)
{
    if(b2==b1) return 0;
    return (a1-a2)/(b2-b1);
}
void add(int now,double a,double b)
{
    if(tree[now].l==0) return;
    if(!tree[now].tag)
    {
        tree[now].tag=true;
        tree[now].a=a,tree[now].b=b;
        return;
    }
    else
    {
        real p=getpos(a,b,tree[now].a,tree[now].b);
        if(p<tree[now].l+eps&&p>tree[now].r-eps)
        {
            if(a+tree[now].mid*b>tree[now].a+tree[now].b*tree[now].mid)
                tree[now].a=a,tree[now].b=b;
            return;
        }
        if(p<=tree[now].mid+eps)
            if(b<tree[now].b) add(now<<1,a,b);
            else add(now<<1,tree[now].a,tree[now].b),tree[now].a=a,tree[now].b=b;
        else
            if(b>tree[now].b) add(now<<1|1,a,b);
            else add(now<<1|1,tree[now].a,tree[now].b),tree[now].a=a,tree[now].b=b;
    }
}
real query(int now,int to)
{
    real res=0;
    if(tree[now].tag) res=tree[now].a+tree[now].b*to;
    if(tree[now].l==tree[now].r) return res;
    if(to<=tree[now].mid) return max(res,query(now<<1,to));
    else return max(res,query(now<<1|1,to));
}
int main()
{
    scanf("%d",&n);
    build(1,1,60000);
    char op[15];
    real a,b;int x;
    while(n--)
    {
        scanf("%s",op);
        if(op[0]=='P') scanf("%lf%lf",&a,&b),add(1,a-b,b);
        else scanf("%d",&x),printf("%d\n",(int)query(1,x)/100);
    }
    return 0;
}
