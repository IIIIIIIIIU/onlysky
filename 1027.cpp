#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxn 505
typedef double real;
const real eps=1e-7;
const real INF=1e9;
struct point
{
    real x,y;
    point operator-(const point pos)const
    {
        point res;
        res.x=x-pos.x,res.y=y-pos.y;
        return res;
    }
};
struct point ai[maxn],bi[maxn];
int n,m,f[maxn][maxn];
real cross(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}
real cross(point a,point b,point c)
{
    return cross(b-a,c-a);
}
real dot(point a,point b)
{
    return a.x*b.x+a.y*b.y;
}
real dot(point a,point b,point c)
{
    return dot(b-a,c-a);
}
int main()
{
    scanf("%d%d",&n,&m);real pos;
    for(int i=1;i<=n;i++) scanf("%lf%lf%lf",&ai[i].x,&ai[i].y,&pos);
    for(int i=1;i<=m;i++) scanf("%lf%lf%lf",&bi[i].x,&bi[i].y,&pos);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++) f[i][v]=INF;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
        {
            bool FLAG=true;real tmp;
            for(int e=1;e<=m;e++)
            {
                tmp=cross(bi[e],ai[i],ai[v]);
                if(tmp>eps||(fabs(tmp)<eps&&dot(bi[e],ai[i],ai[v])>eps))
                {
                    FLAG=false;
                    break;
                }
            }
            if(FLAG) f[i][v]=1;
        }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int v=1;v<=n;v++)
                f[i][v]=min(f[i][v],f[i][k]+f[k][v]);
    int ans=INF;
    for(int i=1;i<=n;i++) ans=min(ans,f[i][i]);
    if(ans==INF) cout<<-1;
    else cout<<ans;
    return 0;
}
