#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef double real;
typedef long long ll;
typedef unsigned long long ull;
const int mod=1e9+7;
const real lit=0.77;
const int maxn=1e5+5;
int n,ch[maxn][2],tot,root,f[maxn];
int seq[maxn],size[maxn],pos,need,cnt,ai[maxn];
real key[maxn],li[maxn],ri[maxn];
ll sum[maxn],height[maxn];
ull Hash[maxn],hpos[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	while(!isdigit((Cget=getchar())));
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
bool cmp(int x,int y)
{
	if(seq[x]!=seq[y])
		return seq[x]<seq[y];
	if(y-1)
		return key[x-1]<key[y-1];
	return false;
}
void insert(int &now,int x,real l,real r)
{
	if(!now)
	{
		now=x;
		size[now]=1;
		li[now]=l;
		ri[now]=r;
		key[now]=(l+r)/2;
		return;
	}
	if(cmp(x,now))
	{
		insert(ch[now][0],x,l,key[now]);
		f[ch[now][0]]=now;
	}
	else
	{
		insert(ch[now][1],x,key[now],r);
		f[ch[now][1]]=now;
	}
	size[now]=size[ch[now][0]]+size[ch[now][1]]+1;
	sum[now]=sum[ch[now][0]]+sum[ch[now][1]]+height[now];
	if(1.0*size[ch[now][0]]/size[now]>lit)
	{
		need=0;
		pos=now;
	}
	if(1.0*size[ch[now][1]]/size[now]>lit)
	{
		need=1;
		pos=now;
	}
}
void check(int now)
{
	if(!now)
		return;
	check(ch[now][0]);
	ai[++cnt]=now;
	check(ch[now][1]);
}
int build(int l,int r,real L,real R)
{
	int mid=l+r>>1;
	li[ai[mid]]=L;
	ri[ai[mid]]=R;
	key[ai[mid]]=(L+R)/2;
	if(mid>l)
		ch[ai[mid]][0]=build(l,mid-1,L,key[ai[mid]]);
	else
		ch[ai[mid]][0]=0;
	if(mid<r)
		ch[ai[mid]][1]=build(mid+1,r,key[ai[mid]],R);
	else
		ch[ai[mid]][1]=0;
	if(ch[ai[mid]][0])
		f[ch[ai[mid]][0]]=ai[mid];
	if(ch[ai[mid]][1])
		f[ch[ai[mid]][1]]=ai[mid];
	size[ai[mid]]=size[ch[ai[mid]][0]]+size[ch[ai[mid]][1]]+1;
	sum[ai[mid]]=sum[ch[ai[mid]][0]]+sum[ch[ai[mid]][1]]+height[ai[mid]];
	f[ai[mid]]=0;
	return ai[mid];
}
int rk(int now,int x)
{
	if(x==now)
		return 1+size[ch[now][0]];
	if(key[x]<key[now])
		return rk(ch[now][0],x);
	else
		return rk(ch[now][1],x)+size[ch[now][0]]+1;
}
int find(int k)
{
	int now=root;
	while(true)
	{
		if(size[ch[now][0]]>=k)
			now=ch[now][0];
		else
		{
			k-=size[ch[now][0]];
			if(k==1)
				return now;
			k--;
			now=ch[now][1];
		}
	}
}
inline ull getHash(int l,int r)
{
	return Hash[r]-Hash[l-1]*hpos[r-l+1];
}
inline int get(int x,int y)
{
	int res=0,l=1,r=std::min(x,y),mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(getHash(x-mid+1,x)==getHash(y-mid+1,y))
		{
			res=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	return res;
}
void update(int now,int to,int x)
{
	if(now==to)
		height[to]=x;
	else
	{
		if(key[to]<key[now])
			update(ch[now][0],to,x);
		else
			update(ch[now][1],to,x);
	}
	sum[now]=sum[ch[now][0]]+sum[ch[now][1]]+height[now];
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	hpos[0]=1;
	for(int i=1,x,tmp,t;i<=n;i++)
	{
		read(x);
		seq[++tot]=x;
		hpos[i]=hpos[i-1]*mod;
		Hash[i]=Hash[i-1]*mod+seq[i];
		pos=0;
		insert(root,i,0,1);
		if(pos)
		{
			cnt=0;
			if(f[pos])
			{
				if(key[pos]<key[f[pos]])
				{
					check(pos);
					tmp=f[pos];
					ch[tmp][0]=build(1,cnt,li[tmp],key[tmp]);
					f[ch[tmp][0]]=tmp;
				}
				else
				{
					check(pos);
					tmp=f[pos];
					ch[tmp][1]=build(1,cnt,key[tmp],ri[tmp]);
					f[ch[tmp][1]]=tmp;
				}
			}
			else
			{
				check(root);
				root=build(1,cnt,0,1);
			}
		}
		tmp=rk(root,i);
		if(tmp!=i)
		{
			x=find(tmp+1);
			t=get(i,x);
			update(root,x,t);
		}
		if(tmp!=1)
		{
			x=find(tmp-1);
			t=get(i,x);
			update(root,i,t);
		}
		printf("%lld\n",1LL*i*(i-1)/2+i-sum[root]);
	}
	return 0;
}
