#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=20005;

class TreeType
{
	private:
		struct NodeType
		{
			int val;

			NodeType *lc,*rc;

			NodeType()
			{
				val=0;
				lc=rc=NULL;
			}
		};
	public:
		struct NodeType *root;

		void add(NodeType *&now,int l,int r,int to,int x)
		{
			if(now==NULL) now=new NodeType;
			now->val+=x;
			if(l==r) return;
			int mid=l+r>>1;
			if(to<=mid) add(now->lc,l,mid,to,x);
			else add(now->rc,mid+1,r,to,x);
		}

		int query(NodeType *now,int l,int r,int tl,int tr)
		{
			if(now==NULL) return 0;
			if(l>=tl&&r<=tr) return now->val;
			int mid=l+r>>1,res=0;
			if(tl<=mid) res+=query(now->lc,l,mid,tl,tr);
			if(tr>mid) res+=query(now->rc,mid+1,r,tl,tr);
			return res;
		}
};

class TreeType tree[maxn];

#define lowbit(x) (x&(-x))

int n,ai[maxn],bi[maxn],ci[maxn],size,m,all,tree2[maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

int query(int l,int r,int tl,int tr)
{
	int res=0;l--;
	while(r) res+=tree[r].query(tree[r].root,1,size,tl,tr),r-=lowbit(r);
	while(l) res-=tree[l].query(tree[l].root,1,size,tl,tr),l-=lowbit(l);
	return res;
}

void add(int to,int pos,int x)
{
	while(to<=n) tree[to].add(tree[to].root,1,size,pos,x),to+=lowbit(to);
}

void add2(int to,int x)
{
	while(to<=size) tree2[to]+=x,to+=lowbit(to);
}

int query2(int x)
{
	int res=0;
	while(x) res+=tree2[x],x-=lowbit(x);
	return res;
}

int main()
{
//	freopen("nt2011_queue.in","r",stdin);
//	freopen("nt2011_queue.out","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		bi[i]=ai[i];
	}
	std::sort(bi+1,bi+n+1);
	size=std::unique(bi+1,bi+n+1)-bi-1;
	for(int i=1;i<=n;i++)
	{
		ai[i]=std::lower_bound(bi+1,bi+size+1,ai[i])-bi;
		add(i,ai[i],1);
	}
	for(int i=n;i>=1;i--)
	{
		add2(ai[i],1);
		if(ai[i]>1) all+=query2(ai[i]-1);
	}
	read(m);
	int u,v;
	printf("%d\n",all);
	for(int i=1;i<=m;i++)
	{
		read(u),read(v);
		if(u>v) std::swap(u,v);
		if(ai[u]==ai[v])
		{
			printf("%d\n",all);
			continue;
		}
		if(u<n&&ai[u]>1) all-=query(u+1,n,1,ai[u]-1);
		if(u>1&&ai[u]<size) all-=query(1,u-1,ai[u]+1,size);
		if(v<n&&ai[v]>1) all-=query(v+1,n,1,ai[v]-1);
		if(v>1&&ai[v]<size) all-=query(1,v-1,ai[v]+1,size);
		if(ai[u]>ai[v]) all++;
		add(u,ai[u],-1);
		add(v,ai[v],-1);
		std::swap(ai[u],ai[v]);
		add(u,ai[u],1);
		add(v,ai[v],1);
		if(u<n&&ai[u]>1) all+=query(u+1,n,1,ai[u]-1);
		if(u>1&&ai[u]<size) all+=query(1,u-1,ai[u]+1,size);
		if(v<n&&ai[v]>1) all+=query(v+1,n,1,ai[v]-1);
		if(v>1&&ai[v]<size) all+=query(1,v-1,ai[v]+1,size);
		if(ai[u]>ai[v]) all--;
		printf("%d\n",all);
	}
	return 0;
}
