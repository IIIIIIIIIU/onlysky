#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const int maxn=1005;
const int maxm=maxn*maxn;
struct EdgeType
{
    int u,v;
    real w;
    bool operator<(const EdgeType &pos)const
    {
        return w<pos.w;
    }
};
struct EdgeType e[maxm];
int n,m,cnt,f[maxn];
real xi[maxn],yi[maxn],ans=1e9;
int find(int x)
{
    if(x==f[x]) return x;
    return f[x]=find(f[x]);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%lf%lf",&xi[i],&yi[i]);
    for(int i=1;i<=n;i++)
        for(int v=i+1;v<=n;v++)
        {
            cnt++;
            e[cnt].u=i,e[cnt].v=v;
            e[cnt].w=sqrt((xi[i]-xi[v])*(xi[i]-xi[v])+(yi[i]-yi[v])*(yi[i]-yi[v]));
        }
    sort(e+1,e+cnt+1);
    for(int i=1;i<=n;i++) f[i]=i;
    int tmp=n,u,v;
    for(int i=1;i<=cnt;i++)
    {
        u=e[i].u,v=e[i].v;
        u=find(u),v=find(v);
        if(u!=v) f[u]=v,tmp--;
        if(tmp<m)
        {
            ans=e[i].w;
            break;
        }
    }
    printf("%.2lf",ans);
    return 0;
}
