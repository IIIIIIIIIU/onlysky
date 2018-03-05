#include <cstdio>

typedef double real;

const int maxn=55;

int n,m,ai[maxn];

real f[maxn][maxn];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&ai[i]);
	f[1][1]=1;
	for(int i=2;i<=n;i++)
		for(int v=1;v<=i;v++)
			for(int e=1,t;e<=m;e++)
			{
				t=(ai[e]%i==0)?i:(ai[e]%i);
				if(t<v)
					f[i][v]+=f[i-1][v-t]/m;
				if(t>v)
					f[i][v]+=f[i-1][i-t+v]/m;
			}
	for(int i=1;i<=n;i++)
	{
		printf("%.2lf",f[n][i]*100);
		putchar('%');
		if(i!=n)
			putchar(' ');
	}
	return 0;
}
