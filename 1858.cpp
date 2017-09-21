#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
struct TreeNodeType { 
    int l,r,l1,r1,m1,l0,r0,m0,mid,size,cnt1,cnt0;
    bool f1,f0,ff;
    inline void turn(){swap(l1,l0),swap(r1,r0),swap(m1,m0),swap(cnt1,cnt0);}
    inline void turn1(){l0=0,r0=0,m0=0,cnt0=0,l1=size,r1=size,m1=size,cnt1=size;}
    inline void turn0(){l1=0,r1=0,m1=0,cnt1=0,l0=size,r0=size,m0=size,cnt0=size;}
    inline void F1(){f1=true,f0=false,ff=false;}
    inline void F0(){f0=true,f1=false,ff=false;}
    inline void FF(){
        if(f1) f0=true,f1=false;
        else if(f0) f1=true,f0=false;
        else ff^=1;
    }
    inline void turnzero(){f1=false,f0=false,ff=false;}
};
struct TreeNodeType tree[maxn<<2];
struct AnsType {
    int l,r,m,s;
};
int n,m,Count;
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
inline void updata(int now)
{
    tree[now].cnt1=tree[now<<1].cnt1+tree[now<<1|1].cnt1;
    tree[now].cnt0=tree[now<<1].cnt0+tree[now<<1|1].cnt0;
    tree[now].l1=tree[now<<1].size==tree[now<<1].l1?tree[now<<1].l1+tree[now<<1|1].l1:tree[now<<1].l1;
    tree[now].l0=tree[now<<1].size==tree[now<<1].l0?tree[now<<1].l0+tree[now<<1|1].l0:tree[now<<1].l0;
    tree[now].r1=tree[now<<1|1].size==tree[now<<1|1].r1?tree[now<<1|1].r1+tree[now<<1].r1:tree[now<<1|1].r1;
    tree[now].r0=tree[now<<1|1].size==tree[now<<1|1].r0?tree[now<<1|1].r0+tree[now<<1].r0:tree[now<<1|1].r0;
    tree[now].m1=max(tree[now<<1].r1+tree[now<<1|1].l1,max(tree[now<<1].m1,tree[now<<1|1].m1));
    tree[now].m0=max(tree[now<<1].r0+tree[now<<1|1].l0,max(tree[now<<1].m0,tree[now<<1|1].m0));
}
inline void downdata(int now)
{
    if(tree[now].f1) tree[now<<1].turn1(),tree[now<<1|1].turn1(),tree[now<<1].F1(),tree[now<<1|1].F1();
    if(tree[now].f0) tree[now<<1].turn0(),tree[now<<1|1].turn0(),tree[now<<1].F0(),tree[now<<1|1].F0();
    if(tree[now].ff) tree[now<<1].turn(),tree[now<<1|1].turn(),tree[now<<1].FF(),tree[now<<1|1].FF();
    tree[now].turnzero();
}
inline void build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r,tree[now].size=r-l+1;
    if(l==r)
    {
        int pos;
        in(pos);
        if(pos) tree[now].l1=1,tree[now].r1=1,tree[now].m1=1,tree[now].cnt1=1;
        else tree[now].l0=1,tree[now].r0=1,tree[now].m0=1,tree[now].cnt0=1;
        return;
    }
    tree[now].mid=l+r>>1;
    build(now<<1,l,tree[now].mid);
    build(now<<1|1,tree[now].mid+1,r);
    updata(now);
}
inline void operation0(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r){tree[now].turn0(),tree[now].F0();return;}
    if(tree[now].f1||tree[now].f0||tree[now].ff) downdata(now);
    if(l<=tree[now].mid) operation0(now<<1,l,min(r,tree[now].mid));
    if(r>tree[now].mid) operation0(now<<1|1,max(tree[now].mid+1,l),r);
    updata(now);    
}
inline void operation1(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r){tree[now].turn1(),tree[now].F1();return;}  
    if(tree[now].f1||tree[now].f0||tree[now].ff) downdata(now);
    if(l<=tree[now].mid) operation1(now<<1,l,min(r,tree[now].mid));
    if(r>tree[now].mid) operation1(now<<1|1,max(tree[now].mid+1,l),r);
    updata(now);
}
inline void operation2(int now,int l,int r)
{   
    if(tree[now].l>=l&&tree[now].r<=r){tree[now].turn(),tree[now].FF();return;}   
    if(tree[now].f1||tree[now].f0||tree[now].ff) downdata(now);
    if(l<=tree[now].mid) operation2(now<<1,l,min(r,tree[now].mid));
    if(r>tree[now].mid) operation2(now<<1|1,max(tree[now].mid+1,l),r);
    updata(now);
}
inline void operation3(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r){Count+=tree[now].cnt1;return;}
    if(tree[now].f1||tree[now].f0||tree[now].ff) downdata(now);
    if(l<=tree[now].mid) operation3(now<<1,l,min(r,tree[now].mid));
    if(r>tree[now].mid) operation3(now<<1|1,max(l,tree[now].mid+1),r);
    updata(now);
}
inline AnsType operation4(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r) return (AnsType){tree[now].l1,tree[now].r1,tree[now].m1,tree[now].size};
    if(tree[now].f1||tree[now].f0||tree[now].ff) downdata(now);
    bool al=false,ar=false;AnsType Al,Ar,res;
    if(l<=tree[now].mid) al=true,Al=operation4(now<<1,l,min(r,tree[now].mid));
    if(r>tree[now].mid) ar=true,Ar=operation4(now<<1|1,max(l,tree[now].mid+1),r);
    if(al&&ar)
    {
        res.s=Al.s+Ar.s;
        res.l=Al.s==Al.l?Al.l+Ar.l:Al.l;
        res.r=Ar.s==Ar.r?Ar.r+Al.r:Ar.r;
        res.m=max(Al.r+Ar.l,max(Al.m,Ar.m));
        return res;
    }
    return al?Al:Ar;
}
int main()
{
    in(n),in(m),build(1,0,n-1);
    int op,l,r;AnsType pos;
    while(m--)
    {
        in(op),in(l),in(r);
        if(op==0) operation0(1,l,r);
        if(op==1) operation1(1,l,r);
        if(op==2) operation2(1,l,r);
        if(op==3) Count=0,operation3(1,l,r),printf("%d\n",Count);
        if(op==4) pos=operation4(1,l,r),printf("%d\n",max(max(pos.l,pos.r),pos.m));
    }
    return 0;
}
