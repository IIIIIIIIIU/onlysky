#include <bitset>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=3e4+5;

int n,m,head[maxn],E[maxn<<2],V[maxn<<2],cnt;
int ans,tag[maxn],que[maxn],order[maxn],num;
int seq[maxn];

std::bitset<maxn>bit[maxn];

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
	return order[a]>order[b];
}

inline bool compare_(const int &a,const int &b)
{
	return order[a]<order[b];
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1,u,v;i<=m;i++)
	{
		read(u);
		read(v);
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		tag[v]++;
	}
	int h=1,tail=1,now;
	for(int i=1;i<=n;i++)
		if(!tag[i])
			que[tail++]=i;
	while(h<tail)
	{
		now=que[h++];
		order[now]=++num;
		for(int i=head[now];i!=0;i=E[i])
			if(!(--tag[V[i]]))
				que[tail++]=V[i];
	}
	std::sort(que+1,que+n+1,compare);
	for(int v=1;v<=n;v++)
	{
		h=0;
		now=que[v];
		bit[now][now]=1;
		for(int i=head[now];i!=0;i=E[i])
			seq[++h]=V[i];
		std::sort(seq+1,seq+h+1,compare_);
		for(int i=1;i<=h;i++)
			if(bit[now][seq[i]])
				++ans;
			else
				bit[now]|=bit[seq[i]];
	}
	std::cout<<ans<<std::endl;
	return 0;
}
