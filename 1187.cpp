#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int INF=0x3f3f3f3f;
int s[130],q[10],n,m,top=0,ans=-INF,tot=0;
int a[105][7],c[130][7],f[7][1<<14];
inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while(!isdigit(Cget=getchar()))
		if(Cget=='-')
			if_z=-1;
	while(isdigit(Cget))
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}
inline void R(int &x,int y)
{
	y>x?x=y:0;
}
int main()
{
	read(n);
	read(m);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			read(a[i][v]);
	for(int i=0;i<1<<(m<<1)+2;++i)
	{
		s[++tot]=i;
		top=0;
		for(int v=0;v<=m;v++)
		{
			int x=i>>(v<<1);
			if((x&3)==3)
			{
				top=-1;
				break;
			}
			if((x&3)==1)
				q[++top]=v;
			if((x&3)==2)
			{
				if(!top)
				{
					top=-1;
					break;
				}
				c[tot][v]=q[top];
				c[tot][q[top]]=v;
				--top;
			}
		}
		if(top)
			--tot;
	}
	for(int i=0;i<7;i++)
		for(int v=0;v<1<<14;++v)
			f[i][v]=-INF;
	f[m][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int v=1;v<=tot;v++)
		{
			if(s[v]&3)
				f[0][s[v]]=-INF;
			else
				f[0][s[v]]=f[m][s[v]>>2];
		}
		for(int v=1;v<=m;v++)
		{
			int x=(v-1)<<1;
			for(int k=1;k<=tot;k++)
				f[v][s[k]]=-INF;
			for(int k=1;k<=tot;k++)
			{
				int p=(s[k]>>x)&3,q=(s[k]>>(x+2))&3;
				if(!p&&!q)
				{
					R(f[v][s[k]],f[v-1][s[k]]);
					R(f[v][s[k]^(9<<x)],f[v-1][s[k]]+a[i][v]);
				}
				else if(p&&q)
				{
					if(p==1&&q==1)
						R(f[v][s[k]^(5<<x)^(3<<(c[k][v]<<1))],f[v-1][s[k]]+a[i][v]);
					if(p==1&&q==2)
						if(s[k]==(9<<x))
							R(ans,f[v-1][s[k]]+a[i][v]);
					if(p==2&&q==1)
						R(f[v][s[k]^(6<<x)],f[v-1][s[k]]+a[i][v]);
					if(p==2&&q==2)
						R(f[v][s[k]^(10<<x)^(3<<(c[k][v-1]<<1))],f[v-1][s[k]]+a[i][v]);
				}
				else
				{
					R(f[v][s[k]],f[v-1][s[k]]+a[i][v]);
					R(f[v][s[k]^(p<<x)^(q<<x+2)|(p<<x+2)|(q<<x)],f[v-1][s[k]]+a[i][v]);
				}
			}
		}
	}
	std::cout<<ans;
	return 0;
}
