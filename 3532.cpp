#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e6+5;
const int INF=0x3f3f3f3f;
struct node
{
	int id,key;
	inline bool operator<(const node &tmp)const
	{
		return key<tmp.key;
	}
};
struct node seq[maxn];
int n,ai[maxn],bi[maxn],ci[maxn],head[maxn],s,t,E[maxn];
int V[maxn],F[maxn],cnt,end,f[maxn],deep[maxn];
int que[maxn],di[maxn],num;
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
inline void edge_add(int u,int v,int f_)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	F[cnt]=f_;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	F[cnt]=0;
	head[v]=cnt;
}
inline bool bfs()
{
	for(int i=0;i<=end;i++)
		deep[i]=-1;
	int h=0,tail=1,now;
	deep[s]=0;
	que[0]=s;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
			if(F[i]&&deep[V[i]]<0)
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	}
	return false;
}
int flowing(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(F[i]&&deep[V[i]]==deep[now]+1)
		{
			tmp=flowing(V[i],std::min(flow,F[i]));
			flow-=tmp;
			oldflow+=tmp;
			F[i]-=tmp;
			F[i^1]+=tmp;
			if(!flow)
				return oldflow;
		}
	if(flow)
		deep[now]=-1;
	return oldflow;
}
int main()
{
	freopen("data.txt","r",stdin);
	int testcase;
	read(testcase);
	while(testcase--)
	{
		cnt=1;
		read(n);
		for(int i=1;i<=n;i++)
			read(ai[i]);
		for(int i=1;i<=n;i++)
			read(bi[i]);
		for(int i=1;i<=n;i++)
			read(ci[i]);
		s=0;
		t=n*2+1;
		end=t;
		for(int i=s;i<=t;i++)
			head[i]=0;
		int Max=0;
		for(int i=1;i<=n;i++)
		{
			f[i]=1;
			edge_add(i,i+n,bi[i]);
			for(int v=1;v<i;v++)
				if(ai[i]>ai[v]&&f[i]<f[v]+1)
					f[i]=f[v]+1;
			for(int v=1;v<i;v++)
				if(ai[v]<ai[i]&&f[v]+1==f[i])
					edge_add(v+n,i,INF);
			if(f[i]==1)
				edge_add(s,i,INF);
			if(f[i]>Max)
				Max=f[i];
		}
		for(int i=1;i<=n;i++)
			if(f[i]==Max)
				edge_add(i+n,t,INF);
		int out=0;
		while(bfs())
			out+=flowing(s,INF);
		num=0;
		for(int i=1;i<=n;i++)
		{
			seq[i].id=i;
			seq[i].key=ci[i];
		}
		std::sort(seq+1,seq+n+1);
		for(int i=1;i<=n;i++)
		{
			int now=seq[i].id;
			s=now;
			t=now+n;
			if(bfs())
				continue;
			s=n*2+1;
			t=now+n;
			while(bfs())
				flowing(s,INF);
			s=now;
			t=0;
			while(bfs())
				flowing(s,INF);
			di[++num]=now;
		}
		std::sort(di+1,di+num+1);
		printf("%d %d\n",out,num);
		for(int i=1;i<num;i++)
			printf("%d ",di[i]);
		printf("%d\n",di[num]);
	}
	return 0;
}
