#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1005;

int n,k,vi[maxn];

std::map<int,int>Map;

inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

int main()
{
	read(n);
	read(k);
	for(int i=1;i<=n;i++)
	{
		read(vi[i]);
		for(int v=1,e;v*v<=vi[i];v++)
			if(vi[i]%v==0)
			{
				e=vi[i]/v;
				Map[v]++;
				if(e!=v)
					Map[e]++;
			}
	}
	int ans=0;
	for(std::map<int,int>::iterator it=Map.begin();it!=Map.end();++it)
		if(it->second>=k)
			ans=it->first;
	std::cout<<ans;
	return 0;
}
