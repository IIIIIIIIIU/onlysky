#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
#define maxn 150005
#define ll long long
 
struct BuildingType {
    ll lit,time;
};
struct BuildingType ai[maxn];
 
ll n,sum,ans;
 
inline void in(ll &now)
{
    char Cget=getchar();now=0;
    while(Cget>'9'||Cget<'0') Cget=getchar();
    while(Cget>='0'&&Cget<='9')
    {
        now=now*10+Cget-'0';
        Cget=getchar();
    }
}
 
bool cmp(BuildingType aa,BuildingType bb)
{
    if(aa.lit==bb.lit) return aa.time<bb.time;
    else return aa.lit<bb.lit;
}
 
priority_queue<ll>que;
 
int main()
{
    in(n);
    for(ll i=1;i<=n;i++) in(ai[i].time),in(ai[i].lit);
    sort(ai+1,ai+n+1,cmp);
    for(ll i=1;i<=n;i++)
    {
        if(sum+ai[i].time<=ai[i].lit) que.push(ai[i].time),sum+=ai[i].time,ans++;
        else
        {
            if(que.empty()) continue;
            if(ai[i].time<que.top()) sum-=que.top(),que.pop(),que.push(ai[i].time),sum+=ai[i].time;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
