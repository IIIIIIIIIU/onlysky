#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=3e5+5;
int n,m,ch[maxn][2],val[maxn],sum[maxn],f[maxn],rev[maxn];
int stack[maxn],top;
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
inline bool isroot(int x)
{
	return ch[f[x]][0]!=x&&ch[f[x]][1]!=x;
}
inline void update(int x)
{
	sum[x]=val[x]^sum[ch[x][0]]^sum[ch[x][1]];
}
inline void rotate(int x)
{
	int fa=f[x],ffa=f[fa],l=(ch[fa][1]==x),r=l^1;
	if(!isroot(fa))
		ch[ffa][ch[ffa][1]==fa]=x;
	f[fa]=x;
	f[x]=ffa;
	ch[fa][l]=ch[x][r];
	ch[x][r]=fa;
	if(ch[fa][l])
		f[ch[fa][l]]=fa;
	update(fa);
}
inline void pushdown(int x)
{
	if(rev[x])
	{
		std::swap(ch[x][0],ch[x][1]);
		if(ch[x][0])
			rev[ch[x][0]]^=1;
		if(ch[x][1])
			rev[ch[x][1]]^=1;
		rev[x]=0;
	}
}
inline void splay(int x)
{
	int fa=x,ffa;
	stack[top=1]=x;
	while(f[fa])
	{
		stack[++top]=f[fa];
		fa=f[fa];
	}
	while(top)
		pushdown(stack[top--]);
	while(!isroot(x))
	{
		fa=f[x];
		ffa=f[fa];
		if(!isroot(fa))
		{
			if(ch[fa][1]==x&&ch[ffa][1]==fa)
				rotate(x);
			else
				rotate(fa);
		}
		rotate(x);
	}
	update(x);
}
inline void access(int x)
{
	for(int t=0;x;t=x,x=f[x])
	{
		splay(x);
		ch[x][1]=t;
		update(x);
	}
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
inline int findroot(int x)
{
	access(x);
	splay(x);
	while(ch[x][0])
		x=ch[x][0];
	return x;
}
inline bool connect(int x,int y)
{
	return findroot(x)==findroot(y);
}
inline void link(int x,int y)
{
	makeroot(x);
	f[x]=y;
}
inline void cut(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
	f[x]=0;
	ch[y][0]=0;
}
inline int getVal(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
	return sum[y];
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
	{
		read(val[i]);
		sum[i]=val[i];
	}
	for(int i=1,op,x,y;i<=m;i++)
	{
		read(op);
		read(x);
		read(y);
		if(op==0)
			printf("%d\n",getVal(x,y));
		else if(op==1)
		{
			if(!connect(x,y))
				link(x,y);
		}
		else if(op==2)
		{
			if(connect(x,y))
				cut(x,y);
		}
		else
		{
			makeroot(x);
			splay(x);
			sum[x]^=val[x];
			val[x]=y;
			sum[x]^=y;
		}
	}
	return 0;
}
