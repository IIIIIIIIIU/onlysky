#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e5+5;

struct node
{
	int c,p;
	
	bool operator<(const node &tmp)const
	{
		return p>tmp.p;
	}
};

struct node c[maxn];

int p[maxn],n,m;

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

bool cmp(int a,int b)
{
	return a>b;
}

int main()
{
	while(scanf("%d%d",&n,&m)&&n&&m)
	{
		for(int i=1;i<=n;i++)
			read(p[i]);
		for(int i=1;i<=m;i++)
		{
			read(c[i].c);
			read(c[i].p);
		}
		std::sort(p+1,p+n+1,cmp);
		std::sort(c+1,c+m+1);
		int ans1=0,ans2=0,now=1;
		for(int i=1;i<=m;i++)
		{
			while(now<=n&&p[now]>c[i].p)
				now++;
			while(now<=n&&p[now]<=c[i].p&&c[i].c)
			{
				ans1++;
				c[i].c--;
				ans2+=p[now];
				now++;
			}
		}
		printf("%d %d\n",ans1,ans2);
	}
	return 0;
}
