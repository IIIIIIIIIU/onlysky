#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
typedef long long ll;
const int maxn=1e5+5;
struct node
{
	ll d[2];
};
struct node pi[maxn];
int ch[maxn][2],root,n,m,tot;
ll Max[maxn][2],Min[maxn][2],base[2];
std::priority_queue<ll,std::vector<ll>,std::greater<ll> >que;
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
inline void read(ll &now)
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
inline bool cmp0(const node &x,const node &y)
{
	return x.d[0]<y.d[0];
}
inline bool cmp1(const node &x,const node &y)
{
	return x.d[1]<y.d[1];
}
inline void update(int now)
{
	for(short i=0,v;i<=1;i++)
	{
		Max[now][i]=pi[now].d[i];
		Min[now][i]=pi[now].d[i];
		for(v=0;v<=1;v++)
			if(ch[now][v])
			{
				if(Max[ch[now][v]][i]>Max[now][i])
					Max[now][i]=Max[ch[now][v]][i];
				if(Min[ch[now][v]][i]<Min[now][i])
					Min[now][i]=Min[ch[now][v]][i];
			}
	}
}
int build(int l,int r,int deep)
{
	if(l>r)
		return 0;
	int now=l+r>>1;
	if(deep)
		std::nth_element(pi+l+1,pi+now+1,pi+r+1,cmp1);
	else
		std::nth_element(pi+l+1,pi+now+1,pi+r+1,cmp0);
	if(l<now)
		ch[now][0]=build(l,now-1,deep^1);
	if(r>now)
		ch[now][1]=build(now+1,r,deep^1);
	update(now);
	return now;
}
inline ll get(int x)
{
	return (base[0]-pi[x].d[0])*(base[0]-pi[x].d[0])+(base[1]-pi[x].d[1])*(base[1]-pi[x].d[1]);
}
void Update(int now)
{
	ll tmp=get(now);
	if(tot<m)
	{
		que.push(tmp);
		++tot;
	}
	else if(tmp>que.top())
	{
		que.pop();
		que.push(tmp);
	}
}
inline ll getval(int x)
{
	return std::max((base[0]-Max[x][0])*(base[0]-Max[x][0]),(base[0]-Min[x][0])*(base[0]-Min[x][0]))
		+std::max((base[1]-Max[x][1])*(base[1]-Max[x][1]),(base[1]-Min[x][1])*(base[1]-Min[x][1]));
}
void query(int now)
{
	Update(now);
	ll tmp[2];
	tmp[0]=getval(ch[now][0]);
	tmp[1]=getval(ch[now][1]);
	int to;
	if(tmp[0]>tmp[1])
		to=0;
	else
		to=1;
	if(ch[now][to]&&(tot<m||tmp[to]>que.top()))
		query(ch[now][to]);
	to^=1;
	if(ch[now][to]&&(tot<m||tmp[to]>que.top()))
		query(ch[now][to]);
}
int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(m);
	m<<=1;
	for(int i=1;i<=n;i++)
	{
		read(pi[i].d[0]);
		read(pi[i].d[1]);
	}
	root=build(1,n,0);
	for(int i=1;i<=n;i++)
	{
		base[0]=pi[i].d[0];
		base[1]=pi[i].d[1];
		query(root);
	}
	std::cout<<que.top()<<std::endl;
	return 0;
}
