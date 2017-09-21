#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
typedef long long ll;
ll dis[105][105],num[105][105],n,m;
real ans[105];
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(m);ll u,v,w;
    memset(dis,127/3,sizeof(dis));
    for(ll i=1;i<=m;i++)
    {
        in(u),in(v),in(w);
        dis[u][v]=dis[v][u]=w;
        num[u][v]=num[v][u]=1;
    }
    for(ll k=1;k<=n;k++)
        for(ll i=1;i<=n;i++)
            for(ll v=1;v<=n;v++)
            {
                if(i==k) continue;
                if(i==v) continue;
                if(v==k) continue;
                if(dis[i][v]>dis[i][k]+dis[k][v])
                {
                    dis[i][v]=dis[i][k]+dis[k][v];
                    num[i][v]=num[i][k]*num[k][v];
                }
                else if(dis[i][v]==dis[i][k]+dis[k][v])
                    num[i][v]+=num[i][k]*num[k][v];
            }
    for(ll s=1;s<=n;s++)
        for(ll t=1;t<=n;t++)
            if(s!=t)
                for(ll v=1;v<=n;v++)
                {
                    if(s==v||t==v) continue;
                    if(dis[s][v]+dis[v][t]==dis[s][t])
                        ans[v]+=((real)num[s][v]*num[v][t])/num[s][t];
                }
    for(ll i=1;i<=n;i++) printf("%.3lf\n",ans[i]);
    return 0;
}
