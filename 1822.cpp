#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int maxn=205;
const real INF=1e9;
const int INFi=0x3f3f3f3f;
struct circle
{
    real x,y,r;
};
struct circle tree[maxn];
struct point
{
    real x,y;
    real operator-(const point &pos)const
    {
        return sqrt((x-pos.x)*(x-pos.x)+(y-pos.y)*(y-pos.y));
    }
    point(int x_=0,int y_=0)
    {
        x=x_,y=y_;
    }
};
struct point lich[maxn],fairy[maxn];
struct segment
{
    point p1,p2;
    real k,b,A,B,C;
};
struct edge
{
    int u,v;
    edge(int u_=0,int v_=0)
    {
        u=u_,v=v_;
    }
};
struct edge e[maxn*maxn];
int n,m,k,cnte,deep[maxn*3],que[maxn*3],s,t,head[maxn*3],cnt,E[maxn*maxn*4];
int V[maxn*maxn*4],F[maxn*maxn*4],ti[maxn];
real R[maxn];
bool vis[maxn];
segment operator+(const point &a,const point &b)
{
    segment res;
    res.p1=a,res.p2=b;
    if(a.x==b.x) res.k=INF,res.b=a.x;
    else if(a.y==b.y) res.k=0,res.b=a.y;
    else
    {
        res.k=(a.y-b.y)/(a.x-b.x);
        res.b=a.y-a.x*res.k;
    }
    res.A=res.k,res.B=-1,res.C=res.b;
    return res;
}
real cross(point a,point b,point c)
{
    real xa=b.x-a.x,ya=b.y-a.y;
    real xb=c.x-a.x,yb=c.y-a.y;
    return xa*yb-xb*ya;
}
real dot(point a,point b,point c)
{
    real xa=b.x-a.x,ya=b.y-a.y;
    real xb=c.x-a.x,yb=c.y-a.y;
    return xa*xb+ya*yb;
}
bool operator&(const segment &a,const circle &b)
{
    point tmp1,tmp2,tmp3;
    tmp1=point(a.p1.x,a.p1.y);
    tmp2=point(a.p2.x,a.p2.y);
    tmp3=point(b.x,b.y);
    if(dot(tmp3,tmp1,tmp2)>=0)
        return min(tmp1-tmp3,tmp2-tmp3)<=b.r;
    else
        return abs(cross(tmp1,tmp3,tmp2))/(tmp1-tmp2)<=b.r;
}
inline void edge_add(int u,int v,int f)
{
    E[++cnt]=head[u],V[cnt]=v,F[cnt]=f,head[u]=cnt;
    E[++cnt]=head[v],V[cnt]=u,F[cnt]=0,head[v]=cnt;
}
bool bfs()
{
    for(int i=s;i<=t;i++) deep[i]=-1;
    int h=0,tail=1,now;deep[s]=0,que[0]=s;
    while(h<tail)
        for(int i=head[now=que[h++]];i;i=E[i])
            if(F[i]&&deep[V[i]]<0)
            {
                deep[V[i]]=deep[now]+1;
                if(V[i]==t) return true;
                que[tail++]=V[i];
            }
    return false;
}
int flowing(int now,int flow)
{
    if(now==t||flow<=0) return flow;
    int oldflow=0,tmp;
    for(int i=head[now];i;i=E[i])
        if(F[i]&&deep[V[i]]==deep[now]+1)
        {
            tmp=flowing(V[i],min(F[i],flow));
            F[i]-=tmp,F[i^1]+=tmp,oldflow+=tmp,flow-=tmp;
            if(!flow) return oldflow;
        }
    if(flow) deep[now]=-1;
    return oldflow;
}
bool check(int lit)
{
    s=0,t=n+m+1,cnt=1;
    for(int i=s;i<=t;i++) head[i]=0;
    for(int i=1;i<=n;i++) edge_add(s,i,(int)(lit/ti[i])+1);
    for(int i=n+1;i<=n+m;i++) edge_add(i,t,1);
    for(int i=1;i<=cnte;i++) edge_add(e[i].u,e[i].v+n,1);
    int res=0;
    while(bfs()) res+=flowing(s,INFi);
    return res>=m;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf%lf%d",&lich[i].x,&lich[i].y,&R[i],&ti[i]);
    for(int i=1;i<=m;i++)
        scanf("%lf%lf",&fairy[i].x,&fairy[i].y);
    for(int i=1;i<=k;i++)
        scanf("%lf%lf%lf",&tree[i].x,&tree[i].y,&tree[i].r);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            if(lich[i]-fairy[v]<=R[i])
            {
                bool can=true;
                segment tmp=lich[i]+fairy[v];
                for(int z=1;z<=k;z++)
                    if(tmp&tree[z])
                    {
                        can=false;
                        break;
                    }
                if(can) e[++cnte]=edge(i,v),vis[v]=true;
            }
    int cur=0;
    for(int i=1;i<=m;i++) cur+=vis[i];
    if(cur<m)
    {
        cout<<-1;
        return 0;
    }
    int l=0,r=4000000,mid,ans=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) ans=mid,r=mid-1;
        else l=mid+1;
    }
    cout<<ans;
    return 0;
}
