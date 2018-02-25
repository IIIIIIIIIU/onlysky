#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=3e5+5;
int n,Log[maxn],pre[maxn],suf[maxn];
struct SaffixArray
{
	int t[maxn],t2[maxn],sa[maxn<<1],c[maxn];
	int height[maxn][20],rank[maxn];
	char s[maxn];
	void init()
	{
		memset(c,0,sizeof(c));
		memset(s,0,sizeof(s));
		memset(t,0,sizeof(t));
		memset(sa,0,sizeof(sa));
		memset(t2,0,sizeof(t2));
		memset(rank,0,sizeof(rank));
		memset(height,0,sizeof(height));
	}
	void buildSa(int M)
	{
		int *x=t,*y=t2;
		for(int i=1;i<=M;i++)
			c[i]=0;
		for(int i=1;i<=n;i++)
			c[x[i]=s[i]]++;
		for(int i=1;i<=M;i++)
			c[i]+=c[i-1];
		for(int i=n;i>=1;i--)
			sa[c[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1)
		{
			int p=0;
			for(int i=n-k+1;i<=n;i++)
				y[++p]=i;
			for(int i=1;i<=n;i++)
				if(sa[i]>k)
					y[++p]=sa[i]-k;
			for(int i=1;i<=M;i++)
				c[i]=0;
			for(int i=1;i<=n;i++)
				c[x[y[i]]]++;
			for(int i=1;i<=M;i++)
				c[i]+=c[i-1];
			for(int i=n;i>=1;i--)
				sa[c[x[y[i]]]--]=y[i];
			std::swap(x,y);
			p=x[sa[1]]=1;
			for(int i=2;i<=n;i++)
				x[sa[i]]=y[sa[i]]==y[sa[i-1]] && y[sa[i]+k]==y[sa[i-1]+k]?p:++p;
			if(p>=n)
				break;
			M=p;
		}
		std::memcpy(rank,x,sizeof(rank));
		int k=0;
		for(int i=1;i<=n;i++)
		{
			int v=sa[rank[i]+1];
			if(k)
				k--;
			if(!v)
				continue;
			while(s[i+k]==s[v+k])
				k++;
			height[rank[i]][0]=k;
		}
		for(int v=1;v<=16;v++)
			for(int i=1;i+(1<<v)<=n;i++)
				height[i][v]=std::min(height[i][v-1],height[i+(1<<(v-1))][v-1]);
	}
	int LCP(int x,int y)
	{
		x=rank[x];
		y=rank[y];
		if(x>y)
			std::swap(x,y);
		int t=Log[y-x];
		return std::min(height[x][t],height[y-(1<<t)][t]);
	}
};
struct SaffixArray A,B;
char s[maxn];
int main()
{
	for(int i=2;i<maxn;i++)
		Log[i]=Log[i>>1]+1;
	int T;
	scanf("%d",&T);
	while(T--)
	{
		A.init();
		B.init();
		memset(pre,0,sizeof(pre));
		memset(suf,0,sizeof(suf));
		scanf("%s",s+1);
		n=strlen(s+1);
		for(int i=1;i<=n;i++)
			A.s[i]=B.s[n+1-i]=s[i];
		A.buildSa('z');
		B.buildSa('z');
		for(int l=1;l<=n/2;l++)
			for(int i=l,v=i+l;v<=n;i+=l,v+=l)
			{
				int R=std::min(A.LCP(i,v),l);
				int L=std::min(B.LCP(n+1-(i-1),n+1-(v-1)),l-1);
				if(L+R>=l)
				{
					pre[v-L+l-1]++;
					pre[v+R]--;
					suf[i-L]++;
					suf[i+R-l+1]--;
				}
			}
		for(int i=1;i<=n;i++)
		{
			pre[i]+=pre[i-1];
			suf[i]+=suf[i-1];
		}
		long long ans=0;
		for(int i=1;i<=n;i++)
			ans+=pre[i]*suf[i+1];
		std::cout<<ans<<std::endl;
	}
	return 0;
}
