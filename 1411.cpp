#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=100005;
ll ai[2][maxn],n,t,out[maxn<<1];
inline void in(ll &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(n),in(t);ll tot=0;
    for(ll i=1;i<=n;i++) in(ai[0][i]),ai[0][i]--;
    for(ll v=2;v<=t;v<<=1)
    {
        if(!(t&v)) continue;
        tot^=1;
        for(ll i=1;i<=n;i++)
        {
            ll l=(i-(v>>1)%n+n-1)%n+1;
            ll r=(i+(v>>1)%n+n-1)%n+1;
            ai[tot][i]=ai[tot^1][l]^ai[tot^1][r];
        }
    }
    for(ll i=1;i<=n;i++) out[i+i-1]=ai[tot][i];
    if(t&1)
    {
        for(ll i=1;i<=n;i++) out[i+i]=out[i+i-1]^out[(i+i+1>n*2)?1:(i+i+1)];
        for(ll i=1;i<=n;i++) out[i+i-1]=-1;
    }
    else for(ll i=1;i<=n;i++) out[i+i]=-1;
    printf("%d",out[1]+1);
    for(ll i=2;i<=(n<<1);i++) printf(" %d",out[i]+1);
    printf("\n");
    return 0;
}
