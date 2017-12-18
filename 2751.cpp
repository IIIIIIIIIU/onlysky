#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
const int maxn=1e5+5;
struct node
{
	int x,y;
	bool operator<(const node &tmp)const
	{
		if(x==tmp.x)
			return y<tmp.y;
		return x<tmp.x;
	}
};
struct node ai[maxn];
int n,m,k,pos[maxn],sum[maxn];
ll ans=1,C;
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
ll pow(int x)
{
	ll res=1,tmp=C;
	while(x>0)
	{
		if(x&1)
			(res*=tmp)%=mod;
		(tmp*=tmp)%=mod;
		x>>=1;
	}
	return res;
}
int main()
{
	//freopen("data.txt","r",stdin);
	//freopen("easy.in","r",stdin);
	//freopen("easy.out","w",stdout);
	read(n);
	read(m);
	read(k);
	C=1LL*n*(n-1)/2+n;
	C%=mod;
	for(int i=1;i<=k;i++)
	{
		read(ai[i].x);
		read(ai[i].y);
	}
	std::sort(ai+1,ai+k+1);
	int num=0;
	for(int i=1,now;i<=k;)
	{
		now=i;
		pos[++num]=ai[i].x;
		(sum[num]+=ai[i].y)%=mod;
		while(now<k&&ai[now+1].x==ai[now].x)
		{
			if(ai[now+1].y!=ai[now].y)
				(sum[num]+=ai[now+1].y)%=mod;
			++now;
		}
		i=now+1;
	}
	if(!k)
		printf("%lld\n",pow(m));
	else
	{
		if(pos[1]>1)
			(ans*=pow(pos[1]-1))%=mod;
		(ans*=(C-sum[1]+mod)%mod)%=mod;
		for(int i=2;i<=num;i++)
		{
			if(pos[i]>pos[i-1]+1)
				(ans*=pow(pos[i]-pos[i-1]-1))%=mod;
			(ans*=(C-sum[i]+mod)%mod)%=mod;
		}
		if(pos[num]<m)
			(ans*=pow(m-pos[num]));
		printf("%lld\n",(ans+mod)%mod);
	}
	return 0;
}
