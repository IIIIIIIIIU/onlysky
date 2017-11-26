#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=55;

int n,num[maxn];

char str[maxn];

ll C[maxn][maxn],ans;

ll get(int x)
{
	ll res=1;
	for(int i=0;i<=9;i++)
	{
		res*=C[x][num[i]];
		x-=num[i];
	}
	return res;
}

int main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	for(int i=1;i<=n;i++)
		num[str[i]-'0']++;
	C[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for(int v=1;v<=i;v++)
			C[i][v]=C[i-1][v]+C[i-1][v-1];
	}
	for(int i=1;i<=n;i++)
	{
		for(int v=0;v<str[i]-'0';v++)
			if(num[v])
			{
				--num[v];
				ans+=get(n-i);
				++num[v];
			}
		--num[str[i]-'0'];
	}
	std::cout<<ans;
	return 0;
}
