#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1000005;
ll ai[maxn],n,bi[maxn],ans,sum;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&ai[i]),sum+=ai[i];
    sum/=n;
    for(int i=1;i<=n;i++) bi[i]=ai[i]-sum+bi[i-1];
    sort(bi+1,bi+n+1);
    int mid=bi[(n>>1)+1];
    for(int i=1;i<=n;i++) ans+=abs(bi[i]-mid);
    printf("%lld\n",ans);
    return 0;
}
