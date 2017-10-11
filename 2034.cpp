#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=5005;

struct node
{
	int x,y,z,s;
};

struct node a[maxn];

int n,blg[maxn],pos[maxn];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

bool cmpx(const node &u,const node &v)
{
	return u.x<v.x;
}

bool cmpz(const node &u,const node &v)
{
	return u.z>v.z;
}

bool check(int k,int x)
{
	if(pos[x]>a[k].y) return false;
	if(!blg[x])
	{
		blg[x]=k;
		return true;
	}
	else if(a[blg[x]].y<a[k].y)
		return check(k,x+1);
	else if(check(blg[x],x+1))
	{
		blg[x]=k;
		return true;
	}
	else return 0;
}

int main()
{
	read(n);
	for(int i=1;i<=n;i++)
		read(a[i].x),read(a[i].y),read(a[i].z);
	std::sort(a+1,a+n+1,cmpx);
	for(int i=1;i<=n;i++)
		pos[i]=std::max(pos[i-1]+1,a[i].x);
	a[1].s=1;
	for(int i=2;i<=n;i++)
	{
		a[i].s=a[i-1].s;
		while(pos[a[i].s]<a[i].x&&a[i].s<n)
			a[i].s++;
	}
	std::sort(a+1,a+n+1,cmpz);
	long long ans=0;
	for(int i=1;i<=n;i++)
		if(check(i,a[i].s))
			ans+=a[i].z;
	std::cout<<ans;
	return 0;
}
