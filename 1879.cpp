#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int p=1000003;
int T,n,k,l,N,ans;
char ch[16][55];
int f[55][1<<15],g[55][27];
int main()
{
	for(scanf("%d",&T);T;T--)
	{
		scanf("%d%d",&n,&k);
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		for(int i=0;i<n;i++) scanf("%s",ch[i]);
		N=1<<n,l=strlen(ch[0]);
		f[0][N-1]=1,ans=0;
		for(int i=0;i<l;i++)
			for(char c='a';c<='z';c++)
				for(int k=0,mat=1;k<n;k++,mat<<=1)
					if(ch[k][i]=='?'||ch[k][i]==c)
						g[i][c-'a']|=mat;
		for(int i=0;i<l;i++)
			for(int v=0;v<N;v++)
				if(f[i][v])
					for(char c='a';c<='z';c++)
						f[i+1][v&g[i][c-'a']]+=f[i][v],f[i+1][v&g[i][c-'a']]%=p;
		for(int cnt=0,i=0;i<N;i++)
		{
			cnt=0;
			for(int v=1;v<N;v<<=1)
				cnt+=(bool)(i&v);
			if(cnt==k) (ans+=f[l][i])%=p;
		}
		printf("%d\n",ans);
	}
	return 0;
}
