#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=55,mod=10000;

struct Matrix
{
	int n,m,ai[maxn][maxn];
	Matrix operator*(const Matrix &pos)const
	{
		Matrix res;
		res.n=n,res.m=pos.m;
		for(int i=0;i<=res.n;i++)
			for(int v=0;v<=res.m;v++)
			{
				res.ai[i][v]=0;
				for(int e=0;e<=m;e++)
					(res.ai[i][v]+=ai[i][e]*pos.ai[e][v])%=mod;
			}
		return res;
	}
	
	void debug()
	{
		for(int i=0;i<=n;i++)
		{
			printf("\n");
			for(int v=0;v<=m;v++) printf("%d ",ai[i][v]);
		}
		printf("\n");
	}
};

struct Matrix BaseMat[13],C,Ans;

int n,m,s,t,k,size=1,q,map[maxn][maxn],pi[maxn][maxn],T[maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

inline int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}

inline int lcm(int a,int b)
{
	return a*b/gcd(a,b);
}

Matrix pow(Matrix base,int mi)
{
	Matrix res=base;mi--;
	while(mi)
	{
		if(mi&1) res=res*base;
		mi>>=1,base=base*base;
	}
	return res;
}

int main()
{
//	freopen("data.txt","r",stdin);
	read(n),read(m),read(s),read(t),read(k);
	int x,y;
	for(int i=1;i<=m;i++)
	{
		read(x),read(y);
		map[x][y]++;
		map[y][x]++;
	}
//	for(int i=0;i<n;i++)
//	{
//		for(int v=0;v<n;v++) printf("%d ",map[i][v]);
//		printf("\n");
//	}
//	printf("\n");
	read(q);
	for(int i=1;i<=q;i++)
	{
		read(T[i]),size=lcm(size,T[i]);
		for(int v=1;v<=T[i];v++) read(pi[i][v]);
	}
	for(int i=1;i<=size;i++)
	{
		BaseMat[i].n=n-1,BaseMat[i].m=n-1;
		for(int v=0;v<n;v++)
			for(int e=0;e<n;e++)
				BaseMat[i].ai[v][e]=map[v][e];
		for(int v=1;v<=q;v++)
		{
			int tmp=pi[v][i%T[v]+1];
			for(int e=0;e<n;e++) BaseMat[i].ai[e][tmp]=0;
		}
//		BaseMat[i].debug();
	}
	C.n=C.m=n-1;
	for(int i=0;i<n;i++) C.ai[i][i]=1;
//	C.debug();
	if(k<=size)
	{
//		BaseMat[1].debug();
		for(int i=1;i<=k;i++)
		{
			C=C*BaseMat[i];
//			C.debug();
//			BaseMat[i].debug();
		}
		std::cout<<C.ai[s][t];
		return 0;
	}
	for(int i=1;i<=size;i++) C=C*BaseMat[i];
//	C.debug();
	if(k/size) C=pow(C,k/size);
	else
	{
		for(int i=0;i<n;i++) C.ai[i][i]=1;
	}
	k%=size;
	for(int i=1;i<=k;i++) C=C*BaseMat[i];
//	C.debug();
	std::cout<<C.ai[s][t];
	return 0;
}
