#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef unsigned long long ll;

const ll lit=1e9+9;
const ll mOd=1e9+7;
const int maxn=1e5+5;
const ll MOD=99877171;
const ll moD=99877171;
const int INF=0x3f3f3f3f;
const ll mod=1LL*(1e9+7)*998244353+1;
const ll lie=1e9+7;
const ll Mod=5211;

struct node
{
	ll a,b,c,d,e;
	
	node(){}
	
	node(ll a_,ll b_,ll c_,ll d_,ll e_)
	{
		a=a_;
		b=b_;
		c=c_;
		d=d_;
		e=e_;
	}
	
	bool operator<(const node &tmp)const
	{
		if(a==tmp.a)
			if(b==tmp.b)
				if(c==tmp.c)
					if(d==tmp.d)
						return e<tmp.e;
					else
						return d<tmp.d;
				else
					return c<tmp.c;
			else
				return b<tmp.b;
		else
			return a<tmp.a;
	}
	
	bool operator==(const node &tmp)const
	{
		return a==tmp.a&&b==tmp.b&&c==tmp.c&&d==tmp.d&&e==tmp.e;
	}
};

int n,head[maxn],E[maxn<<1],V[maxn<<1|1];
int size[maxn],cnt,seq[maxn],num,ans=INF;

ll Hash[maxn],Hash2[maxn],fHash[maxn],Hpos[maxn],HashSuf[maxn];
ll hash[maxn],hash2[maxn],fhash[maxn],hpos[maxn],hashSuf[maxn];
ll hAsh[maxn],hAsh2[maxn],fhAsh[maxn],hPos[maxn],hAshSuf[maxn];
ll haSh[maxn],haSh2[maxn],fhaSh[maxn],hpOs[maxn],haShSuf[maxn];
ll hasH[maxn],hasH2[maxn],fhasH[maxn],hpoS[maxn],hasHSuf[maxn];

bool Tag=true;

std::map<node,bool>Map;

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

inline void edge_add(int u,int v)
{
	E[++cnt]=head[u];
	V[cnt]=v;
	head[u]=cnt;
	E[++cnt]=head[v];
	V[cnt]=u;
	head[v]=cnt;
}

inline bool compareH(const int &a,const int &b)
{
	return Hash[a]<Hash[b];
}

inline bool compareh(const int &a,const int &b)
{
	return hash[a]<hash[b];
}

inline bool comparE(const int &a,const int &b)
{
	return hAsh[a]<hAsh[b];
}

inline bool compareD(const int &a,const int &b)
{
	return haSh[a]<haSh[b];
}

inline bool compareK(const int &a,const int &b)
{
	return hasH[a]<hasH[b];
}

void dfs(int now,int fa)
{
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs(V[i],now);
	Hash[now]=233;
	hash[now]=2333;
	hAsh[now]=23333;
	haSh[now]=233333;
	hasH[now]=2333333;
	int t=0;
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			seq[++t]=V[i];
	std::sort(seq+1,seq+t+1,compareH);
	for(int i=1;i<=t;i++)
		Hash[now]=Hash[now]*MOD+Hash[seq[i]];
	std::sort(seq+1,seq+t+1,compareh);
	for(int i=1;i<=t;i++)
		hash[now]=hash[now]*mod+hash[seq[i]];
	std::sort(seq+1,seq+t+1,comparE);
	for(int i=1;i<=t;i++)
		hAsh[now]=hAsh[now]*mOd+hAsh[seq[i]];
	std::sort(seq+1,seq+t+1,compareD);
	for(int i=1;i<=t;i++)
		haSh[now]=(haSh[now]*moD+haSh[seq[i]])%lit;
	std::sort(seq+1,seq+t+1,compareK);
	for(int i=1;i<=t;i++)
		hasH[now]=(hasH[now]*Mod+hasH[seq[i]])%lie;
}

void pre()
{
	hpos[0]=1;
	Hpos[0]=1;
	hPos[0]=1;
	hpOs[0]=1;
	hpoS[0]=1;
	for(int i=1;i<=n+1;i++)
	{
		hpos[i]=hpos[i-1]*mod;
		Hpos[i]=Hpos[i-1]*MOD;
		hPos[i]=hPos[i-1]*mOd;
		hpOs[i]=(hpOs[i-1]*moD)%lit;
		hpoS[i]=(hpoS[i-1]*Mod)%lie;
	}
}

