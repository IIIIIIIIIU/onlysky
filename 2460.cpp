#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

struct data
{
	int b;
	
	ll a;
	
	bool operator<(const data &tmp)const
	{
		return b>tmp.b;
	}
};

struct data a[1005];

ll bin[65];

int b[65],n,ans;

inline void read(ll &now)
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
	bin[0]=1;
	for(int i=1;i<=63;i++)
		bin[i]=bin[i-1]<<1;
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(a[i].a);
		read(a[i].b);
	}
	std::sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=63;j>=0;j--)
			if(a[i].a&bin[j])
			{
				if(!b[j])
				{
					b[j]=i;
					break;
				}
				else
					a[i].a^=a[b[j]].a;
			}
		if(a[i].a)
			ans+=a[i].b;
	}
	printf("%d\n",ans);
	return 0;
}
