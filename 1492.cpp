#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int maxn=120005;
const real eps=1e-9,INF=1e9;
struct query
{
    real q,a,b,rate,k;
    int pos;
} q[maxn],nq[maxn];
real fabs(real x)
{
    return(x>0)?x:-x;
}
struct point
{
    double x,y;
    friend bool operator<(const point &a,const point &b)
    {
        return (a.x<b.x+eps)||(fabs(a.x-b.x)<=eps&&a.y<b.y+eps);
    }
} p[maxn],np[maxn];
int st[maxn],n,m;
real f[maxn];
real getk(int i,int j)
{
    if(i==0) return -INF;
    if(j==0) return INF;
    if(fabs(p[i].x-p[j].x)<=eps) return -INF;
    return (p[i].y-p[j].y)/(p[i].x-p[j].x);
}
void solve(int l,int r)
{
    if(l==r)
    {
        f[l]=max(f[l-1],f[l]);
        p[l].y=f[l]/(q[l].a*q[l].rate+q[l].b);
        p[l].x=p[l].y*q[l].rate;
        return;
    }
    int mid=l+r>>1,l1=l,l2=mid+1;
    for(int i=l;i<=r;i++)
        if(q[i].pos<=mid) nq[l1++]=q[i];
        else nq[l2++]=q[i];
    for(int i=l;i<=r;i++) q[i]=nq[i];
    solve(l,mid);
    int top=0;
    for(int i=l;i<=mid;i++)
    {
        while(top>=2&&getk(i,st[top])+eps>getk(st[top],st[top-1])) top--;
        st[++top]=i;
    }
    int j=1;
    for(int i=r;i>=mid+1;i--)
    {
        while(j<top&&q[i].k<getk(st[j],st[j+1])+eps) j++;
        f[q[i].pos]=max(f[q[i].pos],p[st[j]].x*q[i].a+p[st[j]].y*q[i].b);
    }
    solve(mid+1,r);
    l1=l,l2=mid+1;
    for(int i=l;i<=r;i++)
        if((p[l1]<p[l2]||l2>r)&&l1<=mid) np[i]=p[l1++];
        else np[i]=p[l2++];
    for(int i=l;i<=r;i++) p[i]=np[i];
}
bool cmp(query a,query b)
{
    return a.k<b.k;
}
int main()
{
    scanf("%d%lf",&n,&f[0]);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf",&q[i].a,&q[i].b,&q[i].rate);
        q[i].k=-q[i].a/q[i].b,q[i].pos=i;
    }
    sort(q+1,q+n+1,cmp);
    solve(1,n);
    printf("%.3lf\n",f[n]);
    return 0;
}
