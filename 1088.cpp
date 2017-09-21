#include <bits/stdc++.h>
using namespace std;
int ai[10005],ans,n,p[10005];
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
void dfs(int now)
{
    if(now==n+1)
    {
        if(p[now-1]+p[now-2]==ai[now-1]) ++ans;
        return;
    }
    int tmp=0;
    if(now-2>=1) tmp+=p[now-2];
    if(now-1>=1) tmp+=p[now-1];
    if(now!=1)
    {
        if(tmp+1==ai[now-1]) p[now]=1,dfs(now+1);
        if(tmp==ai[now-1]) p[now]=0,dfs(now+1);
    }
    else
    {
        if(ai[1]==2) p[now]=1,dfs(now+1);
        if(ai[1]==0) p[now]=0,dfs(now+1);
        if(ai[1]==1) p[now]=1,dfs(now+1),p[now]=0,dfs(now+1);
    }
}
int main()
{
    in(n);
    for(int i=1;i<=n;i++) in(ai[i]);
    if(ai[1]==3||ai[n]==3)
    {
        cout<<0;
        return 0;
    }
    dfs(1);
    cout<<ans;
    return 0;
}
