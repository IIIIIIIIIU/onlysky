#include <bits/stdc++.h>
using namespace std;
#define f(wx,wy,wz) dp[wx][wy][wz+8]
const int maxn=1005;
int dp[maxn][1<<8][17],ti[maxn],bi[maxn],n,INF;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    int T;in(T);
    while(T--)
    {
        in(n);
        for(int i=1;i<=n;i++) in(ti[i]),in(bi[i]);
        memset(dp,127/7,sizeof(dp)),INF=dp[0][0][0];
        f(1,0,-1)=0;
        for(int i=1;i<=n;i++)
            for(int v=0;v<(1<<8);v++)
                for(int k=-8;k<=7;k++)
                    if(f(i,v,k)<INF)
                        if(v&1) f(i+1,v>>1,k-1)=min(f(i+1,v>>1,k-1),f(i,v,k));
                        else
                        {
                            int lim=INF;
                            for(int e=0;e<=7;e++)
                            {
                                if(!(v&(1<<e)))
                                {
                                    if(i+e>lim) break;
                                    lim=min(lim,i+e+bi[i+e]);
                                    f(i,v+(1<<e),e)=min(f(i,v+(1<<e),e),f(i,v,k)+((i+k==0)?0:(ti[i+k]^ti[i+e])));
                                }
                            }
                        }
        int ans=INF;
        for(int i=-8;i<=7;i++) ans=min(ans,f(n+1,0,i));
        cout<<ans<<endl;
    }
    return 0;
}
