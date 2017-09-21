#include <cmath>
#include <cstdio>
#include <iostream>
 
using namespace std;
 
#define eps 1e-8
#define maxn 205
 
int ai[maxn][maxn],bi[maxn][maxn],ma,mi,pre[maxn],s,t,h,tail,cnt;
int n,head[maxn],E[maxn*maxn],V[maxn*maxn],F[maxn*maxn],que[maxn<<8];
 
double W[maxn*maxn],suma,sumb,dis[maxn];
 
bool if_[maxn];
 
inline void in(int &now_)
{
    register int now=0;
    register char Cget=getchar();
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
    now_=now;
}
 
inline bool spfa()
{
    for(int i=s;i<=t;i++) dis[i]=-1e6,pre[i]=-1,if_[i]=false;
    h=maxn<<4,tail=h+1,que[h]=s,dis[s]=0,if_[s]=true;
    while(h<tail)
    {
        register int now=que[h++];if_[now]=false;
        for(register int i=head[now];i;i=E[i])
        {
            if(dis[V[i]]<dis[now]+W[i]&&F[i]>0)
            {
                pre[V[i]]=i;
                dis[V[i]]=dis[now]+W[i];
                if(!if_[V[i]])
                {
                    if_[V[i]]=true;
                    if(dis[V[i]]>dis[que[h]]) que[--h]=V[i];
                    else que[tail++]=V[i];
                }
            }
        }
    }
    return dis[t]!=-1e6;
}
 
int main()
{
    in(n);t=n<<1|1;
    for(register int i=1;i<=n;i++)
    {
        ma=0;
        for(register int j=1;j<=n;j++) in(ai[i][j]),ma=max(ma,ai[i][j]);
        suma+=ma;
    }
    for(register int i=1;i<=n;i++)
    {
        mi=0x7fffffff;
        for(register int j=1;j<=n;j++) in(bi[i][j]),mi=min(mi,bi[i][j]);
        sumb+=mi;
    }
    double l=0,r=suma/sumb,mid,ans;
    while(r-l>eps)
    {
        mid=(l+r)/2.0,cnt=1;
        for(register int i=s;i<=t;i++) head[i]=0;
        for(register int i=1;i<=n;i++)
        {
            E[++cnt]=head[s],V[cnt]=i,F[cnt]=1,W[cnt]=0,head[s]=cnt;
            E[++cnt]=head[i],V[cnt]=s,F[cnt]=0,W[cnt]=0,head[i]=cnt;
            E[++cnt]=head[t],V[cnt]=i+n,F[cnt]=0,W[cnt]=0,head[t]=cnt;
            E[++cnt]=head[i+n],V[cnt]=t,F[cnt]=1,W[cnt]=0,head[i+n]=cnt;
            for(register int j=1;j<=n;j++)
            {
                register int o=j+n;
                register double pos=(double)ai[i][j]-mid*bi[i][j];
                E[++cnt]=head[i],V[cnt]=o,F[cnt]=1,W[cnt]=pos,head[i]=cnt;
                E[++cnt]=head[o],V[cnt]=i,F[cnt]=0,W[cnt]=-pos,head[o]=cnt;
            }
        }
        double sum=0;
        while(spfa())
        {
            sum+=dis[t];
            register int now=t;
            while(pre[now]!=-1) F[pre[now]]--,F[pre[now]^1]++,now=V[pre[now]^1];
        }
        if(sum>0) ans=mid,l=mid+eps;
        else r=mid-eps;
    }
    printf("%.6lf",ans);
    return 0;
}
