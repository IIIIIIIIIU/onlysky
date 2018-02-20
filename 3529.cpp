#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e5+5;
const int maxq=2e4+5;
struct Fnode
{
	int id,x;
	inline bool operator<(const Fnode &tmp)const
	{
		return x<tmp.x;
	}
};
struct Fnode ki[maxn];
struct QueryType
{
	int n,m,a,id;
	inline bool operator<(const QueryType &tmp)const
	{
		return a<tmp.a;
	}
};
struct QueryType query[maxq];
int Q,n,m,F[maxn],mu[maxn],pi[maxn],num,tree[maxn],ans,out[maxn];
bool vis[maxn];
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
void pre()
{
	mu[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			mu[i]=-1;
		}
		for(int v=1;v<=num&&pi[v]*i<maxn;v++)
		{
			vis[pi[v]*i]=true;
			if(i%pi[v]==0)
				break;
			mu[i*pi[v]]=-mu[i];
		}
	}
}
inline void add(int to,int x)
{
	while(to<maxn)
	{
		tree[to]+=x;
		to+=(to&(-to));
	}
}
inline int get(int to)
{
	int res=0;
	while(to)
	{
		res+=tree[to];
		to-=(to&(-to));
	}
	return res;
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	pre();
	for(int i=1;i<maxn;i++)
		for(int v=1;i*v<maxn;v++)
			F[v*i]+=i;
	for(int i=1;i<maxn;i++)
	{
		ki[i].id=i;
		ki[i].x=F[i];
	}
	std::sort(ki+1,ki+maxn);
	read(Q);
	for(int i=1;i<=Q;i++)
	{
		read(query[i].n);
		read(query[i].m);
		read(query[i].a);
		query[i].id=i;
		if(query[i].n>query[i].m)
			std::swap(query[i].n,query[i].m);
	}
	std::sort(query+1,query+Q+1);
	int p=1;
	for(int i=1;i<=Q;i++)
	{
		while(p<maxn&&ki[p].x<=query[i].a)
		{
			for(int v=1;v*ki[p].id<maxn;v++)
				add(v*ki[p].id,ki[p].x*mu[v]);
			p++;
		}
		n=query[i].n;
		m=query[i].m;
		ans=0;
		for(int v=1,nxt;v<=n;v=nxt+1)
		{
			nxt=std::min(n/(n/v),m/(m/v));
			ans+=(get(nxt)-get(v-1))*(n/v)*(m/v);
		}
		out[query[i].id]=ans;
	}
	for(int i=1;i<=Q;i++)
		printf("%d\n",out[i]&0x7fffffff);
	return 0;
}
