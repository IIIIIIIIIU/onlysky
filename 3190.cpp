#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-8;
const int maxn=1e5+5;

struct node
{
	int g,v,id;
	
	inline bool operator<(const node &tmp)const
	{
		if(v==tmp.v)
			return g<tmp.g;
		return v<tmp.v;
	}
};

struct node ai[maxn],s[maxn];

int ans[maxn],n,tp;

real get(node a,node b)
{
	return (real)(a.g-b.g)/(real)(b.v-a.v);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&ai[i].g);
		ai[i].id=i;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&ai[i].v);
	std::sort(ai+1,ai+n+1);
	s[tp=1]=ai[1];
	ans[1]=ai[1].id;
	for(int i=2;i<=n;i++)
	{
		while(tp>=1&&get(s[tp],ai[i])<-eps)
			--tp;
		while(tp>=2&&get(s[tp-1],s[tp])>get(s[tp],ai[i]))
			--tp;
		s[++tp]=ai[i];
		ans[tp]=ai[i].id;
	}
	std::sort(ans+1,ans+tp+1);
	printf("%d\n",tp);
	for(int i=1;i<tp;i++)
		printf("%d ",ans[i]);
	printf("%d",ans[tp]);
	return 0;
}
