#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e7+5;
const int INF=0x3f3f3f3f;

int n,m,T,C,ai[205][205],bi[maxn],si[maxn];
int head[maxn],E[maxn],V[maxn],cnt,ans[maxn];
int F[maxn],deep[maxn],que[maxn],s,t,Sum[maxn];

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

inline void edge_add(int u,int v,int f)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	F[cnt]=f;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	F[cnt]=0;
	head[v]=cnt;
}

inline bool bfs()
{
	for(int i=s;i<=t;i++)
		deep[i]=-1;
	deep[s]=0;
	int h=0,tail=1,now;
	que[h]=s;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
			if(F[i]>0&&deep[V[i]]<0)
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	}
	return false;
}

inline int dfs(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(F[i]>0&&deep[V[i]]==deep[now]+1)
		{
			tmp=dfs(V[i],std::min(flow,F[i]));
			F[i]-=tmp;
			F[i^1]+=tmp;
			flow-=tmp;
			oldflow+=tmp;
			if(!flow)
				return oldflow;
		}
	if(flow)
		deep[now]=-1;
	return oldflow;
}

inline bool check(int lit,int pos)
{
	for(int i=s;i<=t;i++)
		head[i]=0;
	cnt=1;
	for(int i=1;i<=n;i++)
		edge_add(s,i,1);
	for(int i=1;i<=m;i++)
		edge_add(i+n,t,bi[i]);
	for(int i=1;i<=lit;i++)
	{
		for(int v=1;v<=m;v++)
			if(ai[i][v]==ans[i])
				edge_add(i,v+n,1);
	}
	for(int i=1;i<=m;i++)
		if(ai[pos][i]&&ai[pos][i]<=si[pos])
			edge_add(pos,i+n,1);
	int tmp=0;
	while(bfs())
		tmp+=dfs(s,INF);
	return tmp>Sum[lit];
}

int main()
{
	freopen("data.txt","r",stdin);
	read(T);
	read(C);
	while(T--)
	{
		read(n);
		read(m);
		for(int i=1;i<=m;i++)
			read(bi[i]);
		for(int i=1;i<=n;i++)
			for(int v=1;v<=m;v++)
				read(ai[i][v]);
		for(int i=1;i<=n;i++)
			read(si[i]);
		s=0;
		cnt=1;
		t=n+m+1;
		for(int i=s;i<=t;i++)
			head[i]=0;
		int tmp=0;
		for(int i=1;i<=m;i++)
			edge_add(i+n,t,bi[i]);
		for(int i=1;i<=n;i++)
		{
			ans[i]=m+1;
			edge_add(s,i,1);
			for(int v=1;v<=m;v++)
			{
				for(int e=1;e<=m;e++)
					if(ai[i][e]==v)
						edge_add(i,e+n,1);
				tmp=0;
				if(bfs())
					tmp=dfs(s,INF);
				if(tmp)
				{
					ans[i]=v;
					break;
				}
			}
			Sum[i]=Sum[i-1]+(m+1!=ans[i]);
			printf("%d ",ans[i]);
		}
		printf("\n");
		for(int i=1;i<=n;i++)
		{
			if(i==n-2)
			{
				int qwe=0;
			}
			if(ans[i]<=si[i])
			{
				printf("0 ");
				continue;
			}
			int l=0,r=i-1,mid,res=i;
			while(l<=r)
			{
				mid=l+r>>1;
				if(check(mid,i))
				{
					res=i-mid-1;
					l=mid+1;
				}
				else
					r=mid-1;
			}
			printf("%d ",res);
		}
		putchar('\n');
	}
	return 0;
}
