#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=200005,maxtree=4000005;

int n,root[maxn],val[maxtree],ch[maxtree][2],cnt,tot;

ll ans,count1,count2;

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

void add(int &now,int l,int r,int to)
{
	if(!now) now=++tot;
	val[now]++;
	if(l==r) return;
	int mid=l+r>>1;
	if(to<=mid) add(ch[now][0],l,mid,to);
	else add(ch[now][1],mid+1,r,to);
}

int merge(int x,int y)
{
	if(!x) return y;
	if(!y) return x;
	count1+=(ll)val[ch[x][0]]*val[ch[y][1]];
	count2+=(ll)val[ch[x][1]]*val[ch[y][0]];
	ch[x][0]=merge(ch[x][0],ch[y][0]);
	ch[x][1]=merge(ch[x][1],ch[y][1]);
	val[x]=val[ch[x][0]]+val[ch[x][1]];
	return x;
}

int dfs()
{
	int x;
	read(x);
	if(x)
	{
		add(root[++cnt],1,n,x);
		return cnt;
	}
	int l=dfs();
	int r=dfs();
	count1=0,count2=0;
	merge(root[l],root[r]);
	ans+=std::min(count1,count2);
	return l;
}

int main()
{
	read(n);
	dfs();
	std::cout<<ans;
	return 0;
}
