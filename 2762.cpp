#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int M=1e5+1e2;
const int RANGE=1e6;
int n,tot;
std::pair<int,int>intervals[M];
bool v[M];
int c[RANGE<<1|0xffff];
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
inline void Update(int x,int y)
{
	for(;x<=(RANGE<<1|1);x+=x&-x)
		c[x]+=y;
}
inline int Get_Ans(int x)
{
	int re=0;
	for(;x;x-=x&-x)
		re+=c[x];
	return re;
}
std::pair<int,int>Get_Interval(int a,int b,int c)
{
	if(a==0)
	{
		if(b>c)
			return std::make_pair(-RANGE,RANGE);
		else return std::make_pair(1,0);
	}
	else if(a>0)
	{
		int temp=floor(double(c-b)/a+1);
		if(temp<-RANGE)
			return std::make_pair(-RANGE,RANGE);
		if(temp>RANGE)
			return std::make_pair(1,0);
		return std::make_pair(temp,RANGE);
	}
	else
	{
		int temp=ceil(double(c-b)/a-1);
		if(temp>RANGE)
			return std::make_pair(-RANGE,RANGE);
		if(temp<-RANGE)
			return std::make_pair(1,0);
		return std::make_pair(-RANGE,temp);
	}
}
inline void Update(std::pair<int,int>x,int y)
{
	Update(x.first+RANGE+1,y);
	Update(x.second+RANGE+2,-y);
}
int main()
{
	int i,a,b,c,x;
	char p[10];
	read(n);
	for(i=1;i<=n;i++)
	{
		scanf("%s",p);
		switch(p[0])
		{
			case 'A':
				read(a);
				read(b);
				read(c);
				intervals[++tot]=Get_Interval(a,b,c);
				Update(intervals[tot],1);
				break;
			case 'Q':
				read(x);
				printf("%d\n",Get_Ans(x+RANGE+1));
				break;
			case 'D':
				read(x);
				if(v[x])
					break;
				v[x]=1;
				Update(intervals[x],-1);
				break;
		}
	}
	return 0;
}
