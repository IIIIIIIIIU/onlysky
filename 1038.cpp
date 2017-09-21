#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int maxn=305;
const real eps=1e-7;
const real INF=5e9;
struct point;
struct line;
struct point
{
    real x,y;
};
struct point ai[maxn],di[maxn];
struct line
{
    real k,b;
    bool operator<(const line& pos) const
    {
        if(k==pos.k) return b<pos.b;
        return k<pos.k;
    }
    point operator&(const line& pos)const
    {
        point res;
        if(k-pos.k<=eps&&k-pos.k>=eps) return res;
        res.x=(pos.b-b)/(k-pos.k);
        res.y=res.x*k+b;
        return res;
    }
};
struct line bi[maxn],ci[maxn];
int n,sta[maxn],cnt,cntc;
line operator+(point a,point pos)
{
    line res;
    if(a.x==pos.x)
    {
        res.k=INF;
        res.b=0;return res;
    }
    res.k=(pos.y-a.y)/(pos.x-a.x);
    res.b=a.y-a.x*res.k;
    return res;
}
real operator*(point a,line pos)
{
    real res=a.x*pos.k+pos.b;
    return fabs(res-a.y);
}
real get(real x,line a,line b)
{
    real ya=x*a.k+a.b;
    real yb=x*b.k+b.b;
    return fabs(ya-yb);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf",&ai[i].x);
    for(int i=1;i<=n;i++) scanf("%lf",&ai[i].y);
    for(int i=1;i<n;i++) bi[i]=ai[i+1]+ai[i];
    sort(bi+1,bi+n),sta[1]=1;int top=1;
    point tmp1,tmp2;
    for(int i=2;i<n;i++)
    {
        while(top>1)
        {
            tmp1=bi[i]&bi[sta[top-1]];
            tmp2=bi[sta[top]]&bi[sta[top-1]];
            if(tmp1.x<=tmp2.x+eps) top--;
            else break;
        }
        sta[++top]=i;
    }
    cntc=top;
    while(top) ci[top]=bi[sta[top--]];
    cnt++,di[1].x=ai[1].x,di[1].y=ci[1].k*di[1].x+ci[1].b;
    for(int i=2;i<=cntc;i++)
    {
        tmp1=ci[i]&ci[i-1];
        if(tmp1.x>di[cnt].x) di[++cnt]=tmp1;
    }
    tmp1.x=ai[n].x,tmp1.y=tmp1.x*ci[cntc].k+ci[cntc].b;
    if(tmp1.x>di[cnt].x) di[++cnt]=tmp1;
    int l,r;real ans=INF;line tmp3;
    point tmpl,tmpr;
    for(int i=2;i<=n;i++)
    {
        tmp1=ai[i-1],tmp2=ai[i];
        for(int v=2;v<=cnt;v++)
        {
            tmpl=di[v-1],tmpr=di[v],tmp3=tmpl+tmpr;
            if(tmp1.x>=tmpl.x&&tmp2.x<=tmpr.x)
                ans=min(ans,min(tmp1*tmp3,tmp2*tmp3));
            else if(tmp1.x<tmpl.x&&tmp2.x>tmpr.x)
                ans=min(ans,min(tmpl*(tmp1+tmp2),tmpr*(tmp1+tmp2)));
            else if(tmpl.x<tmp1.x&&tmpr.x>=tmp1.x&&tmpr.x<=tmp2.x)
                ans=min(ans,min(tmp1*tmp3,get(tmpr.x,tmp1+tmp2,tmp3)));
            else if(tmpl.x>=tmp1.x&&tmpl.x<=tmp2.x&&tmpr.x>tmp2.x)
                ans=min(ans,min(tmp2*tmp3,get(tmpl.x,tmp1+tmp2,tmp3)));
        }
    }
    printf("%.3lf\n",ans);
    return 0;
}
