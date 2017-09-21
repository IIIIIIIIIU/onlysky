#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef double real;
const real INF=1e9;
const real eps=1e-7;
struct point
{
    real x,y;
    real operator*(const point &pos)const
    {
        return x*pos.y-y*pos.x;
    }
    point operator-(const point &pos)const
    {
        point res;
        res.x=x-pos.x;
        res.y=y-pos.y;
        return res;
    }
    real operator%(const point &pos)const
    {
        return x*pos.x+y*pos.y;
    }
    point operator/(real a)
    {
        point res;
        res.x=x/a,res.y=y/a;
        return res;
    }
    bool operator==(const point &pos)const
    {
        return x>=pos.x-eps&&x<=pos.x+eps&&y>=pos.y-eps&&y<=pos.y+eps;
    }
    bool operator<(const point &pos)const
    {
        if(x==pos.x) return y<pos.y;
        return x<pos.x;
    }
    point operator&(const point &pos)const
    {
        point res;
        res.x=pos.x+x,res.y=pos.y+y;
        return res;
    }
};
inline real dis(point p)
{
    return sqrt(p.x*p.x+p.y*p.y);
}
inline real angle(point p,point q)
{
    return acos(p%q/dis(p)/dis(q));
}
inline point rotate(point p,real A)
{
    real s=sin(A),c=cos(A);
    point res;
    res.x=p.x*c-p.y*s;
    res.y=p.x*s+p.y*c;
    return res;
}
struct point bi[100],pi[100005];
struct line
{
    real A,B,C,k,b;
    point p1,p2;
    point operator^(const point &pos)const
    {
        point res;
        res.x=pos.x-A*2*(A*pos.x+B*pos.y+C)/(A*A+B*B);
        res.y=pos.y-B*2*(A*pos.x+B*pos.y+C)/(A*A+B*B);
        return res;
    }
};
struct line ai[100];
int n,m,cnt;
inline point get(point b,line l,int f)
{
    return l.p1&rotate(b-l.p1,angle(b-l.p1,l.p2)*2*f);
}
line operator+(point a,point b)
{
    line res;
    if(a.x==b.x) res.k=INF;else res.k=(a.y-b.y)/(a.x-b.x);
    res.b=a.y-a.x*res.k,res.A=res.k,res.B=-1,res.C=res.b;
    return res;
}
real cross(point a,point b,point c)
{
    return (c-a)*b;
}
void dfs(point now,int k)
{
    pi[++cnt]=now;
    if(!k) return;
    dfs(now,k-1);
    if(cross(ai[k].p1,ai[k].p2,now)<-eps) //dfs(ai[k]^now,k-1);
        dfs(get(now,ai[k],-1),k-1);
}
bool find(point now,point end)
{
    real tmp;
    for(int i=1;i<=n;i++)
    {
        tmp=cross(ai[i].p1,ai[i].p2,now);
        if(tmp>=-eps&&tmp<=eps) return false;
        if(tmp>eps) //now=ai[i]^now;
            now=get(now,ai[i],1);
    }
    return now==end;
}
bool can(point pos)
{
    return pos.x>eps&&pos.x<100-eps&&pos.y>eps&&pos.y<100-eps;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf%lf",&ai[i].p1.x,&ai[i].p1.y,&ai[i].p2.x,&ai[i].p2.y);
        line tmp=ai[i].p1+ai[i].p2;
        ai[i].k=tmp.k,ai[i].b=tmp.b,ai[i].A=tmp.A,ai[i].B=tmp.B,ai[i].C=tmp.C;
        ai[i].p2=ai[i].p2-ai[i].p1;
    }
    scanf("%d",&m);
    point pos;
    while(m--)
    {
        scanf("%lf%lf",&pos.x,&pos.y);
        cnt=0,dfs(pos,n);
        sort(pi+1,pi+cnt+1);
        cnt=unique(pi+1,pi+cnt+1)-pi-1;
        int res=0;
        for(int i=1;i<=cnt;i++)
            if(can(pi[i])&&find(pi[i],pos)) res++;
        printf("%d\n",res);
    }
    return 0;
}
