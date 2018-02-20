#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=5e4+5;
int pi[maxn],num,mu[maxn];
bool vis[maxn];
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
void pre()
{
	mu[1]=1;
	for(int i=2;i<maxn;i++)
	{
		if(!vis[i])
		{
			pi[++num]=i;
			mu[i]=-1;
		}
		for(int v=1;v<=num&&pi[v]*i<maxn;v++)
		{
			vis[pi[v]*i]=true;
			if(i%pi[v]==0)
				break;
			mu[i*pi[v]]=-mu[i];
		}
	}
	for(int i=2;i<maxn;i++)
		mu[i]+=mu[i-1];
}
int get(int n,int m,int k)
{
	if(!n||!m)
		return 0;
	n/=k;
	m/=k;
	if(n>m)
		std::swap(n,m);
	int res=0;
	for(int i=1,nxt;i<=n;i=nxt+1)
	{
		nxt=std::min(n/(n/i),m/(m/i));
		res+=(mu[nxt]-mu[i-1])*(n/i)*(m/i);
	}
	return res;
}
int main()
{
	freopen("data.txt","r",stdin);
	pre();
	int N,a,b,c,d,k;
	read(N);
	while(N--)
	{
		read(a);
		read(c);
		read(b);
		read(d);
		read(k);
		printf("%d\n",get(c,d,k)-get(a-1,d,k)-get(c,b-1,k)+get(a-1,b-1,k));
	}
	return 0;
}
