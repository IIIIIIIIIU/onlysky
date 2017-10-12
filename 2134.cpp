#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

const int maxn=10000005;

ll n,a[maxn],A,B,C;

real ans;

int main()
{
//	freopen("nt2011_exp.in","r",stdin);
//	freopen("nt2011_exp.out","w",stdout);
	std::cin>>n>>A>>B>>C>>a[1];
	for(int i=2;i<=n;i++) a[i]=(a[i-1]*A+B)%100000001;
	for(int i=1;i<=n;i++) a[i]=a[i]%C+1;
	a[0]=a[n];
	for(int i=1;i<=n;i++) ans+=1/(real)std::max(a[i],a[i-1]);
	printf("%.3lf",ans);
	return 0;
}
