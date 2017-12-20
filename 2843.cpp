#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=3e4+5;
int val[maxn],sum[maxn],f[maxn],ch[maxn][2],n,m,rev[maxn];
int stack[maxn];
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
inline bool isroot(int now)
{
	return ch[f[now]][1]!=now&&ch[f[now]][0]!=now;
}
inline void pushdown(int now)
{
	if(rev[now])
	{
		std::swap(ch[now][0],ch[now][1]);
		rev[ch[now][0]]^=1;
		rev[ch[now][1]]^=1;
		rev[now]=0;
	}
}
inline void updata(int now)
{
	sum[now]=val[now]+sum[ch[now][0]]+sum[ch[now][1]];
}
inline void rotate(int now)
{
	int fa=f[now],ffa=f[fa],l=(ch[fa][1]==now),r=(l^1);
	if(!isroot(fa))
		ch[ffa][ch[ffa][1]==fa]=now;
	f[now]=ffa;
	ch[fa][l]=ch[now][r];
	ch[now][r]=fa;
	f[fa]=now;
	if(ch[fa][l])
		f[ch[fa][l]]=fa;
	updata(fa);
}
inline void splay(int now)
{
	int fa=now,ffa,top=1;
	stack[1]=now;
	while(!isroot(fa))
		stack[++top]=(fa=f[fa]);
	while(top>0)
		pushdown(stack[top--]);
	while(!isroot(now))
	{
		fa=f[now];
		ffa=f[fa];
		if(!isroot(fa))
		{
			if(ch[ffa][1]==fa^ch[fa][1]==now)
				rotate(now);
			else
				rotate(fa);
		}
		rotate(now);
	}
	updata(now);
}
inline void access(int now)
{
	for(int t=0;now;t=now,now=f[now])
	{
		splay(now);
		ch[now][1]=t;
		updata(now);
	}
}
inline void makeroot(int now)
{
	access(now);
	splay(now);
	rev[now]^=1;
}
inline bool connection(int x,int y)
{
	while(f[x])
		x=f[x];
	while(f[y])
		y=f[y];
	return x==y;
}
inline void link(int x,int y)
{
	if(x==y)
		return;
	makeroot(x);
	f[x]=y;
}
inline int get(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
	return sum[y];
}
inline void solve(int x,int y)
{
	makeroot(x);
	val[x]=y;
	updata(x);
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(val[i]);
		sum[i]=val[i];
	}
	read(m);
	char op[15];
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%s",op);
		if(op[0]=='b')
		{
			read(x);
			read(y);
			if(connection(x,y))
				puts("no");
			else
			{
				puts("yes");
				link(x,y);
			}
		}
		else if(op[0]=='p')
		{
			read(x);
			read(y);
			solve(x,y);
		}
		else
		{
			read(x);
			read(y);
			if(connection(x,y))
				printf("%d\n",get(x,y));
			else
				puts("impossible");
		}
	}
	return 0;
}
