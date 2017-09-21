#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
int ai[maxn],bi[maxn],ci[maxn],ans1,ans2,n;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&ai[i]);
    for(int i=1;i<=n;i++) scanf("%d",&bi[i]);
    sort(ai+1,ai+n+1),sort(bi+1,bi+n+1);
    int h1=1,h2=1,t1=n,t2=n;
    for(int i=1;i<=n;i++)
    {
        if(ai[h1]>bi[h2]) h1++,h2++,ans1+=2;
        else if(ai[h1]<bi[h2]) h1++,t2--;
        else if(ai[t1]>bi[t2]) t1--,t2--,ans1+=2;
        else
        {
            if(ai[h1]==bi[t2]) ans1++;
            h1++,t2--;
        }
    }
    h1=h2=1,t1=t2=n;
    for(int i=1;i<=n;i++)
    {
        if(bi[h1]>ai[h2]) h1++,h2++;
        else if(bi[h1]<ai[h2]) h1++,t2--,ans2+=2;
        else if(bi[t1]>ai[t2]) t1--,t2--;
        else
        {
            if(bi[h1]==ai[t2]) ans2++;
            else ans2+=2;
            h1++,t2--;
        }
    }
    cout<<ans1<<' '<<ans2;
    return 0;
}
