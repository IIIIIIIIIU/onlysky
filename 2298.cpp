#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e6+5;

struct node
{
	int a,b;
	
	bool operator<(const node &tmp)const
	{
		if(a==tmp.a)
			return b<tmp.b;
		return a<tmp.a;
	}
};

struct node ai[maxn],bi[maxn];

int n,val[maxn],cnt,ci[maxn],ans=0;

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

int get(int l,int r,int x)
{
	int res=0,mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(bi[mid].a>=x)
		{
			res=mid;
			r=mid-1;
		}
		else
			l=mid+1;
	}
	return res;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(ai[i].a);
		read(ai[i].b);
	}
	std::sort(ai+1,ai+n+1);
	ai[0].a=-1;
	for(int i=1;i<=n;i++)
	{
		if(ai[i].a==ai[i-1].a&&ai[i].b==ai[i-1].b)
			val[cnt]++;
		else
		{
			bi[++cnt]=ai[i];
			val[cnt]++;
		}
	}
	int k=0;
	for(int i=1;i<=cnt;i++)
	{
		k=std::max(k,ci[i]);
		if(bi[i].a+bi[i].b>=n)
			continue;
		val[i]=std::min(val[i],n-bi[i].a-bi[i].b);
		ans=std::max(ans,k+val[i]);
		int tmp=get(i+1,cnt,n-bi[i].b);
		if(tmp)
			ci[tmp]=std::max(k+val[i],ci[tmp]);
	}
	std::cout<<n-ans;
	fclose(stdin);
	fclose(stdout);
	return 0;
}
