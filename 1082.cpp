#include <bits/stdc++.h>
using namespace std;
int n,m,ci[1005],ki[1005],lit,sum[1005],tot,rest;
bool flag;
inline void in(int &now)
{
    char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
    while(Cget>='0'&&Cget<='9') now=now*10+Cget-'0',Cget=getchar();
}
bool dfs(int now,int p)
{
    int tmp,op;
    if(rest>tot) return false;
    for(int i=p;i<=m;i++)
        if(ci[now]<=ki[i])
        {
            if(now==1) return true;
            ki[i]-=ci[now];
            if(ci[now-1]==ci[now])
            {
                if(dfs(now-1,i))
                {
                    ki[i]+=ci[now];
                    return true;
                }
            }
            else if(dfs(now-1,1))
            {
                ki[i]+=ci[now];
                return true;
            }
            ki[i]+=ci[now];
        }
    return false;
}
int main()
{
    in(m);
    for(int i=1;i<=m;i++) in(ki[i]),tot+=ki[i];
    in(n);
    for(int i=1;i<=n;i++) in(ci[i]);
    sort(ki+1,ki+m+1),sort(ci+1,ci+n+1);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+ci[i];
    int l=0,r=n,mid,ans=0;
    while(l<=r)
    {
        mid=l+r>>1,lit=mid,rest=sum[mid];
        if(dfs(lit,1)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
