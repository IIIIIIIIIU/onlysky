#include <bits/stdc++.h>
using namespace std;
int ai[2005][2005],n,m,f[2005][2005],ans1,ans2;
int up[2005][2005],l[2005][2005],r[2005][2005];
inline void in(int &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
int main()
{
    in(n),in(m);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
        {
            in(ai[i][v]);
            if((i+v)%2) ai[i][v]^=1;
            f[i][v]=1;
            if(ai[i-1][v-1]==ai[i][v]&&ai[i-1][v]==ai[i][v]&&ai[i][v-1]==ai[i][v])
                f[i][v]+=min(f[i-1][v-1],min(f[i-1][v],f[i][v-1]));
            ans1=max(ans1,f[i][v]);
        }
    printf("%d\n",ans1*ans1);
    for(int i=1;i<=n;i++)
    {
        for(int v=1;v<=m;v++)
        {
            l[i][v]=1;
            if(v!=1&&ai[i][v]==ai[i][v-1]) l[i][v]+=l[i][v-1];
        }
        for(int v=m;v>=1;v--)
        {
            r[i][v]=1;
            if(v!=m&&ai[i][v]==ai[i][v+1]) r[i][v]+=r[i][v+1];
        }
    }
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
        {
            up[i][v]=1;
            if(i!=1&&ai[i][v]==ai[i-1][v])
            {
                up[i][v]+=up[i-1][v];
                l[i][v]=min(l[i][v],l[i-1][v]);
                r[i][v]=min(r[i][v],r[i-1][v]);
            }
            ans2=max(up[i][v]*(l[i][v]+r[i][v]-1),ans2);
        }
    printf("%d\n",ans2);
    return 0;
}
