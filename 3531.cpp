#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e5+5;
class SegTreeType
{
	private:
		struct node
		{
			int val,Max;
			node *lc,*rc;
			node()
			{
				val=0;
				Max=0;
				lc=NULL;
				rc=NULL;
			}
		};
	public:
		struct node *root;
		SegTreeType()
		{
			root=new node;
		}
		void add(node *&now,int l,int r,int to,int x)
		{
			if(now==NULL)
				now=new node;
			if(l==r)
			{
				now->val+=x;
				now->Max=now->val;
				return;
			}
			int mid=l+r>>1;
			if(to<=mid)
				add(now->lc,l,mid,to,x);
			else
				add(now->rc,mid+1,r,to,x);
			now->val=0;
			now->Max=0;
			if(now->lc!=NULL)
			{
				now->val+=now->lc->val;
				if(now->lc->Max>now->Max)
					now->Max=now->lc->Max;
			}
			if(now->rc!=NULL)
			{
				now->val+=now->rc->val;
				if(now->rc->Max>now->Max)
					now->Max=now->rc->Max;
			}
		}
		int querySum(node *&now,int l,int r,int tl,int tr)
		{
			if(now==NULL)
				return 0;
			if(tl<=l&&tr>=r)
				return now->val;
			int mid=l+r>>1,res=0;
			if(tl<=mid)
				res+=querySum(now->lc,l,mid,tl,tr);
			if(tr>mid)
				res+=querySum(now->rc,mid+1,r,tl,tr);
			return res;
		}
		int queryMax(node *&now,int l,int r,int tl,int tr)
		{
			if(now==NULL)
				return 0;
			if(tl<=l&&tr>=r)
				return now->Max;
			int mid=l+r>>1,res=0;
			if(tl<=mid)
				res=queryMax(now->lc,l,mid,tl,tr);
			if(tr>mid)
				res=std::max(queryMax(now->rc,mid+1,r,tl,tr),res);
			return res;
		}
};
class SegTreeType tree[maxn];
int n,m,bel[maxn],val[maxn],head[maxn],E[maxn<<1|1];
int V[maxn<<1|1],cnt,f[maxn],size[maxn],top[maxn];
int lar[maxn],id[maxn],deep[maxn];
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
			if(size[V[i]]>size[lar[now]])
				lar[now]=V[i];
		}
}
void dfs2(int now,int chain)
{
	id[now]=++cnt;
	top[now]=chain;
	if(lar[now])
		dfs2(lar[now],chain);
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=f[now]&&V[i]!=lar[now])
			dfs2(V[i],V[i]);
}
int querySum(int x,int y,int c)
{
	int res=0;
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
		{
			res+=tree[c].querySum(tree[c].root,1,n,id[top[x]],id[x]);
			x=f[top[x]];
		}
		else
		{
			res+=tree[c].querySum(tree[c].root,1,n,id[top[y]],id[y]);
			y=f[top[y]];
		}
	if(deep[x]>deep[y])
		std::swap(x,y);
	res+=tree[c].querySum(tree[c].root,1,n,id[x],id[y]);
	return res;
}
int queryMax(int x,int y,int c)
{
	int res=0;
	while(top[x]!=top[y])
		if(deep[top[x]]>deep[top[y]])
		{
			res=std::max(res,tree[c].queryMax(tree[c].root,1,n,id[top[x]],id[x]));
			x=f[top[x]];
		}
		else
		{
			res=std::max(res,tree[c].queryMax(tree[c].root,1,n,id[top[y]],id[y]));
			y=f[top[y]];
		}
	if(deep[x]>deep[y])
		std::swap(x,y);
	res=std::max(res,tree[c].queryMax(tree[c].root,1,n,id[x],id[y]));
	return res;
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
	{
		read(val[i]);
		read(bel[i]);
	}
	for(int i=1,u,v;i<n;i++)
	{
		read(u);
		read(v);
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		head[v]=cnt;
	}
	cnt=0;
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		tree[bel[i]].add(tree[bel[i]].root,1,n,id[i],val[i]);
	char op[5];
	int x,y;
	while(m--)
	{
		scanf("%s",op);
		read(x);
		read(y);
		if(op[0]=='C'&&op[1]=='C')
		{
			tree[bel[x]].add(tree[bel[x]].root,1,n,id[x],-val[x]);
			bel[x]=y;
			tree[bel[x]].add(tree[bel[x]].root,1,n,id[x],val[x]);
		}
		else if(op[0]=='C'&&op[1]=='W')
		{
			tree[bel[x]].add(tree[bel[x]].root,1,n,id[x],y-val[x]);
			val[x]=y;
		}
		else if(op[0]=='Q'&&op[1]=='S')
			printf("%d\n",querySum(x,y,bel[x]));
		else
			printf("%d\n",queryMax(x,y,bel[x]));
	}
	return 0;
}
