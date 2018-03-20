#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=5e5+5;
const int INF=0x3f3f3f3f;
int n,m,T,Ui[maxn],Vi[maxn],Si[maxn],Ti[maxn];
int ch[maxn][2],f[maxn],Min[maxn],bid[maxn];
int id[maxn],val[maxn],stack[maxn],top,rev[maxn];
int dis[maxn],sum[maxn],Number;
int headS[maxn],ES[maxn],VS[maxn],cntS;
int headT[maxn],ET[maxn],VT[maxn],cntT;
int seq1[maxn],seq2[maxn],num1,num2,tcir[maxn];
bool vis[maxn];
inline bool isroot(const int &now)
{
	return ch[f[now]][0]!=now&&ch[f[now]][1]!=now;
}
inline void update(int now)
{
	id[now]=bid[now];
	Min[now]=val[now];
	sum[now]=dis[now]+sum[ch[now][0]]+sum[ch[now][1]];
	if(ch[now][0]&&Min[ch[now][0]]<Min[now])
	{
		Min[now]=Min[ch[now][0]];
		id[now]=id[ch[now][0]];
	}
	if(ch[now][1]&&Min[ch[now][1]]<Min[now])
	{
		Min[now]=Min[ch[now][1]];
		id[now]=id[ch[now][1]];
	}
}
inline void rotate(int now)
{
	int fa=f[now],ffa=f[fa],l=(ch[fa][1]==now),r=(l^1);
	if(!isroot(fa))
		ch[ffa][ch[ffa][1]==fa]=now;
	f[fa]=now;
	f[now]=ffa;
	ch[fa][l]=ch[now][r];
	ch[now][r]=fa;
	if(ch[fa][l])
		f[ch[fa][l]]=fa;
	update(fa);
	update(now);
}
inline void pushdown(int now)
{
	if(rev[now])
	{
		std::swap(ch[now][0],ch[now][1]);
		if(ch[now][0])
			rev[ch[now][0]]^=1;
		if(ch[now][1])
			rev[ch[now][1]]^=1;
		rev[now]=0;
	}
}
void splay(int now)
{
	int fa,ffa;
	stack[top=1]=fa=now;
	while(!isroot(fa))
		stack[++top]=fa=f[fa];
	while(top)
		pushdown(stack[top--]);
	while(!isroot(now))
	{
		fa=f[now];
		ffa=f[fa];
		if(!isroot(fa))
		{
			if(ch[ffa][1]==fa^ch[fa][1]==now)
				rotate(fa);
			else
				rotate(now);
		}
		rotate(now);
	}	
	update(now);
}
inline void access(int now)
{
	for(int t=0;now;t=now,now=f[now])
	{
		splay(now);
		ch[now][1]=t;
		update(now);
	}
}
inline void makeroot(int now)
{
	access(now);
	splay(now);
	rev[now]^=1;
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
inline int find(int now)
{
	access(now);
	splay(now);
	int t=now;
	while(ch[now][0])
		now=ch[now][0];
	splay(now);
	return now;
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
inline void edge_add_S(int u,int v)
{
	ES[++cntS]=headS[u];
	VS[cntS]=v;
	headS[u]=cntS;
}
inline void edge_add_T(int u,int v)
{
	ET[++cntT]=headT[u];
	VT[cntT]=v;
	headT[u]=cntT;
}
inline int getdis(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
	return sum[y];
}
inline void add(int now)
{
	if(now==17)
	{
		int noqw=0;
	}
	int u=Ui[now],v=Vi[now];
	if(u==v)
	{
		Number++;
		return;
	}
	now+=n;
	if(find(u)==find(v))
	{
		int d=getdis(u,v);
		if(d%2==0)
		{
			Number++;
			tcir[now]=1;
		}
		int t=id[v],va=Min[v];
		if(val[now]>va)
		{
			tcir[t+n]=tcir[now];
			if(t+n==27)
			{
				int qweq=0;
			}
			tcir[now]=0;
			vis[t]=false;
			vis[now-n]=true;
			cut(t+n,Ui[t]);
			cut(t+n,Vi[t]);
			link(now,u);
			link(now,v);
		}
	}
	else
	{
		vis[now-n]=true;
		link(u,now);
		link(v,now);
	}
}
void del(int now)
{
	if(now==17)
	{
		int qweq=0;
	}
	int u=Ui[now],v=Vi[now];
	if(u==v)
	{
		Number--;
		return;
	}
	now+=n;
	if(!vis[now-n])
	{
		/*
		int d=getdis(u,v);
		if(d%2==0)
			Number--;
			*/
	}
	else
	{
		vis[now-n]=false;
		cut(now,u);
		cut(now,v);
	}
	Number-=tcir[now];
	tcir[now]=0;
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	read(T);
	for(int i=1;i<=n;i++)
	{
		val[i]=INF;
		update(i);
	}
	for(int i=1;i<=m;i++)
	{
		read(Ui[i]);
		read(Vi[i]);
		read(Si[i]);
		read(Ti[i]);
		dis[i+n]=1;
		bid[i+n]=i;
		val[i+n]=Ti[i];
		update(i+n);
		edge_add_S(Si[i],i);
		edge_add_T(Ti[i],i);
	}
	for(int i=0;i<=T;i++)
	{
		if(i==T-1)
		{
			int vod=0;
		}
		if(i)
		{
			if(Number)
				puts("No");
			else
				puts("Yes");
		}
		num1=0;
		num2=0;
		for(int v=headS[i];v!=0;v=ES[v])
			add(VS[v]);
		for(int v=headT[i];v!=0;v=ET[v])
		{
			if(vis[VT[v]])
				seq2[++num2]=VT[v];
			else
				seq1[++num1]=VT[v];
		}
		for(int v=1;v<=num1;v++)
			del(seq1[v]);
		for(int v=1;v<=num2;v++)
			del(seq2[v]);
	}
	return 0;
}
