#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
set<ll>s;
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i*i<=n;i++)
    {
        ll a=i,b=n/i;
        if(n%i==0)
        for(ll v=b;v<=n;v+=b)
        {
            if((v-2)%a==0&&(((v-2)*v))%n==0) s.insert(v-1);
            if((v+2)%a==0&&((v+2)*v)%n==0&&(v+1)<n) s.insert(v+1);
        }
    }
    s.insert(1);
    for(set<ll>::iterator it=s.begin();it!=s.end();it++) printf("%lld\n",*it);
    return 0;
}
