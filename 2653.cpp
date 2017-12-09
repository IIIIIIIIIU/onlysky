#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e5+5;
const int maxtree=maxn*20;

struct point
{
	int v,p;
	
	point(){}
	
	point(int v_,int p_)
	{
		v=v_;
		p=p_;
	}
	
	bool operator<(const point &tmp)const
	{
		return v<tmp.v;
	}
};

struct point vi[maxn];

struct node
{
	int l,r,sum;
	
	node(){}
	
	node(int l_,int r_,int sum_)
	{
		l=l_;
		r=r_;
		sum=sum_;
	}
	
	node operator+(const node &tmp)const
	{
		node res(l,tmp.r,sum+tmp.sum);
		if(sum+tmp.l>res.l)
			res.l=tmp.l+sum;
		if(tmp.sum+r>res.r)
			res.r=r+tmp.sum;
		return res;
	}
};

struct node val[maxtree];

int n,ai[maxn],bi[maxn],size,root[maxn],tot,ch[maxtree][2],q;

inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}

void build(int &now,int l,int r)
{
	now=++tot;
	if(l==r)
	{
		val[now]=node(1,1,1);
		return;
	}
	int mid=l+r>>1;
	build(ch[now][0],l,mid);
	build(ch[now][1],mid+1,r);
	val[now]=val[ch[now][0]]+val[ch[now][1]];
}

void add(int &now,int pre,int l,int r,int to)
{
	now=++tot;
	if(l==r)
	{
		val[now]=node(0,0,-1);
		return;
	}
	int mid=l+r>>1;
	if(to<=mid)
	{
		add(ch[now][0],ch[pre][0],l,mid,to);
		ch[now][1]=ch[pre][1];
	}
	else
	{
		add(ch[now][1],ch[pre][1],mid+1,r,to);
		ch[now][0]=ch[pre][0];
	}
	val[now]=val[ch[now][0]]+val[ch[now][1]];
}

node query(int now,int l,int r,int tl,int tr)
{
	if(l>=tl&&r<=tr)
		return val[now];
	node res;
	bool DID=false;
	int mid=l+r>>1;
	if(tl<=mid)
	{
		res=query(ch[now][0],l,mid,tl,tr);
		DID=true;
	}
	if(tr>mid)
		if(DID)
			res=res+query(ch[now][1],mid+1,r,tl,tr);
		else
			res=query(ch[now][1],mid+1,r,tl,tr);
	return res;
}

int main()
{
//	freopen("nt2012_middle.in","r",stdin);
//	freopen("nt2012_middle.out","w",stdout);
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
		vi[i]=point(ai[i],i);
	}
	std::sort(vi+1,vi+n+1);
	build(root[0],1,n);
	int p=1;
	for(int i=1;i<=size;i++)
	{
		root[i]=root[i-1];
		while(p<=n&&vi[p].v<i)
		{
			add(root[i],root[i],1,n,vi[p].p);
			p++;
		}
	}
	read(q);
	node a1,a2,a3;
	int l,r,mid,res;
	for(int i=1,qi[5],last=0;i<=q;i++)
	{
		for(int v=1;v<=4;v++)
		{
			read(qi[v]);
			qi[v]=(qi[v]+last)%n+1;
		}
		std::sort(qi+1,qi+5);
		l=1;
		r=size;
		mid=l+r>>1;
		while(l<r)
		{
			a2=query(root[mid],1,n,qi[2],qi[3]);
			a3=query(root[mid],1,n,qi[3]+1,qi[4]);
			a1=query(root[mid],1,n,qi[1],qi[2]-1);
			if(a1.r+a2.sum+a3.l>=0)
				l=mid;
			else
				r=mid-1;
			mid=l+r+1>>1;
		}
		last=bi[mid];
		printf("%d\n",last);
	}
	return 0;
}
