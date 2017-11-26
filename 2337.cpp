#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-10;
const int maxn=2e2+5;

struct EdgeType
{
    int v,w;
    
    EdgeType *next;
    
    EdgeType(){}
    
    EdgeType(int v_,int w_,EdgeType *next_)
    {
        v=v_;
        w=w_;
        next=next_;
    }
};

struct EdgeType *head[maxn];

int n,m,du[maxn];

real f[maxn][maxn],ans;

inline void read(int &now)
{
    char Cget;
    now=0;
    while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}

void gauss()
{
    int N=n<<1;
    for(int i=1;i<=N;i++)
    {
        int tmp=i;
        real cur=std::abs(f[i][i]);
        for(int v=i+1;v<=N;v++)
            if(std::abs(f[v][i])+eps>cur)
            {
                cur=std::abs(f[v][i]);
                tmp=v;
            }
        if(tmp!=i)
            std::swap(f[i],f[tmp]);
        for(int v=i+1;v<=N;v++)
            if(f[v][i]>=eps||f[v][i]<=-eps)
            {
                real temp=f[v][i]/f[i][i];
                for(int e=i;e<=N+1;e++)
                    f[v][e]=f[v][e]-f[i][e]*temp;
            }
    }
    f[N][N]=f[N][N+1]/f[N][N];
    for(int i=N-1;i>=1;i--)
    {
        for(int v=N;v>i;v--)
            f[i][N+1]-=f[i][v]*f[v][v];
        f[i][i]=f[i][N+1]/f[i][i];
    }
}

int main()
{
//	freopen("xorpath.in","r",stdin);
//	freopen("xorpath.out","w",stdout);
//	freopen("data.txt","r",stdin);
    read(n);
    read(m);
    for(int i=1;i<=n;i++)
        head[i]=NULL;
    for(int i=1,u,v,w;i<=m;i++)
    {
        read(u);
        read(v);
        read(w);
        head[u]=new EdgeType(v,w,head[u]);
        du[u]++;
        if(u!=v)
        {
            head[v]=new EdgeType(u,w,head[v]);
            du[v]++;
        }
    }
    for(int i=0;i<=30;i++)
    {
        memset(f,0,sizeof(f));
        for(int v=1;v<=n;v++)
        {
            f[v][v]=1;
            f[v+n][v+n]=1;
            for(EdgeType *e=head[v];e!=NULL;e=e->next)
                if(e->v!=n)
                {
                    if(e->w&(1<<i))
                    {
                        f[v][e->v+n]-=(real)1.0/du[e->v];
                        f[v+n][e->v]-=(real)1.0/du[e->v];
                    }
                    else
                    {
                        f[v][e->v]-=(real)1.0/du[e->v];
                        f[v+n][e->v+n]-=(real)1.0/du[e->v];
                    }
                }
        }
        f[1][n+n+1]=1;
        gauss();
        ans+=(1<<i)*f[n+n][n+n];
    }
    printf("%.3lf\n",ans);
    return 0;
}
