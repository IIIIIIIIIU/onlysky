#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real eps=1e-6,INF=5e9;
real ax,ay,bx,by,cx,cy,dx,dy,p1,p2,p3,ans=INF,len1,len2;
real dist(real X1,real Y1,real X2,real Y2)
{
    return sqrt((X1-X2)*(X1-X2)+(Y1-Y2)*(Y1-Y2));
}
real get(real rate)
{
    real res=(len1*rate/100)/p1,sx=ax+(bx-ax)*rate/100,sy=ay+(by-ay)*rate/100;
    real l=0,r=100,mid1,mid2,tmp1,tmp2,ex,ey,ret;
    while(r-l>eps)
    {
        mid1=(l+r)/2,mid2=(mid1+r)/2;
        ex=dx+(cx-dx)*mid1/100,ey=dy+(cy-dy)*mid1/100;
        tmp1=(len2*mid1/100)/p2+res+dist(sx,sy,ex,ey)/p3;
        ex=dx+(cx-dx)*mid2/100,ey=dy+(cy-dy)*mid2/100;
        tmp2=(len2*mid2/100)/p2+res+dist(sx,sy,ex,ey)/p3;
        if(tmp1<tmp2) ret=tmp1,r=mid2-eps;
        else ret=tmp2,l=mid1+eps;
    }
    return ret;
}
int main()
{
    cin>>ax>>ay>>bx>>by>>cx>>cy>>dx>>dy>>p1>>p2>>p3;
    real l=0,r=100,mid1,mid2,tmp1,tmp2;
    len1=dist(ax,ay,bx,by),len2=dist(cx,cy,dx,dy);
    while(r-l>eps)
    {
        mid1=(l+r)/2,mid2=(mid1+r)/2;
        tmp1=get(mid1),tmp2=get(mid2);
        if(tmp1<tmp2) ans=tmp1,r=mid2-eps;
        else ans=tmp2,l=mid1+eps;
    }
    printf("%.2lf\n",ans);
    return 0;
}
