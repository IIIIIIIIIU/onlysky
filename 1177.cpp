#include <bits/stdc++.h>
using namespace std;
const int maxn=1505;
int n,m,k,sum[maxn][maxn],ul[maxn][maxn],ur[maxn][maxn],dl[maxn][maxn],dr[maxn][maxn];
int ans,prer[maxn][maxn],r[maxn][maxn],prec[maxn][maxn],c[maxn][maxn];
inline int get(int prex,int prey,int sufx,int sufy)
{
    return sum[sufx][sufy]-sum[sufx][prey-1]-sum[prex-1][sufy]+sum[prex-1][prey-1];
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            scanf("%d",&sum[i][v]),sum[i][v]+=sum[i-1][v]+sum[i][v-1]-sum[i-1][v-1];
    for(int i=k;i<=n;i++)
        for(int v=k;v<=m;v++)
            dr[i][v]=max(max(dr[i-1][v],dr[i][v-1]),get(i-k+1,v-k+1,i,v));
    for(int i=k;i<=n;i++)
        for(int v=m-k+1;v>=1;v--)
            dl[i][v]=max(max(dl[i-1][v],dl[i][v+1]),get(i-k+1,v,i,v+k-1));
    for(int i=n-k+1;i>=1;i--)
        for(int v=k;v<=m;v++)
            ur[i][v]=max(max(ur[i+1][v],ur[i][v-1]),get(i,v-k+1,i+k-1,v));
    for(int i=n-k+1;i>=1;i--)
        for(int v=m-k+1;v>=1;v--)
            ul[i][v]=max(max(ul[i+1][v],ul[i][v+1]),get(i,v,i+k-1,v+k-1));
    for(int i=k;i<=n;i++)
        for(int v=k;v<=m;v++)
            prec[i][v]=max(prec[i][v-1],get(i-k+1,v-k+1,i,v));
    for(int v=1;v<=n;v++)
    {
        c[v][v]=prec[v][m];
        for(int e=v+k-1;e<=n;e++)
            c[v][e]=max(c[v][e-1],prec[e][m]);
    }
    for(int v=k;v<=m;v++)
        for(int i=k;i<=n;i++)
            prer[i][v]=max(prer[i-1][v],get(i-k+1,v-k+1,i,v));
    for(int i=1;i<=m;i++)
    {
        r[i][i]=prer[n][i];
        for(int e=i+k-1;e<=m;e++)
            r[i][e]=max(r[i][e-1],prer[n][e]);
    }
    for(int i=k;i<=n-2*k;i++)
        for(int v=i+k;v<=n-k;v++)
            ans=max(ans,c[1][i]+c[i+1][v]+c[v+1][n]);
    for(int i=k;i<=m-2*k;i++)
        for(int v=i+k;v<=m-k;v++)
            ans=max(ans,r[1][i]+r[i+1][v]+r[v+1][m]);
    for(int i=k;i<=n-k;i++)
        for(int v=k;v<=m-k;v++)
        {
            ans=max(ans,dr[i][m]+ur[i+1][v]+ul[i+1][v+1]);
            ans=max(ans,ur[i+1][m]+dr[i][v]+dl[i][v+1]);
            ans=max(ans,dr[n][v]+dl[i][v+1]+ul[i+1][v+1]);
            ans=max(ans,dl[n][v+1]+dr[i][v]+ur[i+1][v]);
        }
    cout<<ans;
    return 0;
}
