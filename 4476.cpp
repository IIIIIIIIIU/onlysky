#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const real eps=1e-8;
const int maxn=1e5+5;

int T,n,k,L,R,que[maxn],Log[maxn];

real ai[maxn],bi[maxn],Max[20][maxn],Min[20][maxn];

bool solve(real mid)
{
	real lit=mid*k;
	int h=0,tail=-1;
	for(int i=L,pos=1;i<=n;i++)
	{
		while(h<=tail&&i-que[h]+1>R)
			h++;
		while(i-pos+1>=L)
		{
			while(tail>=h&&ai[pos]>=ai[que[tail]])
				--tail;
			que[++tail]=pos++;
		}
		if(h<=tail&&ai[que[h]]-eps>=ai[i]+lit)
			return true;
	}
	return false;
}

bool check(real mid)
{
	for(int i=1;i<=n;i++)
		ai[i]=bi[i]+mid*i;
	if(solve(mid))
		return true;
	for(int i=n;i>=1;i--)
		ai[n-i+1]=bi[i]+mid*(n-i+1);
	return solve(mid);
}

inline real getMax(int l,int r)
{
	int t=Log[r-l+1];
	return std::max(Max[t][l],Max[t][r-(1<<t)+1]);
}

inline real getMin(int l,int r)
{
	int t=Log[r-l+1];
	return std::min(Min[t][l],Min[t][r-(1<<t)+1]);
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	std::cin>>T;
	Log[1]=0;
	for(int i=2;i<maxn;i++)
		Log[i]=Log[i>>1]+1;
	while(T--)
	{
		std::cin>>n>>k>>L>>R;
		for(int i=1;i<=n;i++)
		{
			std::cin>>bi[i];
			Min[0][i]=bi[i];
			Max[0][i]=bi[i];
		}
		for(int i=1;i<=17;i++)
			for(int v=1;v+(1<<(i-1))-1<=n;v++)
			{
				Min[i][v]=std::min(Min[i-1][v],Min[i-1][v+(1<<(i-1))]);
				Max[i][v]=std::max(Max[i-1][v],Max[i-1][v+(1<<(i-1))]);
			}
		real ans=0;
		for(int i=L;i<=n;i++)
			ans=std::max(ans,(getMax(i-L+1,i)-getMin(i-L+1,i))/(L-1+k));
		for(int i=R;i<=n;i++)
			ans=std::max(ans,(getMax(i-R+1,i)-getMin(i-R+1,i))/(R-1+k));
		real l=0,r=1e3,mid;
		while(l+eps<r)
		{
			mid=(l+r)/2.0;
			if(check(mid))
				l=mid+eps;
			else
				r=mid-eps;
		}
		printf("%.4lf\n",std::max(l,ans));
	}
	return 0;
}
