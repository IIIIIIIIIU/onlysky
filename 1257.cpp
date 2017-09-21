#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k,ans;
int main()
{
    cin>>n>>k;
    if(n>=k) ans+=k*(n-k),n=k-1;
    ans+=n*k;
    for(ll i=1;i<=n;)
    {
        ll p=k/i;
        ll l=i,r=n,mid,res;
        while(l<=r)
        {
            mid=l+r>>1;
            if(k/mid==p) res=mid,l=mid+1;
            else r=mid-1;
        }
        ll len=res-i+1;
        ans-=p*(i*len+len*(len-1)/2);
        i=res+1;
    }
    cout<<ans;
    return 0;
}
