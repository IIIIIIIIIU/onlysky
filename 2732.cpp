#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long double real;
const real Q=4.0;
const real P=-1.0;
const real INF=1e11;
const real eps=1e-16;
const int maxn=2e5+5;
struct Vector
{
	real x,y;
	Vector(real X=0,real Y=0)
	{
		x=X;
		y=Y;
	}
	Vector operator+(const Vector &a)const
	{
		return Vector(x+a.x,y+a.y);
	}
	Vector operator-(const Vector &a)const
	{
		return Vector (x-a.x,y-a.y);
	}
	real operator*(const Vector &a)const
	{
		return x*a.y-y*a.x;
	}
	Vector mul(real t)
	{
		return Vector(x*t,y*t);
	}
};
struct Vector poly[maxn],p[maxn];
struct line
{
	Vector P,v;
	real ang;
	line()
	{
		P=Vector();
		v=Vector();
	}
	line(Vector A,Vector B)
	{
		P=A;
		v=B-A;
		ang=std::atan2(v.y,v.x);
	}
};
struct line L[maxn],q[maxn];
int n,N,head,tail;
real X[maxn],Y[maxn],Yy[maxn];
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
int comp(line a,line b)
{
	return a.ang<b.ang;
}
Vector GLT(line A,line B)
{
	Vector u=A.P-B.P;
	real t=(B.v*u)/(A.v*B.v);
	return A.P+A.v.mul(t);
}
bool onleft(line A,Vector W)
{
	return A.v*(W-A.P)>-eps;
}
bool halfpins()
{
	std::sort(L+1,L+N+1,comp);
	head=tail=1;
	q[1]=L[1];
	for(int i=2;i<=N;i++)
	{
		while(head<tail&&!onleft(L[i],p[tail-1]))
			--tail;
		while(head<tail&&!onleft(L[i],p[head]))
			++head;
		q[++tail]=L[i];
		if(std::fabs(q[tail].v*q[tail-1].v)<eps)
		{
			--tail;
			if(onleft(q[tail],L[i].P))
				q[tail]=L[i];
		}
		if(head<tail)
			p[tail-1]=GLT(q[tail],q[tail-1]);
	}
	while(head<tail&&!onleft(q[head],p[tail-1]))
		--tail;
	if(tail-head<=1)
		return false;
	return true;
}
bool check(int mid)
{
	Vector A,B,v;
	N=0;
	real x,y,yy,M1,M2;
	for(int i=1;i<=mid;i++)
	{
		x=X[i];
		y=Y[i];
		yy=Yy[i];
		y-=eps;
		yy+=eps;
		B=Vector(P,(yy-x*x*P)/x);
		A=Vector(Q,(yy-x*x*Q)/x);
		L[++N]=line(A,B);
		A=Vector(P,(y-x*x*P)/x);
		B=Vector(Q,(y-x*x*Q)/x);
		L[++N]=line(A,B);
	}
	L[++N]=line(Vector(eps,INF),Vector(-INF,INF));
	L[++N]=line(Vector(-INF,INF),Vector(-INF,eps));
	L[++N]=line(Vector(-INF,eps),Vector(eps,eps));
	L[++N]=line(Vector(eps,eps),Vector(eps,INF));
	return halfpins();
}
int Divide(int l,int r)
{
	int mid,ans=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(check(mid))
		{
			ans=std::max(ans,mid);
			l=mid+1;
		}
		else
			r=mid-1;
	}
	return ans;
}
int main()
{
	read(n);
	for(int i=1,x;i<=n;i++)
	{
		read(x);
		X[i]=x;
		read(x);
		Y[i]=x;
		read(x);
		Yy[i]=x;
	}
	printf("%d\n",Divide(1,n));
	return 0;
}
