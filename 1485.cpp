#include <bits/stdc++.h>
using namespace std;
const int maxn=3000005;
int n,p,pi[maxn],cnt,ans1[maxn],ans2[maxn];
bool vis[maxn];
int main()
{
    scanf("%d%d",&n,&p);
    for(int i=2;i<=n*3;i++)
    {
        if(!vis[i]) pi[++cnt]=i;
        for(int v=1;v<=cnt;v++)
        {
            if(pi[v]*i>n*3) break;
            vis[pi[v]*i]=true;
            if(i%pi[v]==0) break;
        }
    }
    for(int i=1;pi[i]<=n*2;i++)
    {
        int t=n*2;
        while(t)
        {
            ans1[i]+=t/pi[i];
            t/=pi[i];
        }
    }
    for(int i=1;pi[i]<=n;i++)
    {
        int t=n;
        while(t)
        {
            ans2[i]+=(t/pi[i])*2;
            t/=pi[i];
        }
    }
    int t=n+1;
    for(int i=1;i<=cnt&&t>=pi[i];i++)
        while(t%pi[i]==0&&t>1) ans2[i]++,t/=pi[i];
    long long out=1;
    for(int i=1;i<=cnt;i++)
    {
        ans1[i]-=ans2[i];
        while(ans1[i]>0) (out*=pi[i])%=p,ans1[i]--;
    }
    cout<<out;
    return 0;
}
