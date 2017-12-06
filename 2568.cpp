#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

int tree[17][150010],bit[17],n,m,num;

char op[5];

std::map<int,int>Map;

inline void read(int &now)
{
	char Cget;
	now=0;
	int if_z=1;
	while((Cget=getchar())>'9'||Cget<'0')
		if(Cget=='-')
			if_z=-1;
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
	now*=if_z;
}

inline void add(int base,int x,int v)
{
	for(;x<=bit[base+1];x+=(x&(-x)))
		tree[base][x]+=v;
}

inline int query(int base,int x)
{
	int res=0;
	for(;x;x-=(x&(-x)))
		res+=tree[base][x];
	return res;
}

int main()
{
	read(n);
	bit[0]=1;
	for(int i=1;i<=16;i++)
		bit[i]=bit[i-1]<<1;
	for(int i=1,x,y,k,l,r;i<=n;i++)
	{
		scanf("%s",op);
		if(op[0]=='I')
		{
			read(x);
			for(int v=0;v<=15;v++)
			{
				y=(x-m)%bit[v+1];
				if(y<=0)
					y+=bit[v+1];
				add(v,y,1);
			}
			++Map[x-m];
		}
		else if(op[0]=='D')
		{
			read(x);
			k=Map[x-m];
			if(!k)
				continue;
			Map[x-m]=0;
			for(int v=0;v<=15;v++)
			{
				y=(x-m)%bit[v+1];
				if(y<=0)
					y+=bit[v+1];
				add(v,y,-k);
			}
		}
		else if(op[0]=='A')
		{
			read(x);
			m+=x;
		}
		else
		{
			read(k);
			l=(bit[k]-m)%bit[k+1];
			r=(bit[k+1]-1-m)%bit[k+1];
			if(l<=0)
				l+=bit[k+1];
			if(r<=0)
				r+=bit[k+1];
			if(l<=r)
				printf("%d\n",query(k,r)-query(k,l-1));
			else
				printf("%d\n",query(k,r)-query(k,l-1)+query(k,bit[k+1]));
		}
	}
	return 0;
}
