#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int mod=2e6+5;
const int maxn=2e6+5;

struct node
{
	int data[11];
	
	ll HashVal;
	
	node()
	{
		HashVal=-1;
		for(short v=0;v<=10;v++)
			data[v]=0;
	}
	
	inline ll getVal(int len)
	{
		HashVal=0;
		for(int i=1;i<=len;i++)
			HashVal=(HashVal*11+data[i])%mod;
		return HashVal;
	}
	
	inline bool operator==(const node &tmp)const
	{
		for(int v=1;v<=10;v++)
			if(tmp.data[v]!=data[v])
				return false;
		return true;
	}
};

struct node pi[200005],hV[maxn];

int n,m,ai[11][11],bi[11][11],tot,hhead[maxn],hE[maxn],hI[maxn];
int head[maxn],E[maxn<<1|1],V[maxn<<1|1],Wa[maxn<<1|1],du[maxn],hcnt;
int cnt,Wb[maxn<<1|1],que[maxn],dp[maxn][2];

bool vis[maxn][2];

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

void dfs(int now,int tmp,node t)
{
	t.data[now]=tmp;
	if(now>=n)
	{
		pi[++tot]=t;
		return;
	}
	for(int v=0;v<=tmp;v++)
		dfs(now+1,v,t);
}

inline void edge_add(node t,int v)
{
	int u=t.getVal(n);
	hE[++hcnt]=hhead[u];
	hV[hcnt]=t;
	hI[hcnt]=v;
	hhead[u]=hcnt;
}

inline int query(node t)
{
	ll tmp=t.getVal(n);
	for(int i=hhead[tmp];i!=0;i=hE[i])
		if(hV[i]==t)
			return hI[i];
	return 0;
}

inline void edge_add(int u,int v,int wa,int wb)
{
	du[u]++;
	E[++cnt]=head[v];
	V[cnt]=u;
	Wa[cnt]=wa;
	Wb[cnt]=wb;
	head[v]=cnt;
}

void build()
{
	node t;
	for(int i=1;i<=tot;i++)
	{
		node t=pi[i];
		if(t.data[1]<m)
		{
			t.data[1]++;
			edge_add(i,query(t),ai[1][t.data[1]],bi[1][t.data[1]]);
			t.data[1]--;
		}
		for(int v=2;v<=n;v++)
			if(t.data[v]<t.data[v-1])
			{
				t.data[v]++;
				edge_add(i,query(t),ai[v][t.data[v]],bi[v][t.data[v]]);
				t.data[v]--;
			}
	}
}

inline void update(int x,int y,int c)
{
	if(!vis[x][y])
	{
		vis[x][y]=true;
		dp[x][y]=c;
	}
	else
	{
		if(y==0)
			dp[x][y]=std::max(dp[x][y],c);
		else
			dp[x][y]=std::min(dp[x][y],c);
	}
}

int main()
{
	read(n);
	read(m);
	node st;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			read(ai[i][v]);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			read(bi[i][v]);
	for(int i=0;i<=m;i++)
		dfs(1,i,st);
	for(int i=1;i<=tot;i++)
		edge_add(pi[i],i);
	build();
	int h=0,tail=0,now,INF=dp[0][0];
	for(int i=1;i<=tot;i++)
		if(!du[i])
		{
			que[tail++]=i;
			dp[i][(n*m)%2]=0;
			vis[i][(n*m)%2]=true;
		}
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
		{
			if(!(--du[V[i]]))
				que[tail++]=V[i];
			if(vis[now][0])
				update(V[i],1,dp[now][0]-Wb[i]);
			if(vis[now][1])
				update(V[i],0,dp[now][1]+Wa[i]);
		}
	}
	std::cout<<dp[1][0]<<std::endl;
	return 0;
}
