#include <cstdio>
using namespace std;
#define ll long long
#define maxn 1000005
#define mod 1000000007
int n,m;
ll f[maxn],val[maxn];
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
ll poww(ll x)
{
    int mi=mod-2;ll res=1;
    while(mi)
    {
        if(mi&1) res=(res*x)%mod;
        mi>>=1,x=(x*x)%mod;
    }
    return res;
}
int main()
{
    int T;in(T);
    val[0]=1,f[0]=1,f[1]=0,f[2]=1;
    for(int i=1;i<maxn;i++) val[i]=(val[i-1]*i)%mod;
    for(int i=3;i<maxn;i++) f[i]=(i-1)*(f[i-1]+f[i-2])%mod;
    while(T--)
    {
        in(n),in(m);
        printf("%lld\n",(val[n]*f[n-m]%mod)*poww(val[m]*val[n-m]%mod)%mod);
    }
    return 0;
}
