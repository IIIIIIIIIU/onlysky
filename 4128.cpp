#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=75;
const int HashHpos=19999;
const int HashMod=2017;

int mod,n,head[HashMod],cnt,E[HashMod],V[HashMod];
int m;

struct Matrix
{
	int n,data[maxn][maxn];
	
	ll Hash;
	
	void MakeHash()
	{
		Hash=0;
		for(short i=1;i<=n;i++)
			for(short v=1;v<=n;v++)
				Hash=(Hash*HashHpos+data[i][v])%HashMod;
	}
	
	bool operator==(const Matrix &tmp)const
	{
		for(short i=1;i<=n;i++)
			for(short v=1;v<=n;v++)
				if(data[i][v]!=tmp.data[i][v])
					return false;
		return true;
	}
	
	Matrix operator*(const Matrix &tmp)const
	{
		Matrix res;
		res.n=n;
		for(short i=1;i<=n;i++)
			for(short v=1;v<=n;v++)
			{
				res.data[i][v]=0;
				for(short e=1;e<=n;e++)
					res.data[i][v]=(res.data[i][v]+data[i][e]*tmp.data[e][v]%mod)%mod;
			}
		return res;
	}
};

struct Matrix W[HashMod],A,B;

inline void AddHash(Matrix X,int id)
{
	X.MakeHash();
	int HashValue=X.Hash;
	E[++cnt]=head[HashValue];
	V[cnt]=id;
	W[cnt]=X;
	head[HashValue]=cnt;
}

void MakeHashTable()
{
	Matrix CMatrix=A;
	Matrix BaseMatrix=B;
	AddHash(BaseMatrix,0);
	for(int i=1;i<=m;i++)
	{
		BaseMatrix=BaseMatrix*CMatrix;
		AddHash(BaseMatrix,i);
	}
}

int Query(Matrix X)
{
	X.MakeHash();
	int t=X.Hash,res=0;
	for(int i=head[t];i!=0;i=E[i])
		if(W[i]==X)
			res=V[i];
	return res;
}

int main()
{
	std::cin>>n>>mod;
	m=std::ceil(std::sqrt(mod*1.0));
	A.n=n;
	B.n=n;
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			std::cin>>A.data[i][v];
	for(int i=1;i<=n;i++)
		for(int v=1;v<=n;v++)
			std::cin>>B.data[i][v];
	B.MakeHash();
	MakeHashTable();
	Matrix CA=A,TA;
	for(int i=2;i<=m;i++)
		CA=CA*A;
	TA=CA;
	int Ans=0;
	for(int i=1;i<=m;i++)
	{
		if(i!=1)
			TA=TA*CA;
		Ans=Query(TA);
		if(Ans)
		{
			Ans=i*m-Ans;
			break;
		}
	}
	std::cout<<Ans<<std::endl;
	return 0;
}
