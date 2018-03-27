#include <set>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e5+5;

int n,val[maxn],f[maxn],seq[maxn],head[maxn],bel[maxn];
int E[maxn<<1|1],V[maxn<<1|1],cnt,tot,id[maxn],size[maxn];

std::multiset<int>Set[maxn];

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

inline bool compare(int a,int b)
{
	return size[a]>size[b];
}

void dfs(int now)
{
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=f[now])
			dfs(V[i]);
	int t=0;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=f[now])
			seq[++t]=bel[V[i]];
	if(!t)
	{
		bel[now]=++cnt;
		size[bel[now]]=1;
		Set[bel[now]].insert(val[now]);
	}
	else
	{
		std::sort(seq+1,seq+t+1,compare);
		bel[now]=seq[1];
		for(int i=2;i<=t;i++)
			for(std::multiset<int>::iterator it=Set[seq[i]].begin();it!=Set[seq[i]].end();++it)
			{
				Set[bel[now]].insert(*it);
				size[bel[now]]++;
			}
		std::multiset<int>::iterator it=Set[bel[now]].lower_bound(val[now]);
		if(it!=Set[bel[now]].end())
		{
			Set[bel[now]].erase(it);
			size[bel[now]]--;
		}
		Set[bel[now]].insert(val[now]);
		size[bel[now]]++;
	}
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	for(int i=1,u,v;i<=n;i++)
	{
		read(val[i]);
		read(f[i]);
		if(f[i])
		{
			u=f[i];
			v=i;
			E[++cnt]=head[u];
			V[cnt]=v;
			head[u]=cnt;
			E[++cnt]=head[v];
			V[cnt]=u;
			head[v]=cnt;
		}
	}
	cnt=0;
	dfs(1);
	std::cout<<Set[bel[1]].size()<<std::endl;
	return 0;
}
