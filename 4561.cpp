#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef double real;
typedef long long ll;

const real eps=1e-8;
const ll maxn=5e5+5;

struct point
{
	ll x,y;
	
	point(){}
	
	point(ll x_,ll y_)
	{
		x=x_;
		y=y_;
	}
	
	bool operator<(const point &tmp)const
	{
		return x<tmp.x;
	}
};

struct point pi[maxn];

struct halfCir
{
	real x,y,r;
	
	ll tag,id;
};

ll n,xi[maxn],yi[maxn],ri[maxn],nowX,num,deep[maxn];

bool vis[maxn];

std::set<halfCir>Set;

using std::fabs;

bool operator<(const halfCir &a,const halfCir &b)
{
	real A=a.y+std::sqrt(a.r*a.r-(a.x-nowX)*(a.x-nowX))*a.tag;
	real B=b.y+std::sqrt(b.r*b.r-(b.x-nowX)*(b.x-nowX))*b.tag;
	if(fabs(A-B)>eps)
		return A<B;
	return a.tag<b.tag;
}

inline void read(ll &now)
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

int main()
{
	read(n);
	for(ll i=1;i<=n;i++)
	{
		read(xi[i]);
		read(yi[i]);
		read(ri[i]);
		pi[++num]=point(xi[i]-ri[i],i);
		pi[++num]=point(xi[i]+ri[i],i);
	}
	std::sort(pi+1,pi+num+1);
	halfCir tmp;
	std::set<halfCir>::iterator it;
	for(ll i=1;i<=num;i++)
		if(!vis[pi[i].y])
		{
			nowX=pi[i].x;
			vis[pi[i].y]=true;
			tmp.x=xi[pi[i].y];
			tmp.y=yi[pi[i].y];
			tmp.r=ri[pi[i].y];
			tmp.id=pi[i].y;
			tmp.tag=-1;
			it=Set.upper_bound(tmp);
			if(it==Set.end())
				deep[pi[i].y]=1;
			else if((*it).tag==1)
				deep[pi[i].y]=-deep[(*it).id];
			else
				deep[pi[i].y]=deep[(*it).id];
			Set.insert(tmp);
			tmp.tag=1;
			Set.insert(tmp);
		}
		else
		{
			nowX=pi[i].x;
			tmp.x=xi[pi[i].y];
			tmp.y=yi[pi[i].y];
			tmp.r=ri[pi[i].y];
			tmp.id=pi[i].y;
			tmp.tag=1;
			Set.erase(tmp);
			tmp.tag=-1;
			Set.erase(tmp);
		}
	long long ans=0;
	for(ll i=1;i<=n;i++)
		ans+=deep[i]*ri[i]*ri[i];
	std::cout<<ans<<std::endl;
	return 0;
}
