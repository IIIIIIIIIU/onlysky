#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef double real;
const int maxn=4e5+5;
const real pi=std::acos(-1.0);
struct node
{
	real a,b;
	node(){}
	node(real a_,real b_)
	{
		a=a_;
		b=b_;
	}
	inline node operator+(const node &tmp)const
	{
		return node(a+tmp.a,b+tmp.b);
	}
	inline node operator-(const node &tmp)const
	{
		return node(a-tmp.a,b-tmp.b);
	}
	inline node operator*(const node &tmp)const
	{
		return node(a*tmp.a-b*tmp.b,a*tmp.b+b*tmp.a);
	}
	inline node operator/(const real &tmp)const
	{
		return node(a/tmp,b/tmp);
	}
};
struct node f[maxn],g[maxn],u[maxn];
int n;
real ai[maxn],ans[maxn];
void fft(node *p,int len,int opt)
{
	for(int i=1,v=0,k;i<len;++i)
	{
		for(k=(len>>1);v&k;k>>=1)
			v^=k;
		v^=k;
		if(i<v)
			std::swap(p[i],p[v]);
	}
	for(int h=2;h<=len;h<<=1)
	{
		node wn=node(std::cos(opt*pi*2/h),std::sin(opt*pi*2/h));
		for(int v=0;v<len;v+=h)
		{
			node w=node(1.0,0.0);
			for(int t=0;t<h/2;++t,w=w*wn)
			{
				node tmp1=p[t+v],tmp2=p[t+v+h/2];
				p[t+v]=tmp1+tmp2*w;
				p[t+v+h/2]=tmp1-tmp2*w;
			}
		}
	}
	if(opt==-1)
		for(int i=0;i<len;++i)
			p[i]=p[i]/len;
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%lf",&ai[i]);
	int len=2;
	while(len<n*2)
		len<<=1;
	for(int i=0;i<n;i++)
		f[i].a=ai[i];
	for(int i=1;i<n;i++)
		g[i].a=1.0/i/i;
	fft(f,len,1);
	fft(g,len,1);
	for(int i=0;i<len;i++)
		u[i]=f[i]*g[i];
	fft(u,len,-1);
	for(int i=0;i<n;i++)
		ans[i]+=u[i].a;
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(u,0,sizeof(u));
	for(int i=0;i<n;i++)
		f[i].a=ai[n-i-1];
	for(int i=1;i<n;i++)
		g[i].a=1.0/i/i;
	fft(f,len,1);
	fft(g,len,1);
	for(int i=0;i<len;i++)
		u[i]=f[i]*g[i];
	fft(u,len,-1);
	for(int i=n-1;i>=0;i--)
		printf("%.10lf\n",ans[n-i-1]-u[i].a);
	return 0;
}
