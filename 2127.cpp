#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int T=10005,INF=0x3f3f3f3f,maxn=T;
const int xx[4]={0,0,1,-1},yy[4]={1,-1,0,0};

struct data
{
	int to,next,v;
};

struct data e[300001];

int n,m,ans,cnt=1,head[T],h[T],a[105][105],b[105][105];
int color[101][101],mark[105][105],tot,que[maxn],deep[maxn];

inline void ins(int u,int v,int w)
{
	e[++cnt].to=v,e[cnt].v=w,e[cnt].next=head[u],head[u]=cnt;
}

inline void insert(int u,int v,int w)
{
	ins(u,v,w),ins(v,u,0);
}

inline void insert2(int u,int v,int w)
{
	ins(u,v,w),ins(v,u,w);
}

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

bool bfs()
{
	int h=0,tail=1,now;
	for(int i=0;i<=T;i++) deep[i]=-1;
	deep[0]=0,que[h]=0;
	while(h<tail)
		for(int i=head[now=que[h++]];i;i=e[i].next)
			if(e[i].v&&deep[e[i].to]<0)
			{
				deep[e[i].to]=deep[now]+1;
				if(e[i].to==T) return true;
				que[tail++]=e[i].to;
			}
	return false;
}

int flowing(int now,int flow)
{
	if(now==T||flow<=0) return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i;i=e[i].next)
		if(e[i].v&&deep[e[i].to]==deep[now]+1)
		{
			tmp=flowing(e[i].to,std::min(flow,e[i].v));
			e[i].v-=tmp,e[i^1].v+=tmp,flow-=tmp,oldflow+=tmp;
			if(!flow) return oldflow;
		}
	if(flow) deep[now]=-1;
	return oldflow;
}

int main()
{
//	freopen("nt2011_happiness.in","r",stdin);
//	freopen("nt2011_happiness.out","w",stdout);
//	freopen("data.txt","r",stdin);
	read(n),read(m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			read(a[i][j]),tot+=a[i][j],a[i][j]<<=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			read(b[i][j]),tot+=b[i][j],b[i][j]<<=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			mark[i][j]=(i-1)*m+j;
	int x;
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			read(x);
			tot+=x;
			a[i][j]+=x;
			a[i+1][j]+=x;
			insert2(mark[i][j],mark[i+1][j],x);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			read(x);
			tot+=x;
			b[i][j]+=x;
			b[i+1][j]+=x;
			insert2(mark[i][j],mark[i+1][j],x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			read(x);
			tot+=x;
			a[i][j]+=x;
			a[i][j+1]+=x;
			insert2(mark[i][j],mark[i][j+1],x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			read(x);
			tot+=x;
			b[i][j]+=x;
			b[i][j+1]+=x;
			insert2(mark[i][j],mark[i][j+1],x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			insert(0,mark[i][j],a[i][j]);	
			insert(mark[i][j],T,b[i][j]);
		}
	while(bfs())
		ans+=flowing(0,INF);
	std::cout<<tot-(ans>>1);
	return 0;
}
