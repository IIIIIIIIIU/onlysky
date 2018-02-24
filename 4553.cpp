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
			int val;
			node *ch[2];
			node()
			{
				val=0;
				ch[0]=NULL;
				ch[1]=NULL;
			}
			void update()
			{
				val=std::max(ch[0]==NULL?0:ch[0]->val,ch[1]==NULL?0:ch[1]->val);
			}
		};
	public:
		struct node *root;
		SegTreeType()
		{
			root=NULL;
		}
		void update(node *&now,int l,int r,int to,int x)
		{
			if(now==NULL)
				now=new node;
			if(l==r)
			{
				now->val=std::max(x,now->val);
				return;
			}
			int mid=l+r>>1;
			if(to<=mid)
				update(now->ch[0],l,mid,to,x);
			else
				update(now->ch[1],mid+1,r,to,x);
			now->update();
		}
		int query(node *now,int l,int r,int tl,int tr)
		{
			if(now==NULL)
				return 0;
			if(tl<=l&&tr>=r)
				return now->val;
			int res=0,mid=l+r>>1;
			if(tl<=mid)
				res=query(now->ch[0],l,mid,tl,tr);
			if(tr>mid)
				res=std::max(res,query(now->ch[1],mid+1,r,tl,tr));
			return res;
		}
};
class SegTreeType tree[maxn];
int n,m,ai[maxn],Max[maxn],Min[maxn],f[maxn];
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
int query(int lit1,int lit2)
{
	int res=0;
	while(lit1)
	{
		res=std::max(res,tree[lit1].query(tree[lit1].root,1,100000,1,lit2));
		lit1-=(lit1&(-lit1));
	}
	return res;
}
void update(int x,int y,int z)
{
	while(x<=100000)
	{
		tree[x].update(tree[x].root,1,100000,y,z);
		x+=(x&(-x));
	}
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
	{
		read(ai[i]);
		Max[i]=ai[i];
		Min[i]=ai[i];
	}
	int x,y;
	for(int i=1;i<=m;i++)
	{
		read(x);
		read(y);
		Max[x]=std::max(y,Max[x]);
		Min[x]=std::min(y,Min[x]);
	}
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		f[i]=1;
		f[i]+=query(Min[i],ai[i]);
		update(ai[i],Max[i],f[i]);
		if(f[i]>ans)
			ans=f[i];
	}
	std::cout<<ans<<std::endl;
	return 0;
}
