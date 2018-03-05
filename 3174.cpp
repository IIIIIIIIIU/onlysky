#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e3+5;

struct node
{
	int a,b;
	
	bool operator<(const node &tmp)const
	{
		return a+b<tmp.b+tmp.a;
	}
};

struct node ai[maxn];

int n,h,f[maxn],ans;

int main()
{
	scanf("%d",&n);
	memset(f,-1,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&ai[i].a,&ai[i].b);
		f[0]+=ai[i].a;
	}
	scanf("%d",&h);
	std::sort(ai+1,ai+n+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=ans;j>=0;j--)
			if(f[j]+ai[i].b>=h)
				f[j+1]=std::max(f[j+1],f[j]-ai[i].a);
		if(f[ans+1]>=0)
			ans++;
	}
	std::cout<<ans<<std::endl;
	return 0;
}
