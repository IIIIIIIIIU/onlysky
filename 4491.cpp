#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=5e4+5;
const int maxtree=maxn<<2|1;

using std::max;

class SegTreeType
{
	private:
		struct node
		{
			int len,Max,l,r,lv,rv;
			
			node operator+(const node &tmp)const
			{
				node res;
				res.len=len+tmp.len;
				res.Max=max(Max,tmp.Max);
				res.l=l;
				res.r=tmp.r;
				res.lv=lv;
				res.rv=tmp.rv;
				if(tmp.lv>=rv)
				{
					if(r+tmp.l>res.Max)
						res.Max=r+tmp.l;
					if(l==len)
						res.l+=tmp.l;
					if(tmp.r==tmp.len)
						res.r+=r;
					res.Max=max(res.Max,max(res.l,res.r));
				}
				return res;
			}
		};
		
		struct node val[maxtree];
		
		int L[maxtree],R[maxtree],mid[maxtree];
	
		node query(int now,int l,int r)
		{
			if(L[now]>=l&&R[now]<=r)
				return val[now];
			node res;
			bool DID=false;
			if(l<=mid[now])
			{
				res=query(now<<1,l,r);
				DID=true;
			}
			if(r>mid[now])
				if(DID)
					res=res+query(now<<1|1,l,r);
				else
					res=query(now<<1|1,l,r);
			return res;
		}
	
	public:
		void build(int now,int l,int r,int *p)
		{
			L[now]=l;
			R[now]=r;
			if(l==r)
			{
				val[now].len=1;
				val[now].lv=p[l];
				val[now].rv=p[l];
				val[now].Max=1;
				val[now].l=1;
				val[now].r=1;
				return;
			}
			mid[now]=l+r>>1;
			build(now<<1,l,mid[now],p);
			build(now<<1|1,mid[now]+1,r,p);
			val[now]=val[now<<1]+val[now<<1|1];
		}
		
		int query(int l,int r)
		{
			return query(1,l,r).Max;
		}
};

class SegTreeType tree1,tree2;

int n,ai[maxn],q;

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

int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(ai[i]);
	tree1.build(1,1,n,ai);
	for(int i=1;i<=n;i++)
		ai[i]=-ai[i];
	tree2.build(1,1,n,ai);
	read(q);
	for(int i=1,l,r;i<=q;i++)
	{
		read(l);
		read(r);
		printf("%d\n",max(tree1.query(l,r),tree2.query(l,r)));
	}
	return 0;
}
