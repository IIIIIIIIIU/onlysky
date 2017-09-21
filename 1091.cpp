#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real eps=1e-9;
const real INF=1e9;
struct point
{
    real x,y;
};
struct point pi[105],p1[105],p2[105];
struct line
{
    real k,b;
};
struct line baseline[105],baseline2[5];
int num,bit[100];
real n,m,dp[1005];
line operator+(point a,point b)
{
    line res;
    if(a.x==b.x)
    {
        res.k=INF,res.b=a.x;
        return res;
    }
    res.k=(a.y-b.y)/(a.x-b.x);
    res.b=a.y-a.x*res.k;
    return res;
}
point operator&(line a,line b)
{
    point res;
    res.x=res.y=0;
    if(a.k==b.k) return res;
    if(b.k==INF) swap(a,b);
    if(a.k==INF)
    {
        res.x=a.b,res.y=b.k*res.x+b.b;
        return res;
    }
    res.x=(b.b-a.b)/(a.k-b.k);
    res.y=res.x*a.k+a.b;
    return res;
}
real dist(point x,point y)
{
    return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}
int main()
{
    scanf("%lf%lf",&n,&m);
    scanf("%d",&num);
    for(int i=1;i<=num;i++) scanf("%lf%lf",&pi[i].x,&pi[i].y);
    for(int i=2;i<=num;i++) baseline[i-1]=pi[i]+pi[i-1],p1[i-1]=pi[i-1],p2[i-1]=pi[i];
    baseline[num]=pi[num]+pi[1],p1[num]=pi[1],p2[num]=pi[num];
    baseline2[1].k=0,baseline2[1].b=0;
    baseline2[2].k=INF,baseline2[2].b=0;
    baseline2[3].k=0,baseline2[3].b=m;
    baseline2[4].k=INF,baseline2[4].b=n;
    for(int i=1;i<=num;i++)
    {
        if(p1[i].x==p2[i].x)
        {
            if(p1[i].y>p2[i].y) swap(p1[i],p2[i]);
        }
        else if(p1[i].x>p2[i].x) swap(p1[i],p2[i]);
    }
    bit[1]=1;for(int i=2;i<=num;i++) bit[i]=bit[i-1]<<1;dp[0]=0;
    for(int i=1;i<=(bit[num]<<1)-1;i++)
    {
        dp[i]=INF;
        if(i==4)
        {
            int opk=0;
        }
        for(int v=1;v<=num;v++)
            if((bit[v]&i)==bit[v])
            {
                int pos=i^bit[v];
                point l,r,tmp;
                l.x=-INF,l.y=-INF,r.x=INF,r.y=INF;
                if(p1[v].x!=p2[v].x)
                {
                    for(int e=1;e<=4;e++)
                    {
                        if(baseline[v].k==baseline2[e].k) continue;
                        tmp=baseline[v]&baseline2[e];
                        if(tmp.x<=p1[v].x+eps&&tmp.x>l.x) l=tmp;
                        if(tmp.x>=p2[v].x-eps&&tmp.x<r.x) r=tmp;
                    }
                    for(int e=1;e<=num;e++)
                        if((bit[e]&pos)&&e!=v)
                        {
                            if(baseline[v].k==baseline[e].k) continue;
                            tmp=baseline[v]&baseline[e];
                            if(tmp.x<=p1[v].x+eps&&tmp.x>l.x) l=tmp;
                            if(tmp.x>=p2[v].x-eps&&tmp.x<r.x) r=tmp;
                        }
                }
                else
                {
                    for(int e=1;e<=4;e++)
                    {
                        if(baseline[v].k==baseline2[e].k) continue;
                        tmp=baseline[v]&baseline2[e];
                        if(tmp.y<=p1[v].y+eps&&tmp.y>l.y) l=tmp;
                        if(tmp.y>=p2[v].y-eps&&tmp.y<r.y) r=tmp;
                    }
                    for(int e=1;e<=num;e++)
                        if((bit[e]&pos)&&e!=v)
                        {
                            if(baseline[v].k==baseline[e].k) continue;
                            tmp=baseline[v]&baseline[e];
                            if(tmp.y<=p1[v].y+eps&&tmp.y>l.y) l=tmp;
                            if(tmp.y>=p2[v].y-eps&&tmp.y<r.y) r=tmp;
                        }
                }
                dp[i]=min(dp[i],dp[pos]+dist(l,r));
            }
    }
    printf("%.3lf",dp[(bit[num]<<1)-1]);
    return 0;
}
