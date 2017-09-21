#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll u[7],v[7],n,f[4][40],g[4][40];
int main()
{
    scanf("%lld",&n);char op[4];
    for(ll i=1;i<=6;i++)
    {
        scanf("%s",op);
        u[i]=op[0]-'A'+1;
        v[i]=op[1]-'A'+1;
    }
    f[1][1]=f[2][1]=f[3][1]=1;
    for(ll i=1;i<=3;i++)
    {
        for(ll e=1;e<=6;e++)
            if(u[e]==i)
            {
                g[i][1]=v[e];
                break;
            }
    }
    for(ll e=2;e<=n;e++)
    {
        for(ll i=1;i<=3;i++)
        {
            ll y=g[i][e-1],z=1+2+3-y-i;
            if(g[y][e-1]==z) f[i][e]=f[i][e-1]+1+f[y][e-1],g[i][e]=z;
            else f[i][e]=f[i][e-1]*2+2+f[y][e-1],g[i][e]=y;
        }
    }
    cout<<f[1][n];
    return 0;
}
