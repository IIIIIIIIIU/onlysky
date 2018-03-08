#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e5+5;
const int maxtree=maxn<<2|1;

struct node
{
	int l,r,Max,len;
	
	node()
	{
		l=0;
		r=0;
		Max=0;
		len=0;
	}
	
	node(int l_,int r_,int len_)
	{
		l=l_;
		r=r_;
		len=len_;
		Max=0;
	}
	
	node operator+(const node &tmp)const
	{
		node res(l,tmp.r,len+tmp.len);
		if(res.l==len)
			res.l+=tmp.l;
		if(res.r==tmp.len)
			res.r+=r;
		res.Max=std::max(std::max(Max,tmp.Max),std::max(r+tmp.l,std::max(res.l,res.r)));
		return res;
	}
	
	void reset(int x)
	{
		int t=x*len;
		l=t;
		r=t;
		Max=t;
	}
};

struct node val[maxtree];

int n,m,L[maxtree],R[maxtree],mid[maxtree],sum[maxtree];
int tag[maxtree];

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

void build(int now,int l,int r)
{
	L[now]=l;
	R[now]=r;
	sum[now]=r-l+1;
	val[now].len=r-l+1;
	if(l==r)
		return;
	mid[now]=l+r>>1;
	build(now<<1,l,mid[now]);
	build(now<<1|1,mid[now]+1,r);
}

inline void pushDown(int now)
{
	if(tag[now]==1)
	{
		tag[now<<1]=1;
		tag[now<<1|1]=1;
		sum[now<<1]=0;
		sum[now<<1|1]=0;
		val[now<<1].reset(1);
		val[now<<1|1].reset(1);
	}
	else
	{
		tag[now<<1]=2;
		tag[now<<1|1]=2;
		sum[now<<1]=val[now<<1].len;
		sum[now<<1|1]=val[now<<1|1].len;
		val[now<<1].reset(0);
		val[now<<1|1].reset(0);
	}
	tag[now]=0;
}

void upDateSetFalse(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
	{
		sum[now]=0;
		tag[now]=1;
		val[now].reset(1);
		return;
	}
	if(tag[now])
		pushDown(now);
	if(l<=mid[now])
		upDateSetFalse(now<<1,l,r);
	if(r>mid[now])
		upDateSetFalse(now<<1|1,l,r);
	sum[now]=sum[now<<1]+sum[now<<1|1];
	val[now]=val[now<<1]+val[now<<1|1];
}

void upDateSetTrue(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
	{
		tag[now]=2;
		val[now].reset(0);
		sum[now]=val[now].len;
		return;
	}
	if(tag[now])
		pushDown(now);
	if(l<=mid[now])
		upDateSetTrue(now<<1,l,r);
	if(r>mid[now])
		upDateSetTrue(now<<1|1,l,r);
	sum[now]=sum[now<<1]+sum[now<<1|1];
	val[now]=val[now<<1]+val[now<<1|1];
}

int querySum(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
		return sum[now];
	if(tag[now])
		pushDown(now);
	int res=0;
	if(l<=mid[now])
		res+=querySum(now<<1,l,r);
	if(r>mid[now])
		res+=querySum(now<<1|1,l,r);
	return res;
}

node queryVal(int now,int l,int r)
{
	if(L[now]>=l&&R[now]<=r)
		return val[now];
	if(tag[now])
		pushDown(now);
	node res;
	bool DID=false;
	if(l<=mid[now])
	{
		res=queryVal(now<<1,l,r);
		DID=true;
	}
	if(r>mid[now])
	{
		if(DID)
			res=res+queryVal(now<<1|1,l,r);
		else
			res=queryVal(now<<1|1,l,r);
	}
	return res;
}

int queryPos(int now,int x)
{
	if(L[now]==R[now])
	{
		if(x>=1)
			return L[now];
		else
			return 0;
	}
	if(tag[now])
		pushDown(now);
	if(x<=val[now<<1].len-sum[now<<1])
		return queryPos(now<<1,x);
	else
		return queryPos(now<<1|1,x-(val[now<<1].len-sum[now<<1]));
}

int main()
{
	read(n);
	read(m);
	build(1,1,n);
	int op,l,r,x,l0,r0,l1,r1,t;
	while(m--)
	{
		read(op);
		if(op==0)
		{
			read(l);
			read(r);
			upDateSetFalse(1,l,r);
		}
		else if(op==1)
		{
			read(l0);
			read(r0);
			read(l1);
			read(r1);
			x=querySum(1,l0,r0);
			upDateSetFalse(1,l0,r0);
			t=0;
			if(l1>1)
				t+=l1-1-querySum(1,1,l1-1);
			t=queryPos(1,x+t);
			if(t>=l1)
				upDateSetTrue(1,l1,std::min(t,r1));
		}
		else
		{
			read(l);
			read(r);
			printf("%d\n",queryVal(1,l,r).Max);
		}
	}
	return 0;
}
