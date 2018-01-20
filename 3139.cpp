#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned long long ll;
const int mod=1e9+7;
int n,ai[15],ci[15];
std::map<ll,int>Map[15],vis[15];
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
inline ll hash()
{
	for(int i=1;i<=n;i++)
		ci[i]=ai[i];
	std::sort(ci+1,ci+n+1);
	ll res=0;
	for(int i=1;i<=n;i++)
		res=res*53+ci[i];
	return res;
}
inline void add(int &x,int b)
{
	if((x+=b)>=mod)
		x-=mod;
}
int dfs(int x,int y)
{
	if(x==n)
	{
		if(ai[x])
			return 0;
		return 1;
	}
	ll tmp;
	int res=0;
	if(y==x+1)
	{
		tmp=hash();
		if((vis[x][tmp]+=1)!=1)
			return Map[x][tmp];
	}
	if(ai[x]>=3)
	{
		ai[x]-=3;
		if(y==n)
		{
			if(!ai[x])
				add(res,dfs(x+1,x+2));
		}
		else
			add(res,dfs(x,y+1));
		ai[x]+=3;
	}
	if(ai[y]>=3)
	{
		ai[y]-=3;
		if(y==n)
		{
			if(!ai[x])
				add(res,dfs(x+1,x+2));
		}
		else
			add(res,dfs(x,y+1));
		ai[y]+=3;
	}
	if(ai[x]&&ai[y])
	{
		--ai[x];
		--ai[y];
		if(y==n)
		{
			if(!ai[x])
				add(res,dfs(x+1,x+2));
		}
		else
			add(res,dfs(x,y+1));
		++ai[x];
		++ai[y];
	}
	if(y==x+1)
		Map[x][tmp]=res;
	return res;
}
int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(ai[i]);
	std::sort(ai+1,ai+n+1);
	printf("%d\n",dfs(1,2));
	return 0;
}
