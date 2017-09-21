#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
const ll mod=(1LL<<32);
ll ai[3005][3005],sum1[3005][3005],sum2[3005][3005];
int n,m,q,xi[3000005],yi[3000005],ki[3000005];
unsigned int A,B,C;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
inline unsigned int rng61()
{
    A^=A<<16;
    A^=A>>5;
    A^=A<<1;
    unsigned int t=A;
    A=B;
    B=C;
    C^=t^A;
    return C;
}
int main()
{
    in(n),in(m),in(q);scanf("%u%u%u",&A,&B,&C);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++) ai[i][v]=rng61();
    for(int i=1;i<=n;i++)
        for(int v=m;v>=1;v--)
            sum1[i][v]=ai[i][v]+sum1[i-1][v+1]+sum1[i][v+1]-sum1[i-1][v+2];
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            sum2[i][v]=ai[i][v]+sum2[i-1][v]+sum2[i][v-1]-sum2[i-1][v-1];
    int x,y,k;
    ll ans,res=0;
    for(int i=1;i<=q;i++)
    {
        xi[i]=rng61()%n+1;
        yi[i]=rng61()%m+1;
        ki[i]=rng61()%min(xi[i],yi[i])+1;
    }
    ll pos=1;
    for(int i=q;i>=1;i--)
    {
        x=xi[i],y=yi[i],k=ki[i];
        ans=sum1[x][y-k+1]-sum1[x-k][y+1]-(sum2[x][m]-sum2[x][y]-sum2[x-k][m]+sum2[x-k][y]);
        ans%=mod;
        (res+=pos*ans%mod)%=mod,pos*=233,pos%=mod;
    }
    cout<<res;
    return 0;
}
