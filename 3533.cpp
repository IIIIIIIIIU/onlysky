#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=4e5+5;
const int maxtree=maxn<<2|1;
struct node
{
	int x,y;
	node(){}
	node(int x_,int y_)
	{
		x=x_;
		y=y_;
	}
	inline bool operator<(const node &tmp)const
	{
		if(x==tmp.x)
			return y<tmp.y;
		return x<tmp.x;
	}
	inline ll operator*(const node &tmp)const
	{
		return 1LL*x*tmp.x+1LL*y*tmp.y;
	}
	inline node operator-(const node &tmp)const
	{
		return node(x-tmp.x,y-tmp.y);
	}
	inline ll operator&(const node &tmp)const
	{
		return 1LL*x*tmp.y-1LL*y*tmp.x;
	}
};
struct node p[maxn];
int stack[maxn],top;
inline bool compareUp(const node &base,const node &x,const node &y)
{
	//return 1LL*(base.y-y.y)*(base.x-y.x)<1LL*(base.y-x.y)*(base.x-x.x);
	return ((base-y)&(x-y))<0;
}
inline bool compareDown(const node &base,const node &x,const node &y)
{
	//return 1LL*(base.y-y.y)*(base.x-y.x)>1LL*(base.y-x.y)*(base.x-x.x);
	return ((base-y)&(x-y))>0;
}
struct G
{
	int len,uplen,downlen;
	std::vector<node>up,down;
	void add(node x)
	{
		up.push_back(x);
		++len;
	}
	void makeit()
	{
		if(len==1)
		{
			uplen=1;
			downlen=1;
			down.push_back(up[0]);
			return;
		}
		std::sort(up.begin(),up.end());
		for(int i=0;i<len;i++)
			p[i]=up[i];
		stack[top=1]=0;
		stack[top=2]=1;
		for(int i=2;i<len;i++)
		{
			while(compareUp(p[i],p[stack[top]],p[stack[top-1]]))
				top--;
			stack[++top]=i;
		}
		for(int i=1;i<=top;i++)
			up[uplen++]=p[stack[i]];
		stack[top=1]=0;
		stack[top=2]=1;
		for(int i=2;i<len;i++)
		{
			while(compareDown(p[i],p[stack[top]],p[stack[top-1]]))
				top--;
			stack[++top]=i;
		}
		for(int i=1;i<=top;i++)
		{
			down.push_back(p[stack[i]]);
			downlen++;
		}
	}
	ll query(node x)
	{
		if(x.y>=0)
		{
			int l=0,r=uplen-1,mid1,mid2;
			while(r-l>2)
			{
				mid1=(l*2+r)/3;
				mid2=(l+r*2)/3;
				if(up[mid1]*x>up[mid2]*x)
					r=mid2;
				else
					l=mid1;
			}
			ll res=-1e18;
			for(int i=l;i<=r;i++)
				res=std::max(up[i]*x,res);
			return res;
		}
		else
		{
			int l=0,r=downlen-1,mid1,mid2;
			while(r-l>2)
			{
				mid1=(l*2+r)/3;
				mid2=(l+r*2)/3;
				if(down[mid1]*x>down[mid2]*x)
					r=mid2;
				else
					l=mid1;
			}
			ll res=-1e18;
			for(int i=l;i<=r;i++)
				res=std::max(res,down[i]*x);
			return res;
		}
	}
};
struct G g[maxtree];
int n,L[maxtree],R[maxtree],mid[maxtree];
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
void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	if(l==r)
		return;
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
}
inline void update(int now,int to,node x)
{
	g[now].add(x);
	if(g[now].len==R[now]-L[now]+1)
		g[now].makeit();
	if(L[now]==R[now])
		return;
	if(to<=mid[now])
		update(now<<1,to,x);
	else
		update(now<<1|1,to,x);
}
inline ll query(int now,int l,int r,node x)
{
	if(L[now]>=l&&R[now]<=r)
		return g[now].query(x);
	ll res=-1e18;
	if(l<=mid[now])
		res=query(now<<1,l,r,x);
	if(r>mid[now])
		res=std::max(query(now<<1|1,l,r,x),res);
	return res;
}
inline void decode(int &x,const ll lastans)
{
	x^=(lastans&0x7fffffff);
}
int main()
{
	read(n);
	char op[2];
	bool online;
	scanf("%s",op);
	if(op[0]!='E')
		online=true;
	else
		online=false;
	build(1,1,4e5);
	int x,y,l,r,tot=0;
	ll lastans=0;
	while(n--)
	{
		scanf("%s",op);
		if(op[0]=='A')
		{
			read(x);
			read(y);
			if(online)
			{
				decode(x,lastans);
				decode(y,lastans);
			}
			update(1,++tot,node(x,y));
		}
		else
		{
			read(x);
			read(y);
			read(l);
			read(r);
			if(online)
			{
				decode(l,lastans);
				decode(r,lastans);
				decode(x,lastans);
				decode(y,lastans);
			}
			lastans=query(1,l,r,node(x,y));
			printf("%lld\n",lastans);
		}
	}
	return 0;
}
