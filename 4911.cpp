#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const short Inv=5004;
const short mod=1e4+7;
const int maxn=3e4+5;
const int maxtree=maxn<<2|1;
int n,m,q,head[maxn],E[maxn<<1|1],V[maxn<<1|1],cnt;
int vall[maxtree][128],valr[maxtree][128],val[maxtree][128];
int base[128][128],L[maxtree],R[maxtree],mid[maxtree];
int f[128],g[128],fa[maxn],deep[maxn],top[maxn],lar[maxn];
int valf[maxtree][128],zero[maxtree][128],Li[maxn],Ri[maxn];
int li[maxn],ri[maxn],st[maxn],size[maxn],St[maxn],sum[maxtree][128];
int inv[mod],Tag,fl[128],fr[128],tag,count[maxtree],sumf[maxtree][128];
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
inline void add(int &x,int y)
{
	x+=y;
	while(x>=mod)
		x-=mod;
	while(x<0)
		x+=mod;
}
inline void add0()
{
	for(register short i=0;i<m;i++)
		add(fl[i],base[0][i]);
}
void fwt(int *p,int len)
{
	if(len==1)
		return;
	fwt(p,len>>1);
	fwt(p+(len>>1),len>>1);
	for(int i=0,t1,t2;i<(len>>1);i++)
	{
		t1=p[i];
		t2=p[i+(len>>1)];
		p[i]=p[i+(len>>1)]=t1;
		add(p[i],t2);
		add(p[i+(len>>1)],-t2);
	}
}
void ifwt(int *p,int len)
{
	if(len==1)
		return;
	for(int i=0,t1,t2;i<(len>>1);i++)
	{
		t1=p[i];
		t2=p[i+(len>>1)];
		p[i]=(t1+t2)%mod*Inv%mod;
		p[i+(len>>1)]=(t1-t2)%mod*Inv%mod;
		add(p[i+(len>>1)],0);
	}
	ifwt(p,len>>1);
	ifwt(p+(len>>1),len>>1);
}
inline ll poww(ll x,ll e)
{
	ll res=1;
	while(e>0)
	{
		if(e&1)
			res=res*x%mod;
		e>>=1;
		x=x*x%mod;
	}
	return res;
}
void pre()
{
	for(int i=0;i<m;i++)
	{
		base[i][i]=1;
		fwt(base[i],m);
	}
	for(int i=0;i<mod;i++)
		inv[i]=poww(i,mod-2);
}
void dfs1(int x,int F)
{
	fa[x]=F;
	size[x]=1;
	deep[x]=deep[F]+1;
	for(int i=head[x];i!=0;i=E[i])
		if(V[i]!=F)
		{
			dfs1(V[i],x);
			size[x]+=size[V[i]];
			if(size[V[i]]>=size[lar[x]])
				lar[x]=V[i];
		}
}
void dfs2(int x,int c)
{
	top[x]=c;
	li[x]=++cnt;
	if(!Ri[c])
		Ri[c]=cnt;
	St[cnt]=st[x];
	Li[c]=std::max(Li[c],cnt);
	if(lar[x])
		dfs2(lar[x],c);
	for(int i=head[x];i!=0;i=E[i])
		if(V[i]!=fa[x]&&V[i]!=lar[x])
			dfs2(V[i],V[i]);
	ri[x]=cnt;
}
inline void update(int x)
{
	for(register short i=0;i<m;i++)
	{
		vall[x][i]=vall[x<<1][i];
		valr[x][i]=valr[x<<1|1][i];
		sum[x][i]=sum[x<<1][i]+sum[x<<1|1][i];
		add(sum[x][i],0);
		add(sum[x][i],valr[x<<1][i]*vall[x<<1|1][i]%mod);
		val[x][i]=val[x<<1][i]*val[x<<1|1][i]%mod;
		add(vall[x][i],val[x<<1][i]*vall[x<<1|1][i]%mod);
		add(valr[x][i],val[x<<1|1][i]*valr[x<<1][i]%mod);
	}
}
void build(const int &x,const int &l,const int &r)
{
	L[x]=l;
	R[x]=r;
	if(l==r)
	{
		for(register short i=0;i<m;i++)
			val[x][i]=sum[x][i]=vall[x][i]=valr[x][i]=base[St[l]][i];
		return;
	}
	mid[x]=l+r>>1;
	build(x<<1,l,mid[x]);
	build(x<<1|1,mid[x]+1,r);
	update(x);
}
inline int C(const int &x,const int &y)
{
	if(!count[x])
		return 1;
	if(zero[x][y])
		return 0;
	if(valf[x][y]==-1)
		return 0;
	return valf[x][y];
}
inline void update(const int &x,const int &to)
{
	if(L[x]==R[x])
	{
		if(Tag==1)
		{
			count[x]--;
			for(register short i=0;i<m;i++)
			{
				if(fl[i]==0)
					zero[x][i]--;
				else
					valf[x][i]=valf[x][i]*inv[fl[i]]%mod;
				if(count[x]==zero[x][i])
					valf[x][i]=-1;
				val[x][i]=sum[x][i]=vall[x][i]=valr[x][i]=C(x,i)*base[St[to]][i]%mod;
				add(sumf[x][i],-g[i]);
				add(sum[x][i],sumf[x][i]);
			}
		}
		else
		{
			if(!count[x])
			{
				count[x]++;
				for(register short i=0;i<m;i++)
				{
					if(fl[i]==0)
						zero[x][i]++;
					else
						valf[x][i]=fl[i];
					val[x][i]=sum[x][i]=vall[x][i]=valr[x][i]=C(x,i)*base[St[to]][i]%mod;
					add(sumf[x][i],g[i]);
					add(sum[x][i],sumf[x][i]);
				}
				count[x]--;
			}
			else
			{
				for(register short i=0;i<m;i++)
				{
					if(fl[i]==0)
						zero[x][i]++;
					else
					{
						if(fl[i]!=0&&valf[x][i]==-1)
							valf[x][i]=fl[i];
						else
							valf[x][i]=valf[x][i]*fl[i]%mod;
					}
					val[x][i]=sum[x][i]=vall[x][i]=valr[x][i]=C(x,i)*base[St[to]][i]%mod;
					add(sumf[x][i],g[i]);
					add(sum[x][i],sumf[x][i]);
				}
			}
			count[x]++;
		}
		return;
	}
	if(to<=mid[x])
		update(x<<1,to);
	else
		update(x<<1|1,to);
	update(x);
}
void query(const int &x,const int &l,const int &r)
{
	if(L[x]>=l&&R[x]<=r)
	{
		if(tag)
		{
			for(short i=0;i<m;i++)
			{
				g[i]=sum[x][i];
				fl[i]=vall[x][i];
				fr[i]=valr[x][i];
				f[i]=val[x][i];
			}
			tag=false;
			return;
		}
		int tmp;
		for(short i=0;i<m;i++)
		{
			add(g[i],sum[x][i]+fr[i]*vall[x][i]%mod);
			add(fl[i],f[i]*vall[x][i]%mod);
			tmp=valr[x][i];
			add(tmp,fr[i]*val[x][i]%mod);
			fr[i]=tmp;
			f[i]=f[i]*val[x][i]%mod;
		}
		return;
	}
	if(l<=mid[x])
		query(x<<1,l,r);
	if(r>mid[x])
		query(x<<1|1,l,r);
}
inline void query(int x)
{
	tag=true;
	query(1,Ri[top[x]],Li[top[x]]);
}
void solve_clear(int x)
{
	if(top[x]==1)
		return;
	solve_clear(fa[top[x]]);
	query(x);
	Tag=1;
	add0();
	update(1,li[fa[top[x]]]);
}
void solve(int x)
{
	if(top[x]==1)
		return;
	Tag=2;
	query(x);
	add0();
	update(1,li[fa[top[x]]]);
	solve(fa[top[x]]);
}
void update(const int &x,const int &to,const int &y)
{
	if(L[x]==R[x])
	{
		St[to]=y;
		if(!count[x])
		{
			for(register short i=0;i<m;i++)
				vall[x][i]=valr[x][i]=val[x][i]=sum[x][i]=base[St[to]][i];
		}
		else
		{
			for(register short i=0;i<m;i++)
			{
				vall[x][i]=valr[x][i]=val[x][i]=sum[x][i]=C(x,i)*base[St[to]][i]%mod;
				add(sum[x][i],sumf[x][i]);
			}
		}
		return;
	}
	if(to<=mid[x])
		update(x<<1,to,y);
	else
		update(x<<1|1,to,y);
	update(x);
}
void dfs(int x)
{
	if(lar[x])
		dfs(lar[x]);
	for(int i=head[x];i!=0;i=E[i])
		if(V[i]!=fa[x]&&V[i]!=lar[x])
		{
			dfs(V[i]);
			query(V[i]);
			Tag=2;
			add0();
			update(1,li[x]);
		}
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	pre();
	memset(valf,-1,sizeof(valf));
	for(int i=1;i<=n;i++)
		read(st[i]);
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
	dfs1(1,0);
	cnt=0;
	dfs2(1,1);
	build(1,1,n);
	dfs(1);
	read(q);
	char op[11];
	for(int i=1,x,y;i<=q;i++)
	{
		scanf("%s",op);
		if(op[0]=='C')
		{
			read(x);
			read(y);
			solve_clear(x);
			update(1,li[x],y);
			solve(x);
		}
		else
		{
			read(x);
			query(1);
			ifwt(g,m);
			printf("%d\n",g[x]);
		}
	}
	return 0;
}
