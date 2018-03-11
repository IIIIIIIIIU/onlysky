#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;

const ll mod=998244353;
const int maxn=1e4+5;
const int INF=0x3f3f3f3f;

struct node
{
	int size;
	
	ll Hash;
	
	bool operator<(const node &tmp)const
	{
		if(size==tmp.size)
			return Hash<tmp.Hash;
		return size<tmp.size;
	}
	
	bool operator==(const node &tmp)const
	{
		return Hash==tmp.Hash&&size==tmp.size;
	}
};

struct node Ans[maxn];

struct EdgeType
{
	int u,v;
	
	EdgeType(){}
	
	EdgeType(int u_,int v_)
	{
		u=u_;
		v=v_;
	}
};

struct EdgeType edge[maxn];

int n,m,head[maxn],E[maxn<<1],V[maxn<<1],cnt;
int num,treeSize[maxn],deg[maxn],bel[maxn],f[maxn];
int root[maxn],SIZE,seq[maxn],ans,size[maxn],lar[maxn];

bool vis[maxn];

ll Hash[maxn],hpos[maxn];

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

inline void edge_add(int u,int v)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	head[v]=cnt;
}

void dfs(int now,int fa)
{
	f[now]=fa;
	bel[now]=0;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs(V[i],now);
}

void findRoot(int now,int fa)
{
	lar[now]=0;
	size[now]=1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			findRoot(V[i],now);
			size[now]+=size[V[i]];
			if(size[V[i]]>lar[now])
				lar[now]=size[V[i]];
		}
	if(SIZE-size[now]>lar[now])
		lar[now]=SIZE-size[now];
	if(!num)
		root[++num]=now;
	else if(lar[now]<lar[root[1]])
		root[num=1]=now;
	else if(lar[now]==lar[root[1]])
		root[++num]=now;
}

inline bool compare(const int &a,const int &b)
{
	return Hash[a]>Hash[b];
}

void dfsHash(int now,int fa)
{
	Hash[now]=233;
	size[now]=1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			dfsHash(V[i],now);
			size[now]+=size[V[i]];
		}
	int t=0;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			seq[++t]=V[i];
	if(!t)
		return;
	std::sort(seq+1,seq+t+1,compare);
	for(int i=1;i<=t;i++)
		Hash[now]=Hash[now]*mod+Hash[seq[i]];
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	hpos[0]=1;
	for(int i=1;i<maxn;i++)
		hpos[i]=hpos[i-1]*mod;
	read(m);
	lar[0]=INF;
	for(int i=1;i<=m;i++)
	{
		read(n);
		for(int v=1;v<=n;v++)
		{
			vis[v]=0;
			deg[v]=0;
			head[v]=0;
		}
		cnt=0;
		num=0;
		for(int e=1,u,v;e<n;e++)
		{
			read(u);
			read(v);
			edge_add(u,v);
			deg[u]++;
			deg[v]++;
		}
		for(int v=1;v<=n;v++)
			vis[v]=(deg[v]==2);
		dfs(1,0);
		int s=0;
		for(int v=1;v<=n;v++)
			if(!vis[v])
			{
				s=v;
				treeSize[i]++;
				int t=f[v];
				while(t)
				{
					if(!vis[t])
					{
						edge[++num]=EdgeType(t,v);
						break;
					}
					if(vis[t]&&bel[t])
					{
						edge[++num]=EdgeType(bel[t],v);
						break;
					}
					bel[t]=v;
					t=f[t];
				}
			}
		cnt=0;
		SIZE=treeSize[i];
		for(int e=1;e<=n;e++)
			head[e]=0;
		for(int e=1;e<=num;e++)
			edge_add(edge[e].u,edge[e].v);
		num=0;
		if(s)
		{
			findRoot(s,0);
			if(num==1)
			{
				dfsHash(root[1],0);
				++ans;
				Ans[ans].size=treeSize[i];
				Ans[ans].Hash=Hash[root[1]];
			}
			else
			{
				dfsHash(root[1],root[2]);
				dfsHash(root[2],root[1]);
				ll tmpHash=233;
				if(Hash[root[1]]>Hash[root[2]])
					std::swap(root[1],root[2]);
				tmpHash=tmpHash*mod+Hash[root[1]];
				tmpHash=tmpHash*mod+Hash[root[2]];
				++ans;
				Ans[ans].size=treeSize[i];
				Ans[ans].Hash=tmpHash;
			}
		}
		else
		{
			++ans;
			Ans[ans].size=0;
			Ans[ans].Hash=0;
		}
	}
	std::sort(Ans+1,Ans+ans+1);
	ans=std::unique(Ans+1,Ans+ans+1)-Ans-1;
	printf("%d\n",ans);
	for(int i=1;i<ans;i++)
		printf("%d ",Ans[i].size);
	printf("%d",Ans[ans].size);
	return 0;
}
