#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-12;
const int maxn=8e2+5;

int n,m,a,b,head[maxn],E[maxn<<1|1],V[maxn<<1|1],num;
int cnt,deg[maxn],id[maxn][maxn],backx[maxn],backy[maxn];

real p[maxn],p_[maxn],f[maxn][maxn];

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

using std::fabs;

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	read(a);
	read(b);
	for(int i=1,u,v;i<=m;i++)
	{
		read(u);
		read(v);
		E[++cnt]=head[u];
		V[cnt]=v;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		head[v]=cnt;
		deg[u]++;
		deg[v]++;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&p[i]);
		p_[i]=1-p[i];
	}
	cnt=0;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
		{
			id[i][v]=++cnt;
			backx[cnt]=i;
			backy[cnt]=v;
		}
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
		{
			int now=id[i][v];
			f[now][now]=1;
			if(i!=v)
				f[now][now]-=p[i]*p[v];
 			for(int i_=head[i];i_!=0;i_=E[i_])
				for(int v_=head[v];v_!=0;v_=E[v_])
				{
					int t1=V[i_],t2=V[v_];
					if(t1==t2)
						continue;
					real t=1;
					t*=p_[t1]*p_[t2]/deg[t1]/deg[t2];
					f[now][id[t1][t2]]-=t;
				}
			for(int i_=head[i];i_!=0;i_=E[i_])
			{
				int t1=V[i_];
				if(t1==v)
					continue;
				real t=p[v]*p_[t1]/deg[t1];
				f[now][id[t1][v]]-=t;
			}
			for(int i_=head[v];i_!=0;i_=E[i_])
			{
				int t1=V[i_];
				if(t1==i)
					continue;
				real t=p[i]*p_[t1]/deg[t1];
				f[now][id[i][t1]]-=t;
			}
		}
	f[id[a][b]][cnt+1]=1;
	for(int i=1;i<=cnt;i++)
	{
		int to=i;
		for(int v=i+1;v<=cnt;v++)
			if(fabs(f[to][i])<fabs(f[v][i]))
				to=v;
		if(to!=i)
			std::swap(f[to],f[i]);
		if(fabs(f[i][i]>eps))
		{
			for(int v=i+1;v<=cnt;v++)
				if(fabs(f[v][i])>eps)
				{
					real tmp=f[v][i]/f[i][i];
					for(int e=i;e<=cnt+1;e++)
						f[v][e]=f[v][e]-f[i][e]*tmp;
				}
		}
	}
	for(int i=cnt;i>=1;i--)
	{
		for(int v=cnt;v>i;v--)
			f[i][cnt+1]-=f[v][v]*f[i][v];
		f[i][i]=f[i][cnt+1]/f[i][i];
	}
	for(int i=1;i<=n;i++)
		printf("%.6lf ",f[id[i][i]][id[i][i]]);
	return 0;
}
