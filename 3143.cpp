#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=505;
const real eps=1e-10;

struct EdgeType
{
	int u,v;
	
	real prob;
	
	bool operator<(const EdgeType &tmp)const
	{
		return prob>tmp.prob;
	}
};

struct EdgeType edge[maxn*maxn];

int n,m,head[maxn],E[maxn*maxn],V[maxn*maxn],cnt;

real g[maxn],f[maxn][maxn];

inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
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

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	for(int i=1;i<=m;i++)
	{
		read(edge[i].u);
		read(edge[i].v);
		g[edge[i].u]+=1;
		g[edge[i].v]+=1;
		edge_add(edge[i].u,edge[i].v);
	}
	for(int i=1;i<n;i++)
	{
		f[i][i]=1;
		for(int v=head[i];v!=0;v=E[v])
			if(V[v]!=n)
				f[i][V[v]]=-1.0/g[V[v]];
	}
	f[1][n]=1;
	for(int i=1;i<n;i++)
	{
		real tmp;
		int pos=i;
		for(int v=i+1;v<n;v++)
			if(f[v][i]-f[pos][i]>eps)
				pos=v;
		if(pos!=i)
			for(int v=i;v<=n;v++)
				std::swap(f[i][v],f[pos][v]);
		for(int v=i+1;v<n;v++)
		{
			if(f[v][i]>eps||f[v][i]<-eps)
			{
				tmp=f[v][i]/f[i][i];
				for(int k=i;k<=n;k++)
					f[v][k]-=f[i][k]*tmp;
			}
		}
	}
	for(int i=n-1;i>=1;i--)
	{
		for(int k=i+1;k<n;k++)
			f[i][n]-=f[i][k]*f[k][k];
		f[i][i]=f[i][n]/f[i][i];
	}
	for(int i=1;i<=m;i++)
		edge[i].prob+=f[edge[i].u][edge[i].u]/g[edge[i].u]+f[edge[i].v][edge[i].v]/g[edge[i].v];
	std::sort(edge+1,edge+m+1);
	real ans=0;
	for(int i=1;i<=m;i++)
		ans+=edge[i].prob*i;
	printf("%.3lf\n",ans);
	return 0;
}
