#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real eps=1e-7;
const int maxn=300005;
struct point
{
    real x,y;
    int id;
    bool operator<(const point &pos)const
    {
        return x<pos.x;
    }
};
struct point pi[maxn],ul[maxn],dr[maxn];
int n,m,numr,numc,ans[maxn],ans_[maxn];
real xr[maxn],yr[maxn],R[maxn];
int erfenl(real tmp)
{
    int l=1,r=m,mid,res=m+1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(pi[mid].x>tmp+eps) res=mid,r=mid-1;
        else l=mid+1;
    }
    return res;
}
int erfenr(real tmp)
{
    int l=1,r=m,mid,res=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if(pi[mid].x<tmp-eps) res=mid,l=mid+1;
        else r=mid-1;
    }
    return res;
}
int main()
{
    scanf("%d%d",&n,&m);
    char op[3];
    for(int i=1;i<=n;i++)
    {
        scanf("%s",op);
        if(op[0]=='r')
            numr++,scanf("%lf%lf%lf%lf",&ul[numr].x,&ul[numr].y,&dr[numr].x,&dr[numr].y);
        else
            numc++,scanf("%lf%lf%lf",&xr[numc],&yr[numc],&R[numc]);
    }
    for(int i=1;i<=m;i++) scanf("%lf%lf",&pi[i].x,&pi[i].y),pi[i].id=i;
    sort(pi+1,pi+m+1);
    for(int i=1;i<=numr;i++)
    {
        int l=erfenl(ul[i].x),r=erfenr(dr[i].x);
        for(int v=l;v<=r;v++) if(pi[v].y>ul[i].y+eps&&pi[v].y<dr[i].y-eps) ans[v]++;
    }
    for(int i=1;i<=numc;i++)
    {
        int l=erfenl(xr[i]-R[i]),r=erfenr(xr[i]+R[i]);
        for(int v=l;v<=r;v++)
            if((pi[v].x-xr[i])*(pi[v].x-xr[i])+(pi[v].y-yr[i])*(pi[v].y-yr[i])<R[i]*R[i]-eps)
                ans[v]++;
    }
    for(int i=1;i<=m;i++) ans_[pi[i].id]=ans[i];
    for(int i=1;i<=m;i++) printf("%d\n",ans_[i]);
    return 0;
}
