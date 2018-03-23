#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e3+5;
const int mod1=998244353;
const int mod2=1e9+7;
const int mod3=998244311;
const ll hpos1=31459219;
const int hpos2=37453211;
const int hpos3=4334157;
struct node
{
	ll p1,p2,p3;
	node(){}
	node(ll p1_,ll p2_,ll p3_)
	{
		p1=p1_;
		p2=p2_;
		p3=p3_;
	}
	inline bool operator<(const node &tmp)const
	{
		if(p1==tmp.p1)
		{
			if(p2==tmp.p2)
				return p3<tmp.p3;
			else
				return p2<tmp.p2;
		}
		return p1<tmp.p1;
	}
	inline bool operator==(const node &tmp)const
	{
		return p1==tmp.p1&&p2==tmp.p2&&p3==tmp.p3;
	}
};
int m,head[maxn],E[maxn],V[maxn],cnt,n;
int seq[maxn],size[maxn],lar[maxn],Root[maxn],tot;
ll Hash1[maxn],Hash2[maxn],Hash3[maxn],g1[maxn],g2[maxn],g3[maxn];
std::map<node,int>Map[51];
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
inline bool compare1(const int &a,const int &b)
{
	return Hash1[a]<Hash1[b];
}
inline bool compare2(const int &a,const int &b)
{
	return Hash2[a]<Hash2[b];
}
inline bool compare3(const int &a,const int &b)
{
	return Hash3[a]<Hash3[b];
}
void dfs(int now,int fa)
{
	Hash1[now]=23333;
	Hash2[now]=239;
	Hash3[now]=997;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs(V[i],now);
	int num=0;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			seq[++num]=V[i];
	std::sort(seq+1,seq+num+1,compare1);
	for(int i=1;i<=num;i++)
		Hash1[now]=(Hash1[now]+Hash1[seq[i]]*g1[i]+23)%mod1;
	std::sort(seq+1,seq+num+1,compare2);
	for(int i=1;i<=num;i++)
		Hash2[now]=(Hash2[now]+Hash2[seq[i]]*g2[i]+23)%mod2;
	std::sort(seq+1,seq+num+1,compare3);
	for(int i=1;i<=num;i++)
		Hash3[now]=(Hash3[now]+Hash3[seq[i]]*g3[i]+23)%mod3;
}
void find(int now,int fa)
{
	lar[now]=1;
	size[now]=1;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
		{
			find(V[i],now);
			size[now]+=size[V[i]];
			if(lar[now]<size[V[i]])
				lar[now]=size[V[i]];
		}
	if(n-size[now]>lar[now])
		lar[now]=n-size[now];
	if(lar[now]<lar[Root[tot]])
		Root[tot=1]=now;
	else if(lar[now]==lar[Root[tot]])
		Root[++tot]=now;
}
void pre()
{
	g1[0]=g2[0]=g3[0]=1;
	for(int i=1;i<=50;i++)
	{
		g1[i]=g1[i-1]*hpos1%mod1;
		g2[i]=g2[i-1]*hpos2%mod2;
		g3[i]=g3[i-1]*hpos3%mod3;
	}
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	pre();
	read(m);
	lar[0]=mod1;
	for(int i=1;i<=m;i++)
	{
		read(n);
		int root=0;
		cnt=0;
		for(int e=1;e<=n;e++)
			head[e]=0;
		for(int e=1,u,v;e<=n;e++)
		{
			u=e;
			read(v);
			if(!v)
			{
				root=e;
				continue;
			}
			E[++cnt]=head[u];
			V[cnt]=v;
			head[u]=cnt;
			E[++cnt]=head[v];
			V[cnt]=u;
			head[v]=cnt;
		}
		Root[tot=1]=0;
		find(root,0);
		ll h1,h2,h3;
		if(tot==1)
		{
			dfs(Root[1],0);
			h1=Hash1[Root[1]];
			h2=Hash2[Root[1]];
			h3=Hash3[Root[1]];
		}
		else
		{
			h1=23333;
			h2=239;
			h3=997;
			dfs(Root[1],Root[2]);
			dfs(Root[2],Root[1]);
			if(Hash1[Root[1]]>Hash1[Root[2]])
				std::swap(Hash1[Root[1]],Hash1[Root[2]]);
			h1=(h1+Hash1[Root[1]]*g1[1]%mod1+23+Hash1[Root[2]]*g1[2]%mod1+23)%mod1;
			if(Hash2[Root[1]]>Hash2[Root[2]])
				std::swap(Hash2[Root[1]],Hash2[Root[2]]);
			h2=(h2+Hash2[Root[1]]*g2[1]%mod2+23+Hash2[Root[2]]*g2[2]%mod2+23)%mod2;
			if(Hash3[Root[1]]>Hash3[Root[2]])
				std::swap(Hash3[Root[1]],Hash3[Root[2]]);
			h3=(h3+Hash3[Root[1]]*g3[1]%mod3+23+Hash3[Root[2]]*g3[2]%mod3+23)%mod3;
		}
		node t=node(h1,h2,h3);
		if(!Map[n][t])
			Map[n][t]=i;
		printf("%d\n",Map[n][t]);
	}
	return 0;
}
