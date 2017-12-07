#pragma GCC optimize(2)

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=3075613;
const int maxn=1e6+1e5+5;

struct OperationType
{
	int op,x,y;
};

struct OperationType operation[maxn];

struct EdgeType
{
	int u,v,w;
};

struct EdgeType edge[maxn];

int ch[maxn][2],f[maxn],val[maxn],id[maxn],BaseVal[maxn],n,m,q,bi[maxn];
int BaseId[maxn],rev[maxn],stack[maxn],top,out[maxn],ans[maxn],cnt,tag[maxn];
int head[maxn*3],E[maxn],V[maxn],tot;

bool vis[maxn];

const int BUF=22341235;

char buf[BUF],*Cget=buf;

inline void read(int &now)
{
	now=0;
	while(*(++Cget)>'9'||*Cget<'0');
	while(*Cget>='0'&&*Cget<='9')
		now=now*10+(*(Cget++))-'0';
}
/*
inline bool isroot(const int &now)
{
	return ch[f[now]][0]!=now&&ch[f[now]][1]!=now;
}*/

#define isroot(x) (ch[f[x]][0]!=x&&ch[f[x]][1]!=x)

inline void swap(int &x,int &y)
{
	register int t=y;
	y=x;
	x=t;
}

inline void pushdown(const int &now)
{
	if(rev[now])
	{
		rev[now]=0;
		swap(ch[now][0],ch[now][1]);
		if(ch[now][0])
			rev[ch[now][0]]^=1;
		if(ch[now][1])
			rev[ch[now][1]]^=1;
	}
}

inline void updata(const int &now)
{
	id[now]=BaseId[now];
	val[now]=BaseVal[now];
	if(ch[now][0]&&val[ch[now][0]]>val[now])
	{
		id[now]=id[ch[now][0]];
		val[now]=val[ch[now][0]];
	}
	if(ch[now][1]&&val[ch[now][1]]>val[now])
	{
		id[now]=id[ch[now][1]];
		val[now]=val[ch[now][1]];
	}
}

inline void rotate(const int &now)
{
	register int fa=f[now],ffa=f[fa],l=(ch[fa][1]==now),r=(l^1);
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
	register int fa,ffa;
	stack[top=1]=fa=now;
	while(!isroot(fa))
	{
		stack[++top]=f[fa];
		fa=f[fa];
	}
	while(top)
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

inline void access(const int &now)
{
	for(register int i=now,t=0;i;t=i,i=f[i])
	{
		splay(i);
		ch[i][1]=t;
		updata(i);
	}
}

inline void makeroot(const int &now)
{
	access(now);
	splay(now);
	rev[now]^=1;
}

inline void link(const int &x,const int &y)
{
	makeroot(x);
	f[x]=y;
}

inline void cut(const int &x,const int &y)
{
	makeroot(y);
	access(x);
	splay(x);
	ch[x][0]=0;
	f[y]=0;
}

inline int findroot(int now)
{
	while(f[now])
		now=f[now];
	return now;
}

inline bool connection(const int &x,const int &y)
{
	return findroot(x)==findroot(y);
}

inline void Operation(const int &x,const int &y,const int &z,const int &w)
{
	if(connection(x,y))
	{
		makeroot(x);
		access(y);
		splay(y);
		int k1=id[y],k2=val[y];
		if(k2>z)
		{
			cut(edge[k1-n].u,k1);
			cut(edge[k1-n].v,k1);
			link(x,w);
			link(w,y);
		}
	}
	else
	{
		link(x,w);
		link(w,y);
	}
}

int main()
{
	freopen("tube_strong.in","r",stdin);
	freopen("tube_strong.out","w",stdout);
//	freopen("data.txt","r",stdin);
	fread(Cget+1,1,BUF,stdin);
	Cget[strlen(Cget+1)+1]='\n';
	read(n);
	read(m);
	read(q);
	for(int i=1;i<=n;i++)
	{
		BaseVal[i]=-1;
		BaseId[i]=i;
	}
	ll tmp;
	for(int i=1;i<=m;i++)
	{
		read(edge[i].u);
		read(edge[i].v);
		if(edge[i].u>edge[i].v)
			swap(edge[i].u,edge[i].v);
		read(edge[i].w);
		BaseId[i+n]=i+n;
		BaseVal[i+n]=edge[i].w;
		tmp=edge[i].u*1LL*3157+edge[i].v;
		tmp%=mod;
		E[++tot]=head[tmp];
		V[tot]=i;
		head[tmp]=tot;
	}
	for(register int i=1,x;i<=q;i++)
	{
		read(operation[i].op);
		read(operation[i].x);
		read(operation[i].y);
		if(operation[i].x>operation[i].y)
			swap(operation[i].x,operation[i].y);
		if(operation[i].op==2)
		{
			tmp=operation[i].x*1LL*3157+operation[i].y;
			tmp%=mod;
			for(int v=head[tmp];v!=0;v=E[v])
				if(edge[V[v]].u==operation[i].x&&edge[V[v]].v==operation[i].y)
				{
					x=V[v];
					break;
				}
			vis[x]=true;
			tag[i]=x;
		}
	}
	for(register int i=1;i<=m;i++)
		if(!vis[i])
			Operation(edge[i].u,edge[i].v,edge[i].w,i+n);
	for(register int i=q;i>=1;i--)
		if(operation[i].op==1)
		{
			makeroot(operation[i].x);
			access(operation[i].y);
			splay(operation[i].y);
			ans[++cnt]=val[operation[i].y];
		}
		else
		{
			int t=tag[i];
			Operation(edge[t].u,edge[t].v,edge[t].w,t+n);
		}
	for(int i=cnt;i>=1;i--)
		printf("%d\n",ans[i]);
	return 0;
}
