#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e6+5;

int n,m,size[maxn],deep[maxn],head[maxn],E[maxn];
int V[maxn],cnt,val[maxn],ans,seq[maxn];

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

inline bool compare(const int &a,const int &b)
{
	return val[a]<val[b];
}

void dfs(int now)
{
	for(int i=head[now];i!=0;i=E[i])
		dfs(V[i]);
	int t=0;
	for(int i=head[now];i!=0;i=E[i])
		seq[++t]=V[i];
	std::sort(seq+1,seq+t+1,compare);
	for(int i=1;i<=t;i++)
		if(val[now]+val[seq[i]]-1<=m)
		{
			val[now]+=val[seq[i]]-1;
			ans++;
		}
		else
			break;
}

int main()
{
	read(n);
	read(m);
	for(int i=0;i<n;i++)
		read(val[i]);
	for(int i=0,t,v,pos;i<n;i++)
	{
		read(t);
		val[i]+=t;
		for(v=1;v<=t;v++)
		{
			read(pos);
			E[++cnt]=head[i];
			V[cnt]=pos;
			head[i]=cnt;
		}
	}
	dfs(0);
	std::cout<<ans<<std::endl;
	return 0;
}
