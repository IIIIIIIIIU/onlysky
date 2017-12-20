#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=5e5+5;
const int maxm=maxn<<1;
int n,lim,g[maxn],next[maxn],q[maxn];
ll fa[maxm],fb[maxm],fc[maxm],ans;
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
inline void add(int x,int p)
{
	ll y=1LL*x*x-3*x+2;
	for(int i=x;i<=lim;i+=i&-i)
	{
		fa[i]+=p;
		fb[i]+=x*p;
		fc[i]+=y*p;
	}
}
inline ll ask(int x)
{
	ll a=0,b=0,c=0;
	for(int i=x;i>0;i-=i&-i)
	{
		a+=fa[i];
		b+=fb[i];
		c+=fc[i];
	}
	return a*(1LL*x*x+3*x)-b*2*x+c;
}
inline void work(int l,int r,int v,int p)
{
	r-=l;
	l=v-r+n+1;
	r=v+n+1;
	if(p)
	{
		add(l,-1);
		add(r+1,1);
	}
	else
	{
		ans+=ask(r-1)-ask(l-2);
		add(l,1);
		add(r+1,-1);
	}
}
int main()
{
	int x;
	read(n);
	read(x);
	lim=n*2+1;
	for(int i=1;i<=n;i++)
	{
		read(x);
		next[i]=g[x];
		g[x]=i;
	}
	q[0]=n+1;
	for(int i=0;i<=n;i++)
		if(g[i])
		{
			int m=0;
			for(int j=g[i];j;j=next[j])
				q[++m]=j;
			q[m+1]=0;
			for(int j=m+1;j;j--)
				work(q[j],q[j-1]-1,(m-j+1)*2-q[j],0);
			for(int j=m+1;j;j--)
				work(q[j],q[j-1]-1,(m-j+1)*2-q[j],1);
		}
	std::cout<<ans/2;
	return 0;
}
