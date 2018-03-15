#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e6+5;

int T,n,ai[maxn],bi[maxn],ei[maxn],ci[maxn],f[maxn];

inline void read(int &now)
{
	char Cget;
	now=0;
	while(!isdigit(Cget=getchar()));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}

inline int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}

int main()
{
	read(T);
	while(T--)
	{
		read(n);
		int num=0;
		for(int i=1;i<=n;i++)
		{
			read(ai[i]);
			read(bi[i]);
			read(ei[i]);
			ci[++num]=ai[i];
			ci[++num]=bi[i];
		}
		std::sort(ci+1,ci+num+1);
		num=std::unique(ci+1,ci+num+1)-ci-1;
		for(int i=1;i<=n;i++)
		{
			ai[i]=std::lower_bound(ci+1,ci+num+1,ai[i])-ci;
			bi[i]=std::lower_bound(ci+1,ci+num+1,bi[i])-ci;
		}
		for(int i=1;i<=num;i++)
			f[i]=i;
		num=0;
		int ans=1,x,y;
		for(int i=1;i<=n;i++)
			if(ei[i])
			{
				x=find(ai[i]);
				y=find(bi[i]);
				f[x]=y;
			}
			else
			{
				++num;
				ai[num]=ai[i];
				bi[num]=bi[i];
			}
		for(int i=1;i<=num;i++)
			if(find(ai[i])==find(bi[i]))
			{
				ans=0;
				break;
			}
		if(ans)
			puts("YES");
		else
			puts("NO");
	}
	return 0;
}
