#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real INF=5e9;
const int maxn=2005;
struct point
{
    real x,y;
    bool operator<(const point pos)const
    {
        if(x==pos.x) return y<pos.y;
        return x<pos.x;
    }
};
struct point ai[maxn],up[maxn],down[maxn],bi[maxn];
struct line
{
    real k,b,A,B,C;
};
int n,sta[maxn],numup,numdown,cnt;
real ans;
real getk(point a,point b)
{
    if(a.x==b.x) return INF;
    return (a.y-b.y)/(a.x-b.x);
}
line operator+(point a,point b)
{
    line res;
    res.k=getk(a,b),res.b=a.y-a.x*res.k;
    res.A=res.k,res.B=-1,res.C=res.b;
    return res;
}
bool upordown(line tmp,point c)
{
    if(c.y>=tmp.k*c.x+tmp.b) return true;
    return false;
}
real getdis(line base,point pos)
{
    return fabs(pos.x*base.A+pos.y*base.B+base.C)/
            sqrt(base.A*base.A+base.B*base.B);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&ai[i].x,&ai[i].y);
    sort(ai+1,ai+n+1);
    real basek=getk(ai[1],ai[n]);
    line baseline=ai[1]+ai[n];
    int top=1;
    sta[top]=1;
    for(int i=2;i<=n;i++)
    {
        if(i!=n&&!upordown(baseline,ai[i])) continue;
        while(top>1&&getk(ai[i],ai[sta[top]])>=getk(ai[i],ai[sta[top-1]])) top--;
        sta[++top]=i;
    }
    while(top) up[++numup]=ai[sta[top--]];
    sta[top=1]=1;
    for(int i=2;i<=n;i++)
    {
        if(i!=n&&upordown(baseline,ai[i])) continue;
        while(top>1&&getk(ai[i],ai[sta[top]])<=getk(ai[i],ai[sta[top-1]])) top--;
        sta[++top]=i;
    }
    while(top) down[++numdown]=ai[sta[top--]];
    for(int i=numup;i>1;i--) bi[++cnt]=up[i];
    for(int i=1;i<numdown;i++) bi[++cnt]=down[i];
    line tmp;
    for(int i=1;i<cnt;i++)
    {
        int pre=i,suf=i+1,lit=cnt-2,pos=0;
        for(int v=i+1;v<=cnt;v++)
        {
            tmp=bi[i]+bi[v];
            while(pos<lit&&(getdis(tmp,bi[suf])<getdis(tmp,bi[suf%cnt+1]))) suf=(suf%cnt)+1,pos++;
            while(pre<v&&(getdis(tmp,bi[pre])<getdis(tmp,bi[pre+1]))) pre++;
            ans=max(ans,(getdis(tmp,bi[pre])+getdis(tmp,bi[suf]))*
                    sqrt((bi[i].x-bi[v].x)*(bi[i].x-bi[v].x)+(bi[i].y-bi[v].y)*(bi[i].y-bi[v].y))/2);
        }
    }
    printf("%.3lf",ans);
    return 0;
}
