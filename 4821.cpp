#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
struct TreeNodeType {
    int l,r,mid;
    double flagx2,flagy2,flagx3,flagy3,size;
    double sumx,sumy,suml,sumxy,sumx2,sumy2,suml2;
    bool if_3;
    inline void updata2(double posx,double posy)
    {
        sumx2+=size*posx*posx+2*posx*sumx;
        sumy2+=size*posy*posy+2*posy*sumy;
        sumxy+=size*posx*posy+sumx*posy+sumy*posx;
        sumx+=size*posx,sumy+=size*posy;
        flagx2+=posx,flagy2+=posy;
    }
    inline void updata3(double posx,double posy)
    {
        sumxy=size*posx*posy+suml*(posx+posy)+suml2;
        sumx2=size*posx*posx+posx*2*suml+suml2;
        sumy2=size*posy*posy+posy*2*suml+suml2;
        sumx=size*posx+suml,sumy=size*posy+suml;
        if_3=true,flagx3=posx,flagy3=posy;
        flagx2=0,flagy2=0;
    }
};
struct TreeNodeType tree[maxn<<2];
int n,m;
double Sumx,Sumy,Sumx2,Sumy2,Sumxy,ai[maxn],bi[maxn];
inline void updata(int now)
{
    tree[now].sumx=tree[now<<1].sumx+tree[now<<1|1].sumx;
    tree[now].sumy=tree[now<<1].sumy+tree[now<<1|1].sumy;
    tree[now].suml=tree[now<<1].suml+tree[now<<1|1].suml;
    tree[now].sumxy=tree[now<<1].sumxy+tree[now<<1|1].sumxy;
    tree[now].sumx2=tree[now<<1].sumx2+tree[now<<1|1].sumx2;
    tree[now].sumy2=tree[now<<1].sumy2+tree[now<<1|1].sumy2;
    tree[now].suml2=tree[now<<1].suml2+tree[now<<1|1].suml2;
}
void build(int now,int l,int r)
{
    tree[now].l=l,tree[now].r=r,tree[now].size=r-l+1;
    if(l==r)
    {
        tree[now].sumx=ai[l],tree[now].sumy=bi[l],tree[now].suml=l;
        tree[now].sumxy=ai[l]*bi[l],tree[now].suml2=(double)l*l;
        tree[now].sumx2=ai[l]*ai[l],tree[now].sumy2=bi[l]*bi[l];
        return;
    }
    tree[now].mid=l+r>>1;
    build(now<<1,l,tree[now].mid);
    build(now<<1|1,tree[now].mid+1,r);
    updata(now);
}
inline void pushdown(int now)
{
    if(tree[now].if_3)
    {
        tree[now].if_3=false;
        tree[now<<1].updata3(tree[now].flagx3,tree[now].flagy3);
        tree[now<<1|1].updata3(tree[now].flagx3,tree[now].flagy3);
    }
    if(tree[now].flagx2||tree[now].flagy2)
    {
        tree[now<<1].updata2(tree[now].flagx2,tree[now].flagy2);
        tree[now<<1|1].updata2(tree[now].flagx2,tree[now].flagy2);
        tree[now].flagx2=0,tree[now].flagy2=0;
    }
}
void operation1(int now,int l,int r)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        Sumx+=tree[now].sumx,Sumy+=tree[now].sumy;
        Sumx2+=tree[now].sumx2,Sumy2+=tree[now].sumy2;
        Sumxy+=tree[now].sumxy;return;
    }
    if(tree[now].if_3||tree[now].flagx2||tree[now].flagy2) pushdown(now);
    if(l<=tree[now].mid) operation1(now<<1,l,r);
    if(r>tree[now].mid) operation1(now<<1|1,l,r);
}
void operation2(int now,int l,int r,double s,double t)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        tree[now].updata2(s,t);
        return;
    }
    if(tree[now].if_3||tree[now].flagx2||tree[now].flagy2) pushdown(now);
    if(l<=tree[now].mid) operation2(now<<1,l,r,s,t);
    if(r>tree[now].mid) operation2(now<<1|1,l,r,s,t);
    updata(now);
}
void operation3(int now,int l,int r,double s,double t)
{
    if(tree[now].l>=l&&tree[now].r<=r)
    {
        tree[now].updata3(s,t);
        return;
    }
    if(tree[now].if_3||tree[now].flagx2||tree[now].flagy2) pushdown(now);
    if(l<=tree[now].mid) operation3(now<<1,l,r,s,t);
    if(r>tree[now].mid) operation3(now<<1|1,l,r,s,t);
    updata(now);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lf",&ai[i]);
    for(int i=1;i<=n;i++) scanf("%lf",&bi[i]);
    build(1,1,n);
    int op,l,r;double s,t;
    while(m--)
    {
        scanf("%d%d%d",&op,&l,&r);
        if(op==1)
        {
            Sumx=0,Sumy=0,Sumxy=0,Sumx2=0,Sumy2=0;
            operation1(1,l,r);
            double size=r-l+1,x_=Sumx/size,y_=Sumy/size;
            double a=Sumxy-Sumy*x_-Sumx*y_+y_*x_*size;
            double b=Sumx2-2*Sumx*x_+x_*x_*size;
            printf("%.10lf\n",a/b);
        }
        if(op==2) scanf("%lf%lf",&s,&t),operation2(1,l,r,s,t);
        if(op==3) scanf("%lf%lf",&s,&t),operation3(1,l,r,s,t);
    }
    return 0;
}
