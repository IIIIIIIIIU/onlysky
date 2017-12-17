#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=50033;
const int maxn=1e5+5;
struct number
{
	ll up,down;
	number(){}
	number(ll up_,ll down_)
	{
		up=up_;
		down=down_;
	}
	bool operator<(const number &tmp)const
	{
		return up*tmp.down<tmp.up*down;
	}
	bool operator==(const number &tmp)const
	{
		return up*tmp.down==tmp.up*down;
	}
	void out()
	{
		if(up==0)
			printf("0\n");
		else if(down==1)
			printf("%lld\n",up);
		else if(down==-1)
			printf("%lld\n",-up);
		else
		{
			bool k=false;
			if(up<0&&down>=0||up>=0&&down<0)
				k=true;
			if(k)
				putchar('-');
			printf("%lld",std::abs(up));
			putchar('/');
			printf("%lld\n",std::abs(down));
		}
	}
};
struct number ans[maxn];
int n,ai[maxn],bi1[maxn],bi2[maxn],num1,num2,num,a0;
ll pn[maxn],qn[maxn];
inline int gcd(int a,int b)
{
	if(!b)
		return a;
	return gcd(b,a%b);
}
bool check(int p,int q)
{
	if(p==-70&&q==-140)
	{
		int ad=0;
	}
	pn[0]=1;
	qn[0]=1;
	for(int i=1;i<=n;i++)
	{
		pn[i]=pn[i-1]*p%mod;
		qn[i]=qn[i-1]*q%mod;
	}
	ll count=0;
	for(int i=1;i<=n;i++)
		(count+=(ai[i]*pn[i])%mod*qn[n-i])%=mod;
	(count=-count+mod)%=mod;
	return ai[0]*qn[n]%mod==count;
}
int main()
{
	//freopen("akai.in","r",stdin);
	//freopen("akai.out","w",stdout);
	//freopen("data.txt","r",stdin);
	scanf("%d",&n);
	for(int i=0;i<=n;i++)
	{
		scanf("%d",&ai[i]);
		if(a0==0)
			a0=std::abs(ai[i]);
	}
	int lit=(int)std::sqrt(std::abs(a0));
	for(int i=1;i<=lit;i++)
		if(a0%i==0)
		{
			bi1[++num1]=i;
			bi1[++num1]=a0/i;
			bi1[++num1]=-i;
			bi1[++num1]=-a0/i;
		}
	lit=(int)std::sqrt(std::abs(ai[n]));
	for(int i=1;i<=lit;i++)
		if(ai[n]%i==0)
		{
			bi2[++num2]=i;
			bi2[++num2]=ai[n]/i;
			bi2[++num2]=-i;
			bi2[++num2]=-ai[n]/i;
		}
	std::sort(bi1+1,bi1+num1+1);
	num1=std::unique(bi1+1,bi1+num1+1)-bi1-1;
	std::sort(bi2+1,bi2+num2+1);
	num2=std::unique(bi2+1,bi2+num2+1)-bi2-1;
	for(int i=1;i<=num1;i++)
		for(int v=1;v<=num2;v++)
			if(check(bi1[i],bi2[v]))
				ans[++num]=number(bi1[i],bi2[v]);
	if(ai[0]==0)
		ans[++num]=number(0,1);
	ll tmp;
	for(int i=1;i<=num;i++)
	{
		tmp=gcd(ans[i].up,ans[i].down);
		if(tmp)
		{
			ans[i].up/=tmp;
			ans[i].down/=tmp;
		}
		if(ans[i].up<0&&ans[i].down<0)
		{
			ans[i].up=-ans[i].up;
			ans[i].down=-ans[i].down;
		}
		if(ans[i].down<0)
		{
			ans[i].up=-ans[i].up;
			ans[i].down=-ans[i].down;
		}
	}
	std::sort(ans+1,ans+num+1);
	num=std::unique(ans+1,ans+num+1)-ans-1;
	printf("%d\n",num);
	for(int i=1;i<=num;i++)
		ans[i].out();
	return 0;
}
