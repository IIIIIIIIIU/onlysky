#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned long long ll;
const int mod=29;
const int maxn=1e6+5;
const int INF=0x3f3f3f3f;
int n,m,head[maxn],cnt,E[maxn<<1|1],V[maxn<<1|1];
int val[maxn],tot,count[maxn],lar[maxn],size[maxn];
int SIZE,M,root,f[maxn],pre[maxn],suf[maxn],id1[maxn],id2[maxn];
ll Hash[maxn*2],Hash2[maxn*2],hpos[maxn*2],ans;
char str[maxn];
bool vis[maxn];
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
void find(int now,int fa)
{
	lar[now]=0;
	size[now]=1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa&&!vis[V[i]])
		{
			find(V[i],now);
			size[now]+=size[V[i]];
			if(size[V[i]]>lar[now])
				lar[now]=size[V[i]];
		}
	if(SIZE-size[now]>lar[now])
		lar[now]=SIZE-size[now];
	if(lar[now]<lar[root])
		root=now;
}
inline ll getHash2(int l,int r)
{
	return Hash2[r]-Hash2[l-1]*hpos[r-l+1];
}
inline ll getHash(int l,int r)
{
	return Hash[r]-Hash[l-1]*hpos[r-l+1];
}
void count1(int now,int fa,ll h1,ll h2,int len)
{
	int tmp;
	if(h1==getHash2(M-len+1,M))
	{
		tmp=m-(len%m);
		tmp%=m;
		if(id2[tmp]==tot)
			ans+=suf[tmp];
		if(len%m==0&&h1==getHash(M-len+1,M))
			ans++;
	}
	else if(len%m==0&&h1==getHash(M-len+1,M))
		ans++;
	if(len>1&&h2==getHash(M-(len-1)+1,M))
	{
		tmp=m-((len-1)%m);
		tmp%=m;
		if(id1[tmp]==tot)
			ans+=pre[tmp];
	}
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa&&!vis[V[i]])
			count1(V[i],now,h1*mod+val[V[i]],h2*mod+val[V[i]],len+1);
}
void count2(int now,int fa,ll h1,ll h2,int len)
{
	int tmp;
	if(h1==getHash2(M-len+1,M))
	{
		tmp=len%m;
		tmp%=m;
		if(id1[tmp]==tot)
			pre[tmp]++;
		else
		{
			id1[tmp]=tot;
			pre[tmp]=1;
		}
	}
	if(len>1&&h2==getHash(M-(len-1)+1,M))
	{
		tmp=(len-1)%m;
		if(id2[tmp]==tot)
			suf[tmp]++;
		else
		{
			id2[tmp]=tot;
			suf[tmp]=1;
		}
	}
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa&&!vis[V[i]])
			count2(V[i],now,h1*mod+val[V[i]],h2*mod+val[V[i]],len+1);
}
void dfs(int now,int fa)
{
	SIZE++;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa&&!vis[V[i]])
			dfs(V[i],now);
}
void solve(int now)
{
	if(SIZE<m)
		return;
	root=0;
	find(now,0);
	tot++;
	now=root;
	for(int i=head[now];i!=0;i=E[i])
		if(!vis[V[i]])
		{
			count1(V[i],now,val[now]*mod+val[V[i]],val[V[i]],2);
			count2(V[i],now,val[now]*mod+val[V[i]],val[V[i]],2);
		}
	if(id1[0]==tot)
		ans+=pre[0];
	vis[now]=true;
	for(int i=head[now];i!=0;i=E[i])
		if(!vis[V[i]])
		{
			SIZE=0;
			dfs(V[i],0);
			solve(V[i]);
		}
}
int main()
{
	int T;
	read(T);
	lar[0]=INF;
	while(T--)
	{
		ans=0;
		read(n);
		read(m);
		std::cin>>str+1;
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
		{
			val[i]=str[i]-'A'+1;
			head[i]=id1[i]=id2[i]=0;
		}
		cnt=0;
		tot=0;
		for(int i=1,u,v;i<n;i++)
		{
			read(u);
			read(v);
			E[++cnt]=head[u];
			V[cnt]=v;
			head[u]=cnt;
			E[++cnt]=head[v];
			V[cnt]=u;
			head[v]=cnt;
		}
		std::cin>>str+1;
		hpos[0]=1;
		int len=m;
		while(len*m<n)
			len++;
		M=len*m;
		for(int i=0;i<len;i++)
			for(int v=1;v<=m;v++)
			{
				hpos[i*m+v]=hpos[i*m+v-1]*mod;
				Hash[i*m+v]=Hash[i*m+v-1]*mod+(str[v]-'A'+1);
				Hash2[i*m+v]=Hash2[i*m+v-1]*mod+(str[m-v+1]-'A'+1);
			}
		SIZE=n;
		solve(1);
		std::cout<<ans<<std::endl;
	}
	return 0;
}
