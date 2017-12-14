#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long double real;
const int maxn=3e5+5;
int n,ai[maxn],que[maxn],bi[maxn];
real fi[maxn],ti[maxn],dp[maxn],S;
inline void read(int &now)
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
bool compare(int i,int j,int k)
{
	return (ti[i]-ti[k])*(dp[k]-dp[j])>=(dp[i]-dp[k])*(ti[k]-ti[j]);
}
bool compare2(int i,int j,int k)
{
	return (dp[j]-dp[k])<fi[i]*(ti[j]-ti[k]);
}
void solve(int l,int r)
{
	if(l>=r)
		return;
	int mid=l+r>>1,h=0,tail=-1;
	solve(l,mid);
	for(int i=l,t;i<=mid;i++)
	{
		t=ai[i];
		while(h<tail&&compare(t,que[tail-1],que[tail]))
			--tail;
		que[++tail]=t;
	}
	for(int i=mid+1,t;i<=r;i++)
	{
		t=ai[i];
		while(h<tail&&compare2(t,que[h+1],que[h]))
			++h;
		dp[t]=std::min(dp[t],dp[que[h]]+(ti[t]-ti[que[h]]+S)*fi[t]);
	}
	solve(mid+1,r);
	int L=l,R=mid+1,M=l;
	while(L<=mid&&R<=r)
		if(ti[ai[L]]<=ti[ai[R]])
			bi[M++]=ai[L++];
		else
			bi[M++]=ai[R++];
	while(L<=mid)
		bi[M++]=ai[L++];
	while(R<=r)
		bi[M++]=ai[R++];
	for(int i=l;i<=r;i++)
		ai[i]=bi[i];
}
int main()
{
	freopen("data.txt","r",stdin);
	int tmp;
	read(n);
	read(tmp);
	S=tmp;
	for(int i=1;i<=n;i++)
	{
		read(tmp);
		ti[i]=tmp;
		read(tmp);
		fi[i]=tmp;
	}
	for(int i=n;i>=1;i--)
	{
		ti[i]+=ti[i+1];
		fi[i]+=fi[i+1];
		ai[n-i+1]=i;
		dp[i]=(ti[i]+S)*fi[i];
	}
	solve(1,n);
	long long ans=dp[1];
	std::cout<<ans;
	return 0;
}
