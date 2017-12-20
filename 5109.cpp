#include <map>
#include <queue>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const ll INF=1e17;
const int maxn=5e4+5;
const ll mod1=1e16+7;
const ll mod2=1e8+1e13+579;
struct Hash
{
	ll HashVal1,HashVal2;
	Hash(){}
	Hash(ll HashVal1_,ll HashVal2_)
	{
		HashVal1=HashVal1_;
		HashVal2=HashVal2_;
	}
	inline bool operator<(const Hash &tmp)const
	{
		if(HashVal1==tmp.HashVal1)
			return HashVal2<tmp.HashVal2;
		return HashVal1<tmp.HashVal1;
	}
	inline bool operator==(const Hash &tmp)const
	{
		return HashVal1==tmp.HashVal1&&HashVal2==tmp.HashVal2;
	}
};
struct node
{
	int now;
	ll dist;
	node(){}
	node(int now_,ll dist_)
	{
		now=now_;
		dist=dist_;
	}
	bool operator<(const node &tmp)const
	{
		return dist>tmp.dist;
	}
};
struct EdgeType
{
	int u,v,w;
};
struct EdgeType edge[maxn];
int n,m,S,T,head[maxn],V[maxn<<1],W[maxn<<1],cnt2,que[maxn],deg[maxn];
int E[maxn<<1],cnt,head2[maxn],V2[maxn<<1],E2[maxn<<1],deg2[maxn];
int W2[maxn<<1];
ll disS[maxn],disT[maxn],Sval1[maxn],Sval2[maxn],Tval1[maxn],Tval2[maxn];
bool vis[maxn];
using std::map;
using std::bitset;
bitset<maxn>f[maxn],g[maxn],Tmp;
map<Hash,bitset<maxn> >Map;
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
inline void edge_add(int u,int v,int w)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	W[cnt]=w;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	W[cnt]=w;
	head[v]=cnt;
}
void dijkstra(int s,ll *dis)
{
	memset(vis,false,sizeof(vis));
	dis[s]=0;
	std::priority_queue<node>que;
	node now;
	que.push(node(s,0));
	while(!que.empty())
	{
		now=que.top();
		que.pop();
		if(vis[now.now])
			continue;
		vis[now.now]=true;
		for(int i=head[now.now];i!=0;i=E[i])
			if(now.dist+W[i]<dis[V[i]])
			{
				dis[V[i]]=now.dist+W[i];
				que.push(node(V[i],dis[V[i]]));
			}
	}
}
inline void edge_add2(int u,int v,int w)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	W[cnt]=w;
	head[u]=cnt;
	E2[++cnt2]=head2[v];
	V2[cnt2]=u;
	W2[cnt2]=w;
	head2[v]=cnt2;
	++deg[v];
	++deg2[u];
	vis[u]=true;
	vis[v]=true;
}
inline void add1(ll &a,ll b)
{
	if((a+=b)>=mod1)
		a-=mod1;
}
inline void add2(ll &a,ll b)
{
	if((a+=b)>=mod2)
		a-=mod2;
}
void top_sort_S()
{
	int h=0,tail=1;
	Sval1[S]=1;
	Sval2[S]=1;
	que[h]=S;
	int now;
	while(h<tail)
	{
		now=que[h++];
		f[now][now]=true;
		for(int i=head[now];i!=0;i=E[i])
		{
			if(!(--deg[V[i]]))
				que[tail++]=V[i];
			add1(Sval1[V[i]],Sval1[now]);
			add2(Sval2[V[i]],Sval2[now]);
			f[V[i]]|=f[now];
		}
	}
}
void top_sort_T()
{
	int h=0,tail=1;
	Tval1[T]=1;
	Tval2[T]=1;
	que[h]=T;
	int now;
	while(h<tail)
	{
		now=que[h++];
		g[now][now]=true;
		for(int i=head2[now];i!=0;i=E2[i])
		{
			if(!(--deg2[V2[i]]))
				que[tail++]=V2[i];
			add1(Tval1[V2[i]],Tval1[now]);
			add2(Tval2[V2[i]],Tval2[now]);
			g[V2[i]]|=g[now];
		}
	}
}
ll mul1(ll a,ll b)
{
	ll res=0;
	while(b>0)
	{
		if(b&1)
			add1(res,a);
		add1(a,a);
		b>>=1;
	}
	return res;
}
ll mul2(ll a,ll b)
{
	ll res=0;
	while(b>0)
	{
		if(b&1)
			add2(res,a);
		add2(a,a);
		b>>=1;
	}
	return res;
}
int main()
{
	read(n);
	read(m);
	read(S);
	read(T);
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u);
		read(v);
		read(w);
		edge[i].u=u;
		edge[i].v=v;
		edge[i].w=w;
		edge_add(u,v,w);
	}
	memset(disS,0x3f,sizeof(disS));
	memset(disT,0x3f,sizeof(disT));
	dijkstra(S,disS);
	dijkstra(T,disT);
	if(disT[S]==disT[0])
	{
		std::cout<<1LL*n*(n-1)/2;
		return 0;
	}
	memset(head,0,sizeof(head));
	cnt=0;
	memset(vis,false,sizeof(vis));
	ll C=disS[T];
	for(int i=1;i<=m;i++)
	{
		if(disS[edge[i].u]+disT[edge[i].v]+edge[i].w==C)
			edge_add2(edge[i].u,edge[i].v,edge[i].w);
		else if(disS[edge[i].v]+disT[edge[i].u]+edge[i].w==C)
			edge_add2(edge[i].v,edge[i].u,edge[i].w);
	}
	top_sort_S();
	top_sort_T();
	ll ALL1=Sval1[T],ALL2=Sval2[T];
	int num=0;
	for(int i=1;i<=n;i++)
		if(vis[i])
		{
			Sval1[i]=mul1(Sval1[i],Tval1[i]);
			Sval2[i]=mul2(Sval2[i],Tval2[i]);
			f[i]|=g[i];
			Map[Hash(Sval1[i],Sval2[i])][i]=true;
			++num;
		}
	ll ans1=0,ans2=0,tmp1,tmp2;
	for(int i=1;i<=n;i++)
		if(vis[i])
		{
			if(Sval1[i]==ALL1&&Sval2[i]==ALL2)
				ans1+=n-num;
			else
			{
				tmp1=(ALL1-Sval1[i]+mod1)%mod1;
				tmp2=(ALL2-Sval2[i]+mod2)%mod2;
				Tmp=Map[Hash(tmp1,tmp2)];
				ans2+=((~f[i])&Tmp).count();
			}
		}
	std::cout<<ans1+ans2/2;
	return 0;
}
