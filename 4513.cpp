#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
ll t,n,m,k,p,ans,f[65][2][2][2],g[65][2][2][2],bit[65];
inline void read(ll &now)
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
	read(t);
	while(t--)
	{
		read(n);
		read(m);
		read(k);
		read(p);
		bit[0]=1;
		for(int i=1;i<=60;i++)
			bit[i]=(bit[i-1]<<1)%p;
		n--;
		m--;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		ans=0;
		f[0][1][1][1]=1;
		for(int i=0;i<=60;i++)
			for(int a=0;a<=1;a++)
				for(int b=0;b<=1;b++)
					for(int c=0;c<=1;c++)
						if(f[i][a][b][c])
						{
							ll tn=n&(1LL<<(60-i))?1:0;
							ll tm=m&(1LL<<(60-i))?1:0;
							ll tk=k&(1LL<<(60-i))?1:0;
							for(int x=0;x<=1;x++)
								if(!a||x<=tn)
									for(int y=0;y<=1;y++)
										if(!b||y<=tm)
										{
											int z=x^y;
											if(c&&z<tk)
												continue;
											int ta=(a&&x==tn)?1:0;
											int tb=(b&&y==tm)?1:0;
											int tc=(c&&z==tk)?1:0;
											(f[i+1][ta][tb][tc]+=f[i][a][b][c])%=p;
											(g[i+1][ta][tb][tc]+=g[i][a][b][c])%=p;
											if(z)
												(g[i+1][ta][tb][tc]+=bit[60-i]*f[i][a][b][c]%p)%=p;
										}
						}
		for(int a=0;a<=1;a++)
			for(int b=0;b<=1;b++)
				for(int c=0;c<=1;c++)
					ans=((ans+g[61][a][b][c]-k%p*f[61][a][b][c])%p+p)%p;
		printf("%lld\n",ans);
	}
	return 0;
}
