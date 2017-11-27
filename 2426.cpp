#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=5e4+5;
const int INF=0x3f3f3f3f;

struct node
{
	int a,c;
	
	bool operator<(const node &tmp)const
	{
		return c<tmp.c;
	}
};

struct node bi[maxn];

int n,m,b,h,hi[maxn],c0[maxn],ci[maxn],ai[maxn],ans=INF;

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

int solve(int id)
{
	int res=0;
	for(int i=1;i<=m;i++)
	{
		read(ci[i]);
		res+=ai[i]*ci[i];
		bi[i].a=ai[i];
		bi[i].c=c0[i]-ci[i];
	}
	std::sort(bi+1,bi+m+1);
	int tmp=b;
	for(int i=1;i<=m;i++)
	{
		if(bi[i].a>=tmp)
		{
			res+=tmp*bi[i].c;
			break;
		}
		tmp-=bi[i].a;
		res+=bi[i].a*bi[i].c;
	}
	return res;
}

int main()
{
	read(m);
	read(b);
	read(h);
	read(n);
	for(int i=1;i<=m;i++)
		read(ai[i]);
	for(int i=1;i<=n;i++)
		read(hi[i]);
	for(int i=1;i<=m;i++)
		read(c0[i]);
	int id=0;
	for(int i=1,tmp;i<=n;i++)
	{
		tmp=solve(i)+h+hi[i];
		if(tmp<ans)
		{
			ans=tmp;
			id=i;
		}
	}
	std::cout<<id<<std::endl<<ans;
	return 0;
}
