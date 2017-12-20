#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
ll M,a,c,x0,n,g;
ll mul(ll a,ll b)
{
	ll res=0;
	while(b>0)
	{
		if(b&1)
			(res+=a)%=M;
		(a+=a)%=M;
		b>>=1;
	}
	return res;
}
struct Matrix
{
	int n,m;
	ll data[3][3];
	Matrix operator*(const Matrix &tmp)const
	{
		Matrix res;
		res.n=this->n;
		res.m=tmp.m;
		for(int i=1,v,e;i<=res.n;i++)
			for(v=1;v<=res.m;v++)
			{
				res.data[i][v]=0;
				for(e=1;e<=this->m;e++)
					(res.data[i][v]+=mul(data[i][e],tmp.data[e][v]))%=M;
			}
		return res;
	}
};
struct Matrix A,B;
int main()
{
	std::cin>>M>>a>>c>>x0>>n>>g;
	A.n=1;
	A.m=2;
	A.data[1][1]=x0;
	A.data[1][2]=c;
	B.n=2;
	B.m=2;
	B.data[1][1]=a;
	B.data[2][1]=1;
	B.data[2][2]=1;
	n--;
	Matrix C=B;
	while(n>0)
	{
		if(n&1)
			B=B*C;
		C=C*C;
		n>>=1;
	}
	A=A*B;
	std::cout<<A.data[1][1]%g;
	return 0;
}
