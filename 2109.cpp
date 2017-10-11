#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2005,maxm=100005;

struct node
{
	int id,key;
	
	node(int id_=0,int key_=0)
	{
		id=id_,key=key_;
	}
	
	bool operator<(const node &tmp)const
	{
		return key<tmp.key;
	}
};

int n,m,basedeg[maxn],head[maxn],E[maxm],V[maxm],ki[maxn];
int cnt,deg[maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

using std::priority_queue;

int solve(int tag)
{
	priority_queue<node>que;
	node now;
	for(int i=1;i<=n;i++)
	{
		deg[i]=basedeg[i];
		if(!deg[i]&&i!=tag) que.push(node(i,ki[i]));
	}
	for(int i=n;i>=1;i--)
	{
		if(!que.size()) return i;
		now=que.top(),que.pop();
		if(now.key<i) return i;
		for(int i=head[now.id];i;i=E[i])
			if(V[i]!=tag)
				if(!(--deg[V[i]])) que.push(node(V[i],ki[V[i]]));
	}
}

int main()
{
//	freopen("plane.in","r",stdin);
//	freopen("plane.out","w",stdout);
	read(n),read(m);
	for(int i=1;i<=n;i++) read(ki[i]);
	int u,v;
	for(int i=1;i<=m;i++)
	{
		read(u),read(v);
		++basedeg[u];
		E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
	}
	for(int i=1;i<=n;i++)
		if(i==n) printf("%d",solve(i));
		else printf("%d ",solve(i));
	return 0;
}
