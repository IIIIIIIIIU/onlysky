#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mod=1e9+7;
const int maxn=1e5+5;
int n,m,f[20][maxn],tot,bit[20],Log[maxn];
int last[20][maxn],ans;
bool vis[maxn];
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
int find(int x,int base)
{
	if(f[base][x]==x)
		return x;
	else
		return f[base][x]=find(f[base][x],base);
}
void merge(int x,int y,int base)
{
	x=find(x,base);
	y=find(y,base);
	f[base][y]=x;
}
ll poww(int x,int y)
{
	ll res=1,t=x;
	while(y>0)
	{
		if(y&1)
			(res*=t)%=mod;
		(t*=t)%=mod;
		y>>=1;
	}
	return res;
}
int main()
{
	read(n);
	read(m);
	bit[1]=1;
	for(int i=2;i<=19;i++)
		bit[i]=bit[i-1]<<1;
	for(int i=1,p=1,k=1;i<=n;i++)
	{
		while((k<<1)<=i)
		{
			k<<=1;
			p++;
		}
		Log[i]=p;
	}
	for(int i=19;i>=1;i--)
		for(int v=1;v<=n;v++)
			f[i][v]=v;
	for(int i=1,l1,r1,l2,r2;i<=m;i++)
	{
		read(l1);
		read(r1);
		read(l2);
		read(r2);
		int len=r1-l1+1,t=Log[len];
		merge(l1,l2,t);
		merge(r1-bit[t]+1,r2-bit[t]+1,t);
	}
	for(int i=19;i>1;i--)
		for(int v=1,t;v<=n;v++)
		{
			t=find(v,i);
			if(last[i][t])
			{
				merge(last[i][t],v,i-1);
				if(t+bit[i-1]<=n)
					merge(last[i][t]+bit[i-1],v+bit[i-1],i-1);
			}
			last[i][t]=v;
		}
	for(int i=1,t;i<=n;i++)
	{
		t=find(i,1);
		if(!vis[t])
			ans++;
		vis[t]=true;
	}
	printf("%lld\n",(1LL*9*poww(10,ans-1))%mod);
	return 0;
}
