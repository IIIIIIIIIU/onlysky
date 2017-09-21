#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n,ans,prime[50001],num_prime=0,m;
bool if_prime[50001];
void euler(int limit)
{
    for(int i=2;i<=limit;i++)
    {
        if(!if_prime[i]) prime[++num_prime]=i;
        for(int j=1;prime[j]*i<=limit&&j<=num_prime;j++)
        {
            if_prime[i*prime[j]]=true;
            if(i%prime[j]==0) break;
        }
    }
}
int main()
{
    scanf("%d",&n),euler(n);
    int now,dis;double pos,tmp;
    for(int i=1;i<n;i++)
    {
        pos=i,now=i;
        for(int v=1;prime[v]<=now&&v<=num_prime;v++)
        {
            if(now%prime[v]==0)
            {
                tmp=prime[v],pos=pos/tmp*(tmp-1);
                while(now%prime[v]==0) now/=prime[v];
            }
        }
        ans+=pos;
    }
    cout<<ans*2+1;
    return 0;
}
