#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef double real;
const real eps=1e-10;
int n,m,x,y,ans=0;
real cmp,sum[1005];
void dfs(int now,int pos,real tmp)
{
    if(tmp>cmp+eps) return;
    if(tmp+sum[m]-sum[m-n+now-1]>cmp+eps) return;
    if(tmp-sum[pos-1]+sum[pos+n-now]<cmp-eps) return;
    if(now==n+1)
    {
        if(tmp>cmp-eps&&tmp<cmp+eps) ans++;
        return;
    }
    if(pos>m) return;
    dfs(now,pos+1,tmp);
    dfs(now+1,pos+1,tmp+1.0/pos);
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&x,&y),cmp=(real)x/y;
    for(int i=1;i<=m;i++) sum[i]=sum[i-1]+1.0/i;
    dfs(1,1,0);cout<<ans;
    return 0;
}
