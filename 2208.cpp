#include <bits/stdc++.h>

const int maxn=2005;

int n;

char str[maxn];

std::bitset<maxn>f[maxn];

int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++)
	{
		std::cin>>str+1;
		for(int v=1;v<=n;v++)
			f[i][v]=str[v]-'0';
		f[i][i]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			if(f[i][k]) f[i]|=f[k];
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=f[i].count();
	std::cout<<ans;
	return 0;
}