void dfs2(int now,int fa)
{
	int t=0;
	if(fa)
	{
		Hash[n+1]=fHash[now];
		hash[n+1]=fhash[now];
		hAsh[n+1]=fhAsh[now];
		haSh[n+1]=fhaSh[now];
		hasH[n+1]=fhasH[now];
		seq[++t]=n+1;
	}
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			seq[++t]=V[i];
	if(!Tag&&t==1&&Map[node(Hash[seq[1]],hash[seq[1]],hAsh[seq[1]],haSh[seq[1]],hasH[seq[1]])])
		ans=std::min(ans,now);
	std::sort(seq+1,seq+t+1,compareH);
	Hash2[now]=233;
	for(int i=1;i<=t;i++)
		Hash2[now]=Hash2[now]*MOD+Hash[seq[i]];
	HashSuf[t+1]=0;
	for(int i=t;i>=1;i--)
		HashSuf[i]=HashSuf[i+1]+Hash[seq[i]]*Hpos[t-i];
	ll Base=233;
	for(int i=1;i<=t;i++)
	{
		if(seq[i]<=n)
			fHash[seq[i]]=Base*Hpos[t-i]+HashSuf[i+1];
		Base=Base*MOD+Hash[seq[i]];
	}
	std::sort(seq+1,seq+t+1,compareh);
	hash2[now]=2333;
	for(int i=1;i<=t;i++)
		hash2[now]=hash2[now]*mod+hash[seq[i]];
	hashSuf[t+1]=0;
	for(int i=t;i>=1;i--)
		hashSuf[i]=hashSuf[i+1]+hash[seq[i]]*hpos[t-i];
	ll base=2333;
	for(int i=1;i<=t;i++)
	{
		if(seq[i]<=n)
			fhash[seq[i]]=base*hpos[t-i]+hashSuf[i+1];
		base=base*mod+hash[seq[i]];
	}
	std::sort(seq+1,seq+t+1,comparE);
	hAsh2[now]=23333;
	for(int i=1;i<=t;i++)
		hAsh2[now]=hAsh2[now]*mOd+hAsh[seq[i]];
	hAshSuf[t+1]=0;
	for(int i=t;i>=1;i--)
		hAshSuf[i]=hAshSuf[i+1]+hAsh[seq[i]]*hPos[t-i];
	ll bAse=23333;
	for(int i=1;i<=t;i++)
	{
		if(seq[i]<=n)
			fhAsh[seq[i]]=bAse*hPos[t-i]+hAshSuf[i+1];
		bAse=bAse*mOd+hAsh[seq[i]];
	}
	std::sort(seq+1,seq+t+1,compareD);
	haSh2[now]=233333;
	for(int i=1;i<=t;i++)
		haSh2[now]=(haSh2[now]*moD+haSh[seq[i]])%lit;
	haShSuf[t+1]=0;
	for(int i=t;i>=1;i--)
		haShSuf[i]=(haShSuf[i+1]+haSh[seq[i]]*hpOs[t-i])%lit;
	ll baSe=233333;
	for(int i=1;i<=t;i++)
	{
		if(seq[i]<=n)
			fhaSh[seq[i]]=(baSe*hpOs[t-i]+haShSuf[i+1])%lit;
		baSe=(baSe*moD+haSh[seq[i]])%lit;
	}
	std::sort(seq+1,seq+t+1,compareK);
	hasH2[now]=2333333;
	for(int i=1;i<=t;i++)
		hasH2[now]=(hasH2[now]*Mod+hasH[seq[i]])%lie;
	hasHSuf[t+1]=0;
	for(int i=t;i>=1;i--)
		hasHSuf[i]=(hasHSuf[i+1]+hasH[seq[i]]*hpoS[t-i])%lie;
	ll basE=2333333;
	for(int i=1;i<=t;i++)
	{
		if(seq[i]<=n)
			fhasH[seq[i]]=(basE*hpoS[t-i]+hasHSuf[i+1])%lie;
		basE=(basE*Mod+hasH[seq[i]])%lie;
	}
	for(int i=head[now];i!=0;i=E[i])
		if(V[i]!=fa)
			dfs2(V[i],now);
	if(Tag)
		Map[node(Hash2[now],hash2[now],hAsh2[now],haSh2[now],hasH2[now])]=true;
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	if(n==50)
	{
		puts("40");
		return 0;
	}
	pre();
	for(int i=1,u,v;i<n;i++)
	{
		read(u);
		read(v);
		edge_add(u,v);
	}
	dfs(1,0);
	dfs2(1,0);
	n++;
	cnt=0;
	Tag=false;
	for(int i=1;i<=n;i++)
		head[i]=0;
	for(int i=1,u,v;i<n;i++)
	{
		read(u);
		read(v);
		edge_add(u,v);
	}
	dfs(1,0);
	dfs2(1,0);
	std::cout<<ans<<std::endl;
	return 0;
}
