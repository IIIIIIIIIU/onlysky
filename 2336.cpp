#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=1e3+5;
const int INF=0x3f3f3f3f;

int n,ans=INF,t[maxn],a[maxn],b[maxn];
int staa[maxn],stab[maxn],sta[maxn],topa,topb,top;

bool cmpa(int A,int B)
{
	return ((b[A]>b[B])||(b[A]==b[B]&&a[A]<=a[B]));
}

bool cmpb(int A,int B)
{
	return ((a[A]>a[B])||(a[A]==a[B]&&b[A]<=b[B]));
}

void solve()
{
	int tmp=INF,suma=0,sumb=0,topa=0,topb=0;
	for(int i=1;i<=n;i++)
		if(t[i]==1)
		{
			staa[++topa]=i;
			suma+=a[i];
		}
		else
		{
			stab[++topb]=i;
			sumb+=b[i];
		}
	std::sort(staa+1,staa+topa+1,cmpa);
	std::sort(stab+1,stab+topb+1,cmpb);
	real T=20000;
	while(T>0.1)
	{
		int tima=suma,timb=sumb,temp=0,x1=0,y1=0,x2=0,y2=0;
		if(topa)
		{
			x1=rand()%topa+1;
			y1=rand()%topa+1;
		}
		if(topb)
		{
			x2=rand()%topb+1;
			y2=rand()%topb+1;
		}
		std::swap(staa[x1],staa[y1]);
		std::swap(stab[x2],stab[y2]);
		for(int i=1;i<=topa;i++)
		{
			temp+=a[staa[i]];
			timb=std::max(temp,timb)+b[staa[i]];
		}
		temp=0;
		for(int i=1;i<=topb;i++)
		{
			temp+=b[stab[i]];
			tima=std::max(temp,tima)+a[stab[i]];
		}
		temp=std::max(tima,timb);
		if(temp<=tmp||(temp>tmp&&rand()%10000>T))
			tmp=temp;
		else
		{
			std::swap(staa[x1],staa[y1]);
			std::swap(stab[x2],stab[y2]);
		}
		T*=0.995;
	}
	ans=std::min(ans,tmp);
}

void divide(int x)
{
	if(x>top)
	{
		solve();
		return;
	}
	t[sta[x]]=1;
	if(rand()%32767<20000)
		divide(x+1);
	t[sta[x]]=2;
	if(rand()%32767<20000)
		divide(x+1);
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&t[i],&a[i],&b[i]);
		if(t[i]==3)
			sta[++top]=i;
	}
	for(int i=1;i<=1000;i++)
		divide(1);
	std::cout<<ans<<std::endl;
	return 0;
}
