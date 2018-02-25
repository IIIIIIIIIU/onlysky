#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef unsigned int uint;
struct Matrix
{
	int n,m;
	uint a[1<<6|1][1<<6|1];
	Matrix(){}
	Matrix(int n_,int m_)
	{
		n=n_;
		m=m_;
		for(int i=1;i<=n;i++)
			for(int v=1;v<=m;v++)
				a[i][v]=0;
	}
	Matrix operator*(const Matrix &tmp)const
	{
		Matrix res(n,tmp.m);
		for(int i=1;i<=res.n;i++)
			for(int v=1;v<=res.m;v++)
				for(int e=1;e<=m;e++)
					res.a[i][v]+=a[i][e]*tmp.a[e][v];
		return res;
	}
};
int n,m,p,k,ai[3][7],bit[11],bi[1<<7][1<<7];
bool di[1<<7];
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
bool check(int s)
{
	for(int i=1;i<=m;i++)
		if(bit[i]&s)
		{
			for(int v=1;v<=k&&i-v>=1;v++)
				if(ai[1][k-v]&&(bit[i-v]&s))
					return false;
			for(int v=k+1;v<p&&i+v-k<=m;v++)
				if(ai[1][v]&&(bit[i+v-k]&s))
					return false;
		}
	return true;
}
bool check(int x,int y)
{
	for(int i=1;i<=m;i++)
	{
		if(bit[i]&x)
		{
			for(int v=0;v<=k&&i-v>=1;v++)
				if(ai[2][k-v]&&(bit[i-v]&y))
					return false;
			for(int v=k+1;v<p&&i+v-k<=m;v++)
				if(ai[2][v]&&(bit[i+v-k]&y))
					return false;
		}
		if(bit[i]&y)
		{
			for(int v=0;v<=k&&i-v>=1;v++)
				if(ai[0][k-v]&&(bit[i-v]&x))
					return false;
			for(int v=k+1;v<p&&i+v-k<=m;v++)
				if(ai[0][v]&&(bit[i+v-k]&x))
					return false;
		}
	}
	return true;
}
int main()
{
	read(n);
	read(m);
	read(p);
	read(k);
	bit[1]=1;
	for(int i=2;i<=7;i++)
		bit[i]=bit[i-1]<<1;
	for(int i=0;i<3;i++)
		for(int v=0;v<p;v++)
			read(ai[i][v]);
	for(int s=0;s<(1<<m);s++)
		di[s]=check(s);
	Matrix t(1<<m,1<<m);
	for(int s1=0;s1<(1<<m);s1++)
		for(int s2=0;s2<(1<<m);s2++)
			if(di[s1]&&di[s2])
			{
				bi[s1][s2]=check(s1,s2);
				t.a[s1+1][s2+1]=bi[s1][s2];
			}
	Matrix base(1,1<<m);
	base.a[1][1]=1;
	while(n>0)
	{
		if(n&1)
			base=base*t;
		n>>=1;
		t=t*t;
	}
	uint ans=0;
	for(int i=1;i<=(1<<m);i++)
		ans+=base.a[1][i];
	std::cout<<ans<<std::endl;
	return 0;
}
