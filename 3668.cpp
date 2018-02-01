#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e5+5;
int n,val[31][2],m,ans;
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
int main()
{
	read(n);
	read(m);
	char op[12];
	for(int i=0;i<=30;i++)
		val[i][1]=1;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%s",op);
		read(x);
		for(int v=0,tmp;v<=30;v++)
		{
			tmp=(x&(1<<v));
			if(tmp)
				tmp=1;
			if(op[0]=='A')
			{
				val[v][0]&=tmp;
				val[v][1]&=tmp;
			}
			else if(op[0]=='X')
			{
				val[v][0]^=tmp;
				val[v][1]^=tmp;
			}
			else
			{
				val[v][0]|=tmp;
				val[v][1]|=tmp;
			}
		}
	}
	for(int i=0;i<=30;i++)
	{
		val[i][0]*=(1<<i);
		val[i][1]*=(1<<i);
	}
	bool did=true;
	for(int i=30;i>=0;i--)
		if(did)
		{
			if(m&(1<<i))
			{
				if(val[i][0])
				{
					ans+=val[i][0];
					did=false;
				}
				else if(val[i][1])
					ans+=val[i][1];
				else
					did=false;
			}
			else
				ans+=val[i][0];
		}
		else
			ans+=std::max(val[i][0],val[i][1]);
	std::cout<<ans;
	return 0;
}
