#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int mn=2e3+5;
int n,p,c[mn][mn],f[mn][mn],g[mn*mn];
int main(){
	scanf("%d%d",&n,&p);
	c[0][0]=f[1][1]=1;
	g[0]=1;
	for(int i=1;i<=n*n;i++)
		g[i]=g[i-1]*2%p;
	for(int i=1;i<=n;i++){
		c[i][0]=1;
		for(int v=1;v<=i;v++)
			c[i][v]=(c[i-1][v]+c[i-1][v-1])%p;
	}
	for(int i=2;i<=n;i++){
		f[i][1]=g[(i-1)*(i-2)/2];
		for(int v=2;v<i;v++)
			f[i][v]=1LL*f[v][v]*c[i-1][v-1]%p*g[(i-v)*(i-v-1)/2]%p;
		f[i][i]=g[i*(i-1)/2];
		for(int v=1;v<i;v++)
			(f[i][i]+=p-f[i][v])%=p;
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",f[n][i]);
	return 0;
}
