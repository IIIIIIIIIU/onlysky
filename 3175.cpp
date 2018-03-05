#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=2e6+5;
const int INF=0x3f3f3f3f;
const int dx[8]={-2,-2,-1,1,2,2,1,-1};
const int dy[8]={-1,1,2,2,1,-1,-2,-2};

int n,m,head[maxn],E[maxn<<1],V[maxn<<1|1],F[maxn<<1|1];
int cnt=1,id[205][205],num,s,t,deep[maxn],que[maxn];

char str[205][205];

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

bool bfs()
{
	for(int i=s;i<=t;i++)
		deep[i]=-1;
	que[0]=s;
	deep[s]=0;
	int h=0,tail=1,now;
	while(h<tail)
	{
		now=que[h++];
		for(int i=head[now];i!=0;i=E[i])
			if(deep[V[i]]<0&&F[i]>0)
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
		if(F[i]>0&&deep[V[i]]==deep[now]+1)
		{
			tmp=flowing(V[i],std::min(F[i],flow));
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
	std::cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str[i]+1);
		for(int v=1;v<=n;v++)
			if(str[i][v]=='0')
				id[i][v]=++num;
	}
	t=num*2+1;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			if(str[i][v]=='0')
			{
				edge_add(s,id[i][v],1);
				edge_add(id[i][v]+num,t,1);
				for(int e=0,x,y;e<8;e++)
				{
					x=i+dx[e];
					y=v+dy[e];
					if(x>0&&x<=n&&y>0&&y<=n&&id[x][y])
						edge_add(id[i][v],id[x][y]+num,1);
				}
			}
	int tans=0;
	for(;bfs();tans+=flowing(s,INF));
	std::cout<<num-(tans>>1)<<std::endl;
	return 0;
}
