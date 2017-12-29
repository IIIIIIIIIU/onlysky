#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=305;
int n,m;
bool e[maxn][maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
bool check()
{
	read(n);
	read(m);
	memset(e,false,sizeof(e));
	int x,y;
	for(int i=1;i<=m;i++)
	{
		read(x);
		read(y);
		e[x][y]=true;
	}
	for(int i=0;i<n;i++)
		for(int v=i+1;v<n;v++)
		{
			bool p1=false,p2=false;
			for(int k=0;k<n;k++)
			{
				if(e[i][k]&&e[v][k])
					p1=true;
				if(e[i][k]!=e[v][k])
					p2=true;
				if(p1&&p2)
					return false;
			}
		}
	return true;
}
int main()
{
	int T;
	read(T);
	while(T--)
		if(check())
			puts("Yes");
		else
			puts("No");
	return 0;
}
