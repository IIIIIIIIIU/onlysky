#include <bits/stdc++.h>
using namespace std;
const int maxn=2005;
int ap[maxn],bp[maxn],as[maxn],bs[maxn],dp[maxn][maxn],q[maxn];
int t,maxp,w,head,tail;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
int main()
{
    in(t),in(maxp),in(w);
    for(int i=1;i<=t;i++)
        in(ap[i]),in(bp[i]),in(as[i]),in(bs[i]);
    memset(dp,-127/3,sizeof(dp));
    for(int i=0;i<=t;i++) dp[i][0]=0;
    for(int i=1;i<=t;i++)
    {
        for(int v=0;v<=as[i];v++)
            dp[i][v]=-ap[i]*v;
        for(int v=maxp;v>=0;v--)
            dp[i][v]=max(dp[i][v],dp[i-1][v]);
        if(i-w-1>=0)
        {
            head=1,tail=0;
            for(int v=0;v<=maxp;v++)
            {
                while(head<=tail&&q[head]<v-as[i])
                    head++;
                while(head<=tail&&dp[i-w-1][v]+ap[i]*v>=dp[i-w-1][q[tail]]+ap[i]*q[tail])
                    tail--;
                q[++tail]=v;
                if(head<=tail)
                    dp[i][v]=max(dp[i][v],dp[i-w-1][q[head]]-ap[i]*(v-q[head]));
            }
            head=1,tail=0;
            for(int v=maxp;v>=0;v--)
            {
                while(head<=tail&&q[head]>v+bs[i])
                    head++;
                while(head<=tail&&dp[i-w-1][v]+bp[i]*v>=dp[i-w-1][q[tail]]+bp[i]*q[tail])
                    tail--;
                q[++tail]=v;
                if(head<=tail)
                    dp[i][v]=max(dp[i][v],dp[i-w-1][q[head]]+bp[i]*(q[head]-v));
            }
        }
    }
    int ans=0;
    for(int i=0;i<=maxp;i++)
        ans=max(ans,dp[t][i]);
    cout<<ans;
    return 0;
}
