#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=3e3+5;
const int INF=0x3f3f3f3f;
int n,m,k,ai[maxn],bi[maxn],seq1[maxn],seq2[maxn],num1,num2;
int head[maxn],ans,num,s,t,deep[maxn],E[maxn*maxn/5],V[maxn*maxn/5];
int F[maxn*maxn/5],cnt,que[maxn],seq[maxn];
bool has[300][maxn],hasB[maxn][maxn];
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
inline bool check(int x)
{
	short res=0;
	for(short i=0;i<=30;i++)
		if(x&(1<<i))
			res++;
	return res%2==0;
}
inline void edge_add(int u,int v)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	F[cnt]=1;
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
	que[0]=s;
	while(h<tail)
		for(int i=head[now=que[h++]];i!=0;i=E[i])
			if(deep[V[i]]<0&&F[i])
			{
				deep[V[i]]=deep[now]+1;
				if(V[i]==t)
					return true;
				que[tail++]=V[i];
			}
	return false;
}
inline int flowing(int now,int flow)
{
	if(now==t||flow<=0)
		return flow;
	int oldflow=0,tmp;
	for(int i=head[now];i!=0;i=E[i])
		if(F[i]&&deep[V[i]]==deep[now]+1)
		{
			tmp=flowing(V[i],std::min(flow,F[i]));
			F[i]-=tmp;
			F[i^1]+=tmp;
			oldflow+=tmp;
			flow-=tmp;
			if(!flow)
				return oldflow;
		}
	if(flow)
		deep[now]=-1;
	return oldflow;
}
inline int getans()
{
	int res=0;
	while(bfs())
		res+=flowing(s,INF);
	return res;
}
inline void build()
{
	num1=0;
	num2=0;
	for(short i=1,x,v;i<=m;i++)
	{
		x=1;
		for(v=1;v<=num;v++)
			if(!has[seq[v]][i])
			{
				x=0;
				break;
			}
		if(x)
			if(bi[i]%2)
				seq1[++num1]=i;
			else
				seq2[++num2]=i;
	}
	cnt=1;
	s=0;
	t=num1+num2+1;
	for(short i=s;i<=t;i++)
		head[i]=0;
	for(short i=1;i<=num1;i++)
		edge_add(s,i);
	for(short i=1;i<=num2;i++)
		edge_add(i+num1,t);
	for(short i=1,v;i<=num1;i++)
		for(v=1;v<=num2;v++)
			if(hasB[i][v])
				edge_add(i,v+num1);
}
int main()
{
	//freopen("data.txt","r",stdin);
	//freopen("friends.in","r",stdin);
	//freopen("friends.out","w",stdout);
	int T;
	T=1;
	while(T--)
	{
		read(n);
		read(m);
		read(k);
		memset(has,0,sizeof(has));
		memset(hasB,0,sizeof(hasB));
		for(int i=1;i<=n;i++)
			read(ai[i]);
		for(int i=1;i<=m;i++)
			read(bi[i]);
		for(int i=1,u,v;i<=k;i++)
		{
			read(u);
			read(v);
			has[u][v]=true;
		}
		for(int i=1;i<=m;i++)
			for(int v=i+1;v<=m;v++)
				if((bi[i]^bi[v])%2==1&&!check(bi[i]|bi[v]))
					hasB[i][v]=hasB[v][i]=true;
		num1=0;
		num2=0;
		cnt=1;
		for(int i=1;i<=m;i++)
			if(bi[i]%2)
				seq1[++num1]=i;
			else
				seq2[++num2]=i;
		s=0;
		t=num1+num2+1;
		for(int i=1;i<=num1;i++)
			edge_add(s,i);
		for(int i=1;i<=num2;i++)
			edge_add(i+num1,t);
		for(int i=1;i<=num1;i++)
			for(int v=1;v<=num2;v++)
				if(hasB[seq1[i]][seq2[v]])
					edge_add(i,v+num1);
		ans=num1+num2-getans();
		cnt=1;
		for(int i=1;i<=n;i++)
		{
			seq[++num]=i;
			build();
			ans=std::max(ans,num+num1+num2-getans());
			for(int v=i+1;v<=n;v++)
			{
				if((ai[i]^ai[v])%2==0)
					continue;
				seq[++num]=v;
				build();
				ans=std::max(ans,num+num1+num2-getans());
				--num;
			}
			--num;
		}
		std::cout<<ans;
	}
	return 0;
}
