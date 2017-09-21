#include <bits/stdc++.h>
using namespace std;
const int bin[5]={1,2,4,8,16};
int n,m,a[50005],f[10005][32],g[10005][32];
bool ok[50005][32];
int read()
{
    int x=0;char Cget=getchar();
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        x=x*10+Cget-'0';
        Cget=getchar();
    }
    return x;
}
int main()
{
    n=read(),m=read();
    int i,v,k,x,y;
    for(i=1;i<=m;i++)
    {
        a[i]=read();
        v=read(),k=read(),x=y=0;
        while(v--) x|=bin[(read()+n-a[i])%n];
        while(k--) y|=bin[(read()+n-a[i])%n];
        for(v=0;v<32;v++)
            if((v&x)||((31^v)&y))
                ok[i][v]=true,g[a[i]][v]++;
    }
    int ans=0;
    for(int i=0;i<16;i++)
    {
        memset(f[0],200,sizeof(f[0]));
        f[0][i<<1]=0;
        for(v=1;v<=n;v++)
            for(k=0;k<32;k++)
            {
                f[v][k]=max(f[v-1][(k&15)<<1],
                f[v-1][(k&15)<<1|1])+g[v][k];
            }
        ans=max(ans,max(f[n][i<<1],f[n][i<<1|1]));
    }
    printf("%d\n",ans);
    return 0;
}
