#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int mod=65521;
struct node
{
    int u,v;
};
struct node edge[15];
struct Matrix
{
    int n;
    long long Mat[60][60];
    Matrix operator*(const Matrix &pos)const
    {
        Matrix res;
        res.n=n;
        for(int i=1;i<=n;i++)
            for(int v=1;v<=n;v++)
            {
                res.Mat[i][v]=0;
                for(int e=1;e<=n;e++)
                    (res.Mat[i][v]+=(Mat[i][e]*pos.Mat[e][v])%mod)%=mod;
            }
        return res;
    }
};
int bel[1<<11],ShState[105],cntState,Mat[105][105];
int k,bit[15],cnte,BelBlock[105],f[105];
long long n;
bool vis[1<<11];
int find(int x)
{
    if(f[x]==x) return x;
    return find(f[x]);
}
void dfs(int now)
{
    if(now==k+1)
    {
        int tmp=0;
        for(int i=1;i<=cnte;i++)
            if(BelBlock[edge[i].u]==BelBlock[edge[i].v])
             tmp|=bit[i];
        if(!bel[tmp])
        {
            bel[tmp]=++cntState;
            ShState[cntState]=tmp;
        }
        return;
    }
    for(int i=1;i<=now;i++)
        BelBlock[now]=i,dfs(now+1);
}
void FindNext(int S,int now,int to)
{
    if(now==to)
    {
        int u,v,tmp=0;
        for(int i=1;i<=cnte;i++)
        {
            u=edge[i].u+1,v=edge[i].v+1;
            if(find(u)==find(v)) tmp|=bit[i];
        }
        u=find(1);
        for(int i=2;i<=to;i++)
            if(u==find(i))
            {
                Mat[S][bel[tmp]]++;
                break;
            }
        return;
    }
    int u=find(now),v=find(to);
    if(u!=v)
    {
        int back=f[u];
        f[u]=v;
        FindNext(S,now+1,to);
        f[u]=back;
    }
    FindNext(S,now+1,to);
}
long long get(int tmp)
{
    int ai[10],res=1;
    for(int i=1;i<=k;i++) f[i]=i,ai[i]=1;
    for(int i=1;i<=cnte;i++)
        if((tmp&bit[i])&&find(edge[i].u)!=find(edge[i].v))
        {
            ai[find(edge[i].u)]+=ai[find(edge[i].v)];
            ai[find(edge[i].v)]=0;
            f[find(edge[i].v)]=find(edge[i].u);
        }
    for(int i=1;i<=k;i++)
        if(ai[i]>2) res*=pow(ai[i],ai[i]-2);
    return res;
}
int main()
{
    scanf("%d%lld",&k,&n);
    for(int i=1;i<k;i++)
        for(int v=i+1;v<=k;v++)
            edge[++cnte].u=i,edge[cnte].v=v;
    bit[1]=1;
    for(int i=2;i<=cnte;i++) bit[i]=bit[i-1]<<1;
    dfs(1);
    for(int i=1;i<=cntState;i++)
    {
        for(int v=1;v<=k;v++)
        {
            f[v]=v;
            for(int e=1;e<=cnte;e++)
                if((ShState[i]&bit[e])&&edge[e].v==v)
                {
                    f[find(v)]=find(f[edge[e].u]);
                    break;
                }
        }
        f[k+1]=k+1;
        FindNext(i,1,k+1);
    }
    Matrix tmp1,tmp2;
    tmp1.n=cntState;
    for(int i=1;i<=cntState;i++)
        for(int v=1;v<=cntState;v++)
            tmp1.Mat[i][v]=Mat[i][v];
    tmp2=tmp1;
    for(int i=1;i<=cntState;i++)
        for(int v=1;v<=cntState;v++) tmp1.Mat[i][v]=0;
    for(int i=1;i<=cntState;i++) tmp1.Mat[i][i]=1;
    long long mi=n-k;
    while(mi&&mi>=0)
    {
        if(mi&1) tmp1=tmp1*tmp2;
        mi>>=1,tmp2=tmp2*tmp2;
    }
    long long ans=0;
//  for(int i=1;i<=cnt;i++) printf("%d\n")
    for(int i=1;i<=cntState;i++)
        (ans+=get(ShState[i])*tmp1.Mat[i][1]%mod)%=mod;
    cout<<ans;
    return 0;
}
