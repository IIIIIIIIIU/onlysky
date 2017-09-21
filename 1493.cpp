#include <bits/stdc++.h>
//#include <cstdio>
using namespace std;
const int maxn=500005,maxtree=maxn<<2|1;
struct ValType
{
    int l,r,val;
    ValType(int l_=0,int r_=0,int val_=0)
    {
        l=l_,r=r_,val=val_;
    }
    ValType operator+(const ValType &pos)const
    {
        return ValType(l,pos.r,val+pos.val-((pos.l==r)?1:0));
    }
} val[maxtree];
int L[maxtree],R[maxtree],mid[maxtree],tag[maxtree];
int n,C,S;
bool rev;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void build(int now,int l,int r)
{
    L[now]=l,R[now]=r;
    if(l==r)
    {
        in(val[now].l),val[now].r=val[now].l;
        val[now].val=1;return;
    }
    mid[now]=l+r>>1,build(now<<1,l,mid[now]);
    build(now<<1|1,mid[now]+1,r),val[now]=val[now<<1]+val[now<<1|1];
}
void pushdown(int now)
{
    val[now<<1].val=val[now<<1|1].val=1;
    val[now<<1].l=val[now<<1].r=tag[now];
    val[now<<1|1].l=val[now<<1|1].r=tag[now];
    tag[now<<1]=tag[now<<1|1]=tag[now],tag[now]=0;
}
void change(int now,int l,int r,int x)
{
    if(L[now]>=l&&R[now]<=r)
    {
        tag[now]=val[now].l=val[now].r=x,val[now].val=1;
        return;
    }
    if(tag[now]) pushdown(now);
    if(l<=mid[now]) change(now<<1,l,r,x);
    if(r>mid[now]) change(now<<1|1,l,r,x);
    val[now]=val[now<<1]+val[now<<1|1];
}
ValType query(int now,int l,int r)
{
    if(L[now]>=l&&R[now]<=r) return val[now];
    if(tag[now]) pushdown(now);ValType res;bool did=false;
    if(l<=mid[now]) res=query(now<<1,l,r),did=true;
    if(r>mid[now])
        if(did) res=res+query(now<<1|1,l,r);
        else res=query(now<<1|1,l,r);
    return res;
}
void getpos(int &x,int &y)
{
    if(rev)
    {
        x=(n+n+2-S-x)%n;
        y=(n+n+2-S-y)%n;
        swap(x,y);
    }
    else
    {
        x=(x-S+n)%n;
        y=(y-S+n)%n;
    }
    if(!x) x=n;
    if(!y) y=n;
}
int main()
{
//  freopen("necklace.in","r",stdin);
//  freopen("necklace.out","w",stdout);
//  freopen("data.txt","r",stdin);
    in(n),in(C),build(1,1,n),in(C);
    char op[5];int x,l,r;
    ValType tmp1,tmp2;
    while(C--)
    {
//      printf("%d sda\n",S);
        scanf("%s",op);
        if(op[0]=='R')
        {
            in(x);
            if(rev) S=(S+n-x)%n;
            else S=(S+x)%n;
        }
        else if(op[0]=='F') rev^=1;
        else if(op[0]=='S')
        {
            in(l),in(r),getpos(l,r);
            tmp1=query(1,l,l),tmp2=query(1,r,r);
            change(1,l,l,tmp2.l),change(1,r,r,tmp1.l);
        }
        else if(op[0]=='P')
        {
            in(l),in(r),in(x),getpos(l,r);
            if(l<=r) change(1,l,r,x);
            else change(1,1,r,x),change(1,l,n,x);
        }
        else if(op[0]=='C')
        {
            if(op[1]=='S')
            {
                in(l),in(r),getpos(l,r);
                if(l<=r) tmp1=query(1,l,r),printf("%d\n",tmp1.val);
                else tmp1=query(1,l,n)+query(1,1,r),printf("%d\n",tmp1.val);
            }
            else
            {
                tmp1=query(1,1,n);
                printf("%d\n",max(1,tmp1.val-(tmp1.l==tmp1.r)));
            }
        }
    }   
    return 0;
}
