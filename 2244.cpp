#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;
typedef double real;

const int maxn=1e5+5;

int vi[maxn],hi[maxn],n,bi[maxn],numh,numv,seq[maxn];
int ch[maxn*20][2],root[maxn],val[maxn*20],tot,Ans1;
int f[maxn],pref[maxn],suff[maxn];

real g[maxn],sum[maxn*20],Ans2,preg[maxn],sufg[maxn];

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

void Discrete(int *p,int &Num)
{
	for(int i=1;i<=n;i++)
		bi[++Num]=p[i];
	std::sort(bi+1,bi+Num+1);
	Num=std::unique(bi+1,bi+Num+1)-bi-1;
	for(int i=1;i<=n;i++)
		p[i]=Num-(std::lower_bound(bi+1,bi+Num+1,p[i])-bi)+1;
}

void add(int &now,int pre,int l,int r,int to,int x1,real x2)
{
	now=++tot;
	val[now]=0;
	sum[now]=0;
	if(l==r)
	{
		if(x1>val[pre])
		{
			val[now]=x1;
			sum[now]=x2;
		}
		else if(x1==val[pre])
		{
			val[now]=x1;
			sum[now]=x2+sum[pre];
		}
		else
		{
			val[now]=val[pre];
			sum[now]=sum[pre];
		}
		return;
	}
	int mid=l+r>>1;
	if(to<=mid)
	{
		add(ch[now][0],ch[pre][0],l,mid,to,x1,x2);
		ch[now][1]=ch[pre][1];
	}
	else
	{
		add(ch[now][1],ch[pre][1],mid+1,r,to,x1,x2);
		ch[now][0]=ch[pre][0];
	}
	val[now]=std::max(val[ch[now][0]],val[ch[now][1]]);
	sum[now]=0;
	if(val[ch[now][0]]==val[now])
		sum[now]+=sum[ch[now][0]];
	if(val[ch[now][1]]==val[now])
		sum[now]+=sum[ch[now][1]];
}

void query(int now,int l,int r,int tl,int tr)
{
	if(!now)
		return;
	if(l>=tl&&r<=tr)
	{
		if(val[now]>Ans1)
		{
			Ans1=val[now];
			Ans2=sum[now];
		}
		else if(val[now]==Ans1)
			Ans2+=sum[now];
		return;
	}
	int mid=l+r>>1;
	if(tl<=mid)
		query(ch[now][0],l,mid,tl,tr);
	if(tr>mid)
		query(ch[now][1],mid+1,r,tl,tr);
}

inline int find(int l,int r,int x)
{
	int mid,res=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(hi[seq[mid]]<=x)
		{
			res=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	return res;
}

void solve(int l,int r)
{
	if(l>=r)
		return;
	int mid=l+r>>1;
	solve(l,mid);
	root[l-1]=0;
	tot=0;
	for(int i=l,now;i<=mid;i++)
	{
		now=seq[i];
		add(root[i],root[i-1],1,numv,vi[now],f[now],g[now]);
	}
	for(int i=mid+1,now,pos;i<=r;i++)
	{
		now=seq[i];
		pos=find(l,mid,hi[now]);
		if(pos)
		{
			Ans1=0;
			Ans2=0;
			query(root[pos],1,numv,1,vi[now]);
			if(Ans1+1>f[now])
			{
				f[now]=Ans1+1;
				g[now]=Ans2;
			}
			else if(Ans1+1==f[now])
				g[now]+=Ans2;
		}
	}
	solve(mid+1,r);
	int L=l,R=mid+1,T=l;
	while(L<=mid&&R<=r)
	{
		if(hi[seq[L]]<hi[seq[R]])
			bi[T++]=seq[L++];
		else
			bi[T++]=seq[R++];
	}
	while(L<=mid)
		bi[T++]=seq[L++];
	while(R<=r)
		bi[T++]=seq[R++];
	for(int i=l;i<=r;i++)
		seq[i]=bi[i];
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	for(int i=1;i<=n;i++)
	{
		read(hi[i]);
		read(vi[i]);
	}
	Discrete(hi,numh);
	Discrete(vi,numv);
	for(int i=1;i<=n;i++)
	{
		seq[i]=i;
		f[i]=g[i]=1;
	}
	solve(1,n);
	int MAXLEN=0;
	for(int i=1;i<=n;i++)
	{
		pref[i]=f[i];
		preg[i]=g[i];
		MAXLEN=std::max(MAXLEN,pref[i]);
	}
	for(int i=1;i<=n;i++)
	{
		hi[i]=numh-hi[i]+1;
		vi[i]=numv-vi[i]+1;
		seq[i]=n-i+1;
		f[i]=1;
		g[i]=1;
	}
	solve(1,n);
	real SUM=0;
	for(int i=1;i<=n;i++)
	{
		suff[i]=f[i];
		sufg[i]=g[i];
		if(pref[i]==MAXLEN)
			SUM+=preg[i]*sufg[i];
	}
	printf("%d\n",MAXLEN);
	for(int i=1;i<=n;i++)
		if(pref[i]+suff[i]-1==MAXLEN)
		{
			double tout=(preg[i]*sufg[i]/SUM);
			printf("%.8lf ",tout);
		}
		else
			printf("%.8lf ",0.0);
	return 0;
}
