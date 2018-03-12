#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;
const int maxtree=maxn*80+1;

int n,m,ci[maxn],deep[maxn],head[maxn],E[maxn],V[maxn];
int cnt,li[maxn],ri[maxn],num,f[maxn],size[maxn],lar[maxn];
int top[maxn],root[maxn],ch[maxtree][2],val[maxtree],tot;
int back[maxn],seq[maxn];

std::set<int>Set[maxn];

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

void dfs(int now)
{
	lar[now]=0;
	size[now]=1;
	deep[now]=deep[f[now]]+1;
	for(int i=head[now];i;i=E[i])
	{
		dfs(V[i]);
		size[now]+=size[V[i]];
		if(size[V[i]]>size[lar[now]])
			lar[now]=V[i];
	}
}

void dfs2(int now,int chain)
{
	li[now]=++cnt;
	back[cnt]=now;
	top[now]=chain;
	if(lar[now])
		dfs2(lar[now],chain);
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=lar[now])
			dfs2(V[i],V[i]);
	ri[now]=cnt;
}

inline int getLca(int x,int y)
{
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
			x=f[top[x]];
		else
			y=f[top[y]];
	if(deep[x]>deep[y])
		return y;
	return x;
}

inline void update(int &now,int pre,int l,int r,int to,int x)
{
	now=++tot;
	val[now]=val[pre]+x;
	if(l==r)
		return;
	int mid=l+r>>1;
	if(to<=mid)
	{
		update(ch[now][0],ch[pre][0],l,mid,to,x);
		ch[now][1]=ch[pre][1];
	}
	else
	{
		update(ch[now][1],ch[pre][1],mid+1,r,to,x);
		ch[now][0]=ch[pre][0];
	}
}

inline int query(int now,int l,int r,int tl,int tr)
{
	if(!now)
		return 0;
	if(tl<=l&&r<=tr)
		return val[now];
	int mid=l+r>>1,res=0;
	if(tl<=mid)
		res+=query(ch[now][0],l,mid,tl,tr);
	if(tr>mid)
		res+=query(ch[now][1],mid+1,r,tl,tr);
	return res;
}

inline bool compare(const int &a,const int &b)
{
	if(deep[a]==deep[b])
		return li[a]<li[b];
	return deep[a]<deep[b];
}

void insert(int rt,int x)
{
	int bel=ci[x],to=li[x],pre=0,suf=0;
	std::set<int>::iterator it,it_;
	Set[bel].insert(to);
	it_=it=Set[bel].lower_bound(to);
	if(it!=Set[bel].begin())
		pre=*(--it);
	if((++it_)!=Set[bel].end())
		suf=*(it_);
	update(root[rt],root[rt],1,n,li[x],1);
	if(pre&&suf)
		update(root[rt],root[rt],1,n,li[getLca(back[pre],back[suf])],1);
	if(pre)
		update(root[rt],root[rt],1,n,li[getLca(back[pre],x)],-1);
	if(suf)
		update(root[rt],root[rt],1,n,li[getLca(back[suf],x)],-1);
}

int main()
{
	freopen("data.txt","r",stdin);
	int T;
	read(T);
	while(T--)
	{
		tot=0;
		num=0;
		cnt=0;
		read(n);
		read(m);
		for(int i=1;i<=n;i++)
		{
			head[i]=0;
			read(ci[i]);
			if(ci[i]>num)
				num=ci[i];
		}
		for(int i=1;i<=num;i++)
			Set[i].clear();
		for(int i=2;i<=n;i++)
		{
			read(f[i]);
			E[++cnt]=head[f[i]];
			V[cnt]=i;
			head[f[i]]=cnt;
		}
		cnt=0;
		dfs(1);
		dfs2(1,1);
		for(int i=1;i<=n;i++)
			seq[i]=i;
		std::sort(seq+1,seq+n+1,compare);
		for(int i=1,pos=0;i<=n;i++)
		{
			root[i]=root[i-1];
			while(pos<n&&deep[seq[pos+1]]==i)
				insert(i,seq[++pos]);
		}
		for(int i=1,x,d,last=0;i<=m;i++)
		{
			read(x);
			read(d);
			x^=last;
			d^=last;
			d=std::min(deep[x]+d,n);
			last=query(root[d],1,n,li[x],ri[x]);
			printf("%d\n",last);
		}
	}
	return 0;
}
