#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=200005;

struct list
{
	int val,pre,suf;
};

struct list ai[maxn];

struct node
{
	int val,id;

	bool operator<(const node &tmp)const
	{
		if(val==tmp.val) return id>tmp.id;
		else return val<tmp.val;
	}
	
	bool operator==(const node &tmp)const
	{
		return val==tmp.val&&id==tmp.id;
	}

	node(int val_,int id_)
	{
		val=val_,id=id_;
	}
};

int n,m,bi[maxn],ans;

bool vis[maxn];

std::priority_queue<node>que;

inline void read(int &now)
{
	char Cget;now=0;int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')if(Cget=='-')if_z=-1;
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
	now*=if_z;
}

int main()
{
//	freopen("nt2011_tree.in","r",stdin);
//	freopen("nt2011_tree.out","w",stdout);
//	freopen("data.txt","r",stdin);
	read(n),read(m);
	if((m<<1)>n)
	{
		puts("Error!");
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		read(bi[i]);
		ai[i].val=bi[i];
		if(i==1) ai[i].pre=n;
		else ai[i].pre=i-1;
		if(i==n) ai[i].suf=1;
		else ai[i].suf=i+1;
		que.push(node(ai[i].val,i));
	}
	while(m--)
	{
		while(vis[que.top().id]) que.pop();
		node now=que.top();que.pop();
		ans+=now.val;
		ai[now.id].val=now.val=ai[ai[now.id].pre].val+ai[ai[now.id].suf].val-now.val;
		vis[ai[now.id].pre]=true;
		vis[ai[now.id].suf]=true;
		ai[now.id].pre=ai[ai[now.id].pre].pre;
		ai[now.id].suf=ai[ai[now.id].suf].suf;
		ai[ai[now.id].pre].suf=now.id;
		ai[ai[now.id].suf].pre=now.id;
		que.push(now);
	}
	std::cout<<ans;
	return 0;
}
