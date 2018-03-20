#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int mod=1e9+7;

typedef long long ll;

int n,GCD,LCM,m,pi[13],num,up[13],down[13];
int ai[1005],si[1005],cnt,ans[1005],seq[1005],ans2[1005];
int f[805][1<<16],g[805][1<<16],tans[1<<16];

inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x%mod;
		e>>1;
		x=x*x%mod;
	}
	return res;
}

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

inline void pre(int x)
{
	for(int i=2,t=x;i*i<=t;i++)
	{
		if(x%i==0)
		{
			pi[++num]=i;
			while(x%i==0)
			{
				++up[num];
				x/=i;
			}
		}
	}
	if(x!=1)
	{
		pi[++num]=x;
		up[x]=1;
	}
	x=GCD;
	for(int i=1;i<=num;i++)
	{
		while(x%pi[i]==0)
		{
			down[i]++;
			x/=pi[i];
		}
	}
}

void dfs(int now,int deep,int s)
{
	if(now>n)
		return;
	if(deep==num+1)
	{
		ai[++cnt]=now;
		si[cnt]=s;
		return;
	}
	int t=1;
	for(int i=0;i<=up[deep];i++,t*=pi[deep])
		if(i<=up[deep]&&i>=down[deep])
			dfs(now*t,deep+1,s|(i==up[deep]?1<<(deep-1):0)|(i==down[deep]?1<<(deep+num-1):0));
}

inline void add(int &x,int y)
{
	if((x+=y)>=mod)
		x-=mod;
}

inline void add(ll &x,ll y)
{
	if((x+=y)>=mod)
		x-=mod;
}

inline void mis(int &x,int y)
{
	if((x-=y)<0)
		x+=mod;
}

void fwtor(int *p,int len)
{
	if(len==1)
		return;
	fwtor(p,len>>1);
	fwtor(p+(len>>1),len>>1);
	for(int i=0;i<(len>>1);i++)
		add(p[i+(len>>1)],p[i]);
}

void ifwtor(int *p,int len)
{
	if(len==1)
		return;
	for(int i=0;i<(len>>1);i++)
		mis(p[i+(len>>1)],p[i]);
	ifwtor(p,len>>1);
	ifwtor(p+(len>>1),len>>1);
}

inline bool compare(const int &a,const int &b)
{
	return ai[a]<ai[b];
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(GCD);
	read(LCM);
	read(m);
	if(LCM%GCD!=0)
	{
		while(m--)
			puts("0");
		return 0;
	}
	pre(LCM);
	int n2=num<<1;
	dfs(1,1,0);
	f[0][0]=1;
	for(int i=1;i<=cnt;i++)
		for(int _s=0;_s<(1<<n2);_s++)
		{
			add(f[i][_s],f[i-1][_s]);
			add(f[i][_s|si[i]],f[i-1][_s]);
		}
	g[cnt+1][0]=1;
	for(int i=cnt;i>=1;i--)
		for(int _s=0;_s<(1<<n2);_s++)
		{
			add(g[i][_s],g[i+1][_s]);
			add(g[i][_s|si[i]],g[i+1][_s]);
		}
	ll Ans=f[cnt][(1<<n2)-1];
	for(int i=0;i<=cnt;i++)
		fwtor(f[i],1<<n2);
	for(int i=cnt+1;i>=1;i--)
		fwtor(g[i],1<<n2);
	for(int i=1;i<=cnt;i++)
	{
		for(int v=0;v<(1<<n2);v++)
			tans[v]=1LL*f[i-1][v]*g[i+1][v]%mod;
		ifwtor(tans,1<<n2);
		ans[i]=(Ans-tans[(1<<n2)-1]+mod)%mod;
		seq[i]=i;
	}
	std::sort(seq+1,seq+cnt+1,compare);
	for(int i=1;i<=cnt;i++)
	{
		ans2[i]=ans[seq[i]];
		seq[i]=ai[seq[i]];
	}
	for(int x,tmp;m--;)
	{
		read(x);
		if(x%GCD!=0||LCM%x!=0)
			puts("0");
		else
		{
			tmp=std::lower_bound(seq+1,seq+cnt+1,x)-seq;
			printf("%d\n",ans2[tmp]);
		}
	}
	return 0;
}
