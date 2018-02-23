#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
struct use
{
	ll v;
	int t,pre,p;
};
struct use temp;
int k,p[50],f[200],num,i,v;
ll n,t;
std::priority_queue<use>q;
bool operator<(const use &a,const use &b)
{
	return a.v<b.v;
}
int main()
{
	std::cin>>n>>k;
	for(i=2;i<=128;i++)
		if(!f[i])
		{
			p[++num]=i;
			int x=i;
			while(x<=128)
				f[x+=i]=1;
		}
	for(i=1;i<=num;i++)
		for(t=v=1;(t*p[i])<=n;++v)
			q.push(use{t*=p[i],v,i-1,i});
	while(k--)
	{
		temp=q.top();
		q.pop();
		if(temp.t>1)
			for(i=temp.pre;i;i--)
				q.push(use{temp.v/p[temp.p]*p[i],temp.t-1,i,temp.p});
	}
	std::cout<<temp.v<<std::endl;
	return 0;
}
