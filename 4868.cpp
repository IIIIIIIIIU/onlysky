#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e5+5;
int ti[maxn],n,m,bi[maxn],a,b,c;
ll ans=1e18,sumt[maxn],sumb[maxn];
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
int main()
{
	read(a);
	read(b);
	read(c);
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		read(ti[i]);
	for(int i=1;i<=m;i++)
		read(bi[i]);
	std::sort(ti+1,ti+n+1);
	std::sort(bi+1,bi+m+1);
	for(int i=1;i<=n;i++)
		sumt[i]=sumt[i-1]+ti[i];
	for(int i=1;i<=m;i++)
		sumb[i]=sumb[i-1]+bi[i];
	ll pt=0,pb=0;
	for(int tim=0;tim<=bi[m];tim++)
	{
		while(pt<n&&ti[pt+1]<tim)
			pt++;
		while(pb<m&&bi[pb+1]<tim)
			pb++;
		ll sumbl=pb*tim-sumb[pb];
		ll sumbr=sumb[m]-sumb[pb]-(m-pb)*tim;
		ll res=std::min(sumbr*b,std::min(sumbl,sumbr)*a+(sumbr-std::min(sumbl,sumbr))*b);
		res+=(pt*tim-sumt[pt])*c;
		ans=std::min(ans,res);
	}
	std::cout<<ans<<std::endl;
	return 0;
}
