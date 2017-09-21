#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[1005],s[2],f[1005],n,ans,flag;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=3;i<=n;i++)
        if(a[i]+a[i-1]==2) flag=1;
    if(!flag)
    {
        for(int i=2;i<=n;i+=2) s[a[i]]++;
        printf("%lld\n%lld",s[0],s[1]);
        return 0;
    }
    for(int i=1;i<=n;i++) f[i]=(a[i]==1)?1:1e15;
    for(int i=1;i<=n;i++)
        if(i>2&&a[i]&&a[i-1])
        {
            for(int v=i-2;v>=1;v--) f[v]=min(f[v],f[v+1]+f[v+2]);
            for(int v=i+1;v<=n;v++) f[v]=min(f[v],f[v-1]+f[v-2]);
        }
    for(int i=2;i<n;i+=2) ans+=f[i];
    printf("0\n%lld",ans);
    return 0;
}
