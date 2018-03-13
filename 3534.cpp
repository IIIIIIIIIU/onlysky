#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;

const int maxn=55;
const real eps=1e-10;

int n;

real D[maxn][maxn],A[maxn][maxn],B[maxn][maxn],t=1;

int main()
{
	std::cin>>n;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
		{
			std::cin>>B[i][v];
			if(i!=v)
			{
				if(B[i][v]==0)
					B[i][v]=eps;
				if(B[i][v]==1)
					B[i][v]-=eps;
			}
			A[i][i]+=B[i][v]/(1-B[i][v]);
			if(v>i)
				t*=(1-B[i][v]);
			B[i][v]/=(1-B[i][v]);
		}
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			D[i][v]=A[i][v]-B[i][v];
	for(int i=1;i<n;i++)
	{
		int now=i;
		for(int v=i+1;v<n;v++)
			if(fabs(D[v][i])>fabs(D[now][i]))
				now=v;
		if(now!=i)
			std::swap(D[now],D[i]);
		for(int v=i+1;v<n;v++)
		{
			real tmp=D[v][i]/D[i][i];
			for(int e=i;e<n;e++)
				D[v][e]-=tmp*D[i][e];
		}
	}
	for(int i=1;i<n;i++)
		t*=D[i][i];
	printf("%.10lf\n",t);
	return 0;
}
