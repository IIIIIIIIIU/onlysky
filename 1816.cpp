#include <bits/stdc++.h>
using namespace std;
int n,m,ci[101];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&ci[i]);
    int l=0,r=1000000000,mid,ans=0;
    while(l<=r)
    {
        mid=l+r>>1;
        int tmp=0;
        for(int i=1;i<=n;i++)
        {
            if(ci[i]<mid) tmp+=mid-ci[i];
            if(tmp>mid||tmp>m)
            {
                r=mid-1;
                tmp=-1;
                break;
            }
        }
        if(tmp==-1) continue;
        if(tmp<=mid&&tmp<=m) l=mid+1,ans=mid;
        else r=mid-1;
    }
    cout<<ans;
    return 0;
}
