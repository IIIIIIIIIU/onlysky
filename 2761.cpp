#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=5e4+5;
int n;
ll ans[maxn];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,num=0;
		ll x;
		std::map<ll,int>Map;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%lld",&x);
			if((Map[x]+=1)==1)
				ans[++num]=x;
		}
		printf("%lld",ans[1]);
		for(int i=2;i<=num;i++)
			printf(" %lld",ans[i]);
		if(T)
			puts("");
	}
	return 0;
}
