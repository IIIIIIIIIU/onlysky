#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=4e4+5;
const int maxtree=maxn<<2|1;
struct data
{
	int a;
	data(){}
	data(int a_)
	{
		a=a_;
	}
	inline bool operator<(const data &tmp)const
	{
		return a>tmp.a;
	}
	inline bool operator==(const data &tmp)const
	{
		return a==tmp.a;
	}
};
struct node
{
	int num,arr[21];
	node()
	{
		num=0;
		memset(arr,0,sizeof(arr));
	}
	inline node operator+(const node &tmp)const
	{
		node res;
		int l=1,r=1;
		while(l<=num&&r<=tmp.num&&res.num<20)
		{
			if(arr[l]>tmp.arr[r])
				res.arr[++res.num]=arr[l++];
			else
				res.arr[++res.num]=tmp.arr[r++];
		}
		while(res.num<20&&l<=num)
			res.arr[++res.num]=arr[l++];
		while(res.num<20&&r<=tmp.num)
			res.arr[++res.num]=tmp.arr[r++];
		return res;
	}
};
struct node val[maxtree];
int n,m,L[maxtree],R[maxtree],mid[maxtree],head[maxn],E[maxn<<1|1];
int lar[maxn],id[maxn],back[maxn],to[maxn],xi[maxn],Arr[maxn],anum;
int V[maxn<<1|1],cnt,f[maxn],deep[maxn],top[maxn],size[maxn],K,Q;
std::multiset<data>Set[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
inline void edge_add(int u,int v)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	head[v]=cnt;
}
void dfs1(int now,int fa)
{
	f[now]=fa;
	size[now]=1;
	deep[now]=deep[fa]+1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			dfs1(V[i],now);
			size[now]+=size[V[i]];
			if(size[V[i]]>=size[lar[now]])
				lar[now]=V[i];
		}
}
void dfs2(int now,int chain)
{
	top[now]=chain;
	id[now]=++cnt;
	back[cnt]=now;
	if(lar[now])
		dfs2(lar[now],chain);
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=lar[now]&&V[i]!=f[now])
			dfs2(V[i],V[i]);
}
inline void getSet(int x)
{
	anum=0;
	if(Set[x].empty())
		return ;
	std::multiset<data>::iterator it=Set[x].begin();
	for(int i=1;i<=20&&it!=Set[x].end();i++,it++)
		Arr[++anum]=it->a;
}
void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
	{
		getSet(back[l]);
		val[now].num=anum;
		for(int i=1;i<=val[now].num;i++)
			val[now].arr[i]=Arr[i];
		return;
	}
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
	val[now]=val[now<<1]+val[now<<1|1];
}
inline node query(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	node res;
	if(l<=mid[now])
		res=res+query(now<<1,l,r);
	if(r>mid[now])
		res=res+query(now<<1|1,l,r);
	return res;
}
inline void update(int now,int to)
{
	if(L[now]==R[now])
	{
		getSet(back[to]);
		val[now].num=anum;
		for(int i=1;i<=val[now].num;i++)
			val[now].arr[i]=Arr[i];
		return;
	}
	if(to<=mid[now])
		update(now<<1,to);
	else
		update(now<<1|1,to);
	val[now]=val[now<<1]+val[now<<1|1];
}
node query(int x,int y)
{
	node res;
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
		{
			res=res+query(1,id[top[x]],id[x]);
			x=f[top[x]];
		}
		else
		{
			res=res+query(1,id[top[y]],id[y]);
			y=f[top[y]];
		}
	if(deep[x]>deep[y])
		std::swap(x,y);
	return res+query(1,id[x],id[y]);
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	for(int i=1,u,v;i<n;i++)
	{
		read(u);
		read(v);
		edge_add(u,v);
	}
	cnt=0;
	dfs1(1,0);
	dfs2(1,1);
	read(m);
	for(int i=1;i<=m;i++)
	{
		read(xi[i]);
		read(to[i]);
		Set[to[i]].insert(data(xi[i]));
	}
	build(1,1,n);
	read(Q);
	read(K);
	node tmp;
	std::multiset<data>::iterator it;
	for(int i=1,op,x,y;i<=Q;i++)
	{
		read(op);
		read(x);
		read(y);
		if(op==1)
		{
			tmp=query(x,y);
			if(!tmp.num||!K)
				puts("-1");
			else
			{
				for(int v=1;v<=tmp.num&&v<=K;v++)
					printf("%d ",tmp.arr[v]);
				puts("");
			}
		}
		else if(op==2)
		{
			it=Set[to[x]].find(data(xi[x]));
			Set[to[x]].erase(it);
			Set[y].insert(data(xi[x]));
			update(1,id[to[x]]);
			to[x]=y;
			update(1,id[to[x]]);
		}
		else if(op==3)
		{
			it=Set[to[x]].find(data(xi[x]));
			Set[to[x]].erase(it);
			xi[x]=y;
			Set[to[x]].insert(data(xi[x]));
			update(1,id[to[x]]);
		}
	}
	return 0;
}
