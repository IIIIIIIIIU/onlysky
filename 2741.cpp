#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const ll maxb=2e2+5;
const ll maxn=1e4+2e3+5;
const ll maxtree=maxn*45;
ll bit[35];
class TrieType
{
	private:
		ll root[maxn],val[maxtree],ch[maxtree][2],tot;
	public:
		ll query(ll l,ll r,ll x)
		{
			ll res=0;
			ll now=root[r];
			ll pre=root[l-1];
			for(ll i=32,tmp;i>=1;i--)
			{
				if(x&bit[i])
					tmp=0;
				else
					tmp=1;
				if(val[ch[now][tmp]]-val[ch[pre][tmp]])
				{
					res^=bit[i];
					now=ch[now][tmp];
					pre=ch[pre][tmp];
				}
				else
				{
					now=ch[now][tmp^1];
					pre=ch[pre][tmp^1];
				}
			}
			return res;
		}
		void add(ll i,ll e,ll x)
		{
			ll pre=root[e],now;
			root[i]=++tot;
			for(ll v=32;v>=1;v--)
			{
				now=tot;
				val[now]=val[pre]+1;
				if(x&bit[v])
				{
					ch[now][0]=ch[pre][0];
					ch[now][1]=++tot;
					pre=ch[pre][1];
				}
				else
				{
					ch[now][1]=ch[pre][1];
					ch[now][0]=++tot;
					pre=ch[pre][0];
				}
			}
			val[tot]=val[pre]+1;
		}
};
class TrieType trie[2];
ll n,m,tot,root[maxn],val[maxtree],ch[maxtree],blo,bel[maxn];
ll li[maxb],ri[maxb],num,ai[maxn],Max[maxb][maxb],bi[maxn];
inline void read(ll &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	blo=std::sqrt(n)+1;
	read(m);
	bit[1]=1;
	memset(li,0x3f,sizeof(li));
	for(ll i=2;i<=32;i++)
		bit[i]=bit[i-1]<<1;
	num=n/blo+1;
	for(ll i=1;i<=n;i++)
	{
		read(ai[i]);
		bi[i]=ai[i];
		bel[i]=i/blo+1;
		ai[i]^=ai[i-1];
		li[bel[i]]=std::min(li[bel[i]],i);
		ri[bel[i]]=std::max(ri[bel[i]],i);
		trie[0].add(i,i-1,ai[i]);
	}
	for(ll i=n;i>=1;i--)
	{
		bi[i]=bi[i+1]^bi[i];
		trie[1].add(n-i+1,n-i,bi[i]);
	}
	for(ll i=1;i<=num;i++)
		for(ll v=i;v<=num;v++)
			for(ll e=li[i];e<=ri[i];e++)
				Max[i][v]=std::max(Max[i][v],trie[0].query(e,ri[v],ai[e-1]));
	ll x,y,lastans=0;
	ll l,r,bl,br;
	for(ll i=1;i<=m;i++)
	{
		read(x);
		read(y);
		l=std::min((lastans+x)%n,(lastans+y)%n)+1;
		r=std::max((lastans+x)%n,(lastans+y)%n)+1;
		lastans=0;
		bl=bel[l]+1;
		br=bel[r]-1;
		for(ll v=bl;v<=br;v++)
			lastans=std::max(lastans,Max[v][br]);
		for(ll v=l;v<=std::min(ri[bel[l]],r);v++)
			lastans=std::max(lastans,trie[0].query(v,r,ai[v-1]));
		for(ll v=std::max(li[bel[r]],l);v<=r;v++)
			lastans=std::max(lastans,trie[1].query(n-v+1,n-l+1,bi[v+1]));
		printf("%lld\n",lastans);
	}
	return 0;
}
