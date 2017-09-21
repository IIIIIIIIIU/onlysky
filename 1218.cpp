#include <bits/stdc++.h>
using namespace std;
int ans,sum[5005][5005],n,r;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(r);int x,y,k;
    for(int i=1;i<=n;i++)
    {
        in(x),in(y),in(k);
        sum[++x][++y]+=k;
    }
    for(int i=1;i<=5001;i++)
        for(int v=1;v<=5001;v++)
            sum[i][v]+=sum[i-1][v]+sum[i][v-1]-sum[i-1][v-1];
    for(int i=r;i<=5001;i++)
        for(int v=r;v<=5001;v++)
            ans=max(ans,sum[i][v]-sum[i-r][v]-sum[i][v-r]+sum[i-r][v-r]);
    cout<<ans;
    return 0;
}
