#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull hpos1=10000000007LL,hpos2=10000000009LL;
int n;
ull Hash1[55][55],Hash2[55][55],pow1[55],pow2[55];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
ull get1(int x,int y,int len)
{
    return Hash1[x][y]-Hash1[x-len][y]*pow1[len]
        -Hash1[x][y-len]*pow2[len]+Hash1[x-len][y-len]*pow1[len]*pow2[len];
}
ull get2(int x,int y,int len)
{
    return Hash2[x][y]-Hash2[x-len][y]*pow1[len]
        -Hash2[x][y-len]*pow2[len]+Hash2[x-len][y-len]*pow1[len]*pow2[len];
}
bool check(int len)
{
    for(int i1=len;i1<=n;i1++)
        for(int v1=len;v1<=n;v1++)
            for(int i2=len;i2<=n;i2++)
                for(int v2=len;v2<=n;v2++)
                    if(get1(i1,v1,len)==get2(i2,v2,len)) return true;
//              {
//                  cout<<get1(i1,v1,len)<<' '<<get2(i2,v2,len)<<endl;
//              }
    return false;
}
int main()
{
    in(n);int tmp=0;
    pow1[0]=1,pow2[0]=1;
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
        {
            in(tmp),Hash1[i][v]=tmp;
            Hash1[i][v]+=Hash1[i-1][v]*hpos1+Hash1[i][v-1]*hpos2-Hash1[i-1][v-1]*hpos1*hpos2;
        }
    for(int i=1;i<=n;i++)
        for(int v=1;v<=n;v++)
        {
            in(tmp),Hash2[i][v]=tmp;
            Hash2[i][v]+=Hash2[i-1][v]*hpos1+Hash2[i][v-1]*hpos2-Hash2[i-1][v-1]*hpos1*hpos2;
        }
    for(int i=1;i<=n;i++) pow1[i]=pow1[i-1]*hpos1,pow2[i]=pow2[i-1]*hpos2;
    int l=1,r=n,mid,ans=0;
    while(l<=r)
    {
        mid=l+r>>1;
        if(check(mid)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
