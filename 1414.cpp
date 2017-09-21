#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef unsigned int ull;
const int maxn=2005;
const ull hpos1=1000000007,hpos2=1000000013;
int n,m,ai[maxn][maxn],ans;
ull Hash1[maxn][maxn],Hash2[maxn][maxn],Hash3[maxn][maxn];
ull pw1[maxn],pw2[maxn];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
ull get1(int x,int y,int len)
{
    return Hash1[x+len-1][y+len-1]-Hash1[x-len][y+len-1]*pw1[len+len-1]
        -Hash1[x+len-1][y-len]*pw2[len+len-1]+Hash1[x-len][y-len]*pw1[len+len-1]*pw2[len+len-1];
}
ull get2(int x,int y,int len)
{
    return Hash2[x+len-1][y-len+1]-Hash2[x+len-1][y+len]*pw2[len+len-1]
        -Hash2[x-len][y-len+1]*pw1[len+len-1]+Hash2[x-len][y+len]*pw1[len+len-1]*pw2[len+len-1];
}
ull get3(int x,int y,int len)
{
    return Hash3[x-len+1][y+len-1]-Hash3[x+len][y+len-1]*pw1[len+len-1]
        -Hash3[x-len+1][y-len]*pw2[len+len-1]+Hash3[x+len][y-len]*pw1[len+len-1]*pw2[len+len-1];
}
int solveit(int x,int y)
{
    int l=1,r=min(min(x,n-x+1),min(y,m-y+1)),mid,res=1;
    ull tmp1,tmp2,tmp3;
    while(l<=r)
    {
        mid=l+r>>1;
        tmp1=get1(x,y,mid),tmp2=get2(x,y,mid),tmp3=get3(x,y,mid);
        if(tmp1==tmp2&&tmp3==tmp1) res=mid,l=mid+1;
        else r=mid-1;
    }
    return res>>1;
}
int main()
{
    in(n),in(m),n=n<<1|1,m=m<<1|1,pw1[0]=pw2[0]=1;
    for(int i=2;i<=n;i+=2)
        for(int v=2;v<=m;v+=2) in(ai[i][v]);
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++) ai[i][v]++;
    for(int i=1;i<maxn;i++) pw1[i]=pw1[i-1]*hpos1;
    for(int i=1;i<maxn;i++) pw2[i]=pw2[i-1]*hpos2;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            Hash1[i][v]=Hash1[i-1][v]*hpos1+Hash1[i][v-1]*hpos2-Hash1[i-1][v-1]*hpos1*hpos2+ai[i][v];
    for(int i=1;i<=n;i++)
        for(int v=m;v>=1;v--)
            Hash2[i][v]=Hash2[i-1][v]*hpos1+Hash2[i][v+1]*hpos2-Hash2[i-1][v+1]*hpos1*hpos2+ai[i][v];
    for(int i=n;i>=1;i--)
        for(int v=1;v<=m;v++)
            Hash3[i][v]=Hash3[i+1][v]*hpos1+Hash3[i][v-1]*hpos2-Hash3[i+1][v-1]*hpos1*hpos2+ai[i][v];
    for(int i=1;i<=n;i++)
        for(int v=1;v<=m;v++)
            if((i^v^1)&1) ans+=solveit(i,v);
    cout<<ans;
    return 0;
}
