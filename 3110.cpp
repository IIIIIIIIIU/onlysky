#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned int uint;
const int maxn=5e4+5;
const int maxtree=maxn<<2|1;
const int maxtree2=maxn*400;
struct operation
{
	int op,a,b,c;
};
struct operation oper[maxn];
int n,m,ai[maxn],num,ch[maxtree2][2],root[maxtree],tot,L[maxtree],R[maxtree];
int mid[maxtree];
uint val[maxtree2],tag[maxtree2];
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
inline void pushdown(int now,int l,int r)
{
	if(!ch[now][0])
		ch[now][0]=++tot;
	if(!ch[now][1])
		ch[now][1]=++tot;
	int Mid=l+r>>1;
	val[ch[now][0]]+=(Mid-l+1)*tag[now];
	val[ch[now][1]]+=(r-Mid)*tag[now];
	tag[ch[now][0]]+=tag[now];
	tag[ch[now][1]]+=tag[now];
	tag[now]=0;
}
inline void ADD(int &now,int l,int r,int tl,int tr)
{
	if(!now)
		now=++tot;
	if(l>=tl&&r<=tr)
	{
		val[now]+=r-l+1;
		tag[now]++;
		return;
	}
	if(tag[now])
		pushdown(now,l,r);
	int Mid=l+r>>1;
	if(tl<=Mid)
		ADD(ch[now][0],l,Mid,tl,tr);
	if(tr>Mid)
		ADD(ch[now][1],Mid+1,r,tl,tr);
	val[now]=val[ch[now][0]]+val[ch[now][1]];
}
inline uint QUERY(int now,int l,int r,int tl,int tr)
{
	if(!now)
		return 0;
	if(l>=tl&&r<=tr)
		return val[now];
	if(tag[now])
		pushdown(now,l,r);
	uint Mid=l+r>>1,res=0;
	if(tl<=Mid)
		res+=QUERY(ch[now][0],l,Mid,tl,tr);
	if(tr>Mid)
		res+=QUERY(ch[now][1],Mid+1,r,tl,tr);
	return res;
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
inline void add(int now,int to,int a,int b)
{
	ADD(root[now],1,n,a,b);
	if(L[now]==R[now])
		return;
	if(to<=mid[now])
		add(now<<1,to,a,b);
	else
		add(now<<1|1,to,a,b);
}
inline int query(int now,int a,int b,int c)
{
	if(L[now]==R[now])
		return ai[L[now]];
	uint tmp=QUERY(root[now<<1|1],1,n,a,b);
	if(tmp>=c)
		return query(now<<1|1,a,b,c);
	else
		return query(now<<1,a,b,c-tmp);
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1;i<=m;i++)
	{
		read(oper[i].op);
		read(oper[i].a);
		read(oper[i].b);
		read(oper[i].c);
		if(oper[i].op==1)
			ai[++num]=oper[i].c;
	}
	std::sort(ai+1,ai+num+1);
	num=std::unique(ai+1,ai+num+1)-ai-1;
	for(int i=1;i<=m;i++)
		if(oper[i].op==1)
			oper[i].c=std::lower_bound(ai+1,ai+num+1,oper[i].c)-ai;
	build(1,1,num);
	for(int i=1;i<=m;i++)
		if(oper[i].op==1)
			add(1,oper[i].c,oper[i].a,oper[i].b);
		else
			printf("%d\n",query(1,oper[i].a,oper[i].b,oper[i].c));
	return 0;
}
