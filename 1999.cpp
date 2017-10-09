#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=500233;

struct edge
{
	int too,pre,dis;
};

struct edge e[maxn<<1];

struct zs
{
	int id,num;
};

struct zs dll[maxn],q[maxn];

int last[maxn],num[maxn],dl[maxn],f[maxn],p[maxn],s,v,ans;
int dist[4][maxn],i,j,k,a,b,c,n,m,l,r,now,tot,posa,posb,l1,r1;

bool u[maxn],arr[maxn],cant[maxn];

inline void read(int &justval)
{
	char Cget;justval=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')justval=justval*10+Cget-'0',Cget=getchar();
}

inline void insert(int a,int b,int c)
{
	e[++tot].too=b,e[tot].dis=c,e[tot].pre=last[a],last[a]=tot;
	e[++tot].too=a,e[tot].dis=c,e[tot].pre=last[b],last[b]=tot;
}

void bfs(int st,int ed,int id)
{
	int l=0,r=1,now,i,j;
	dl[1]=st,u[st]=1,dist[id][st]=0;
	while(l<r)
	{
		now=dl[++l];
		for(i=last[now];i;i=e[i].pre)
			if(!u[e[i].too])
			{
				dl[++r]=e[i].too,dist[id][e[i].too]=dist[id][now]+e[i].dis,u[e[i].too]=1;
				if(id==3)
					if(dl[r]==ed)
					{
						l=r;
						break;
					}
			}
	}
	memset(u,0,sizeof(u));
	if(id==3)
	{
		arr[ed]=1,num[1]=ed,num[0]=1;
		for(i=r;i;i--)
			if(dist[2][dl[i]]+dist[3][dl[i]]==dist[2][st])
				num[++num[0]]=dl[i],arr[dl[i]]=1;
	}
}

void bii(int x)
{
	int i;u[x]=1;
	for(i=last[x];i;i=e[i].pre)
		if(!arr[e[i].too]&&!u[e[i].too])
		{
			bii(e[i].too);
			f[x]=std::max(f[x],f[e[i].too]+e[i].dis);
		}
}

int main()
{
	read(n),read(s);
	for(i=1;i<n;i++)
		read(a),read(b),read(c),insert(a,b,c);
	bfs(1,0,1),posa=0,dist[1][0]=-1;
	for(i=1;i<=n;i++)
		if(dist[1][i]>dist[1][posa]) posa=i;
	bfs(posa,0,2),posb=0,dist[2][0]=-1;
	for(i=1;i<=n;i++)
		if(dist[2][i]>dist[2][posb]) posb=i;
	bfs(posb,posa,3);
	for(i=1;i<=num[0];i++) bii(num[i]);
	ans=1233333333;
	for(i=1;i<=num[0];i++)
		p[i]=dist[2][num[i]];
	l=1,r=0,l1=1,r1=0;
	for(i=1;i<=num[0];i++)
	{
		while(l<=r&&dist[2][num[i]]-dist[2][num[dll[l].id]]>s)
			cant[dll[l].id]=1,l++;
		while(l1<=r1&&cant[q[l1].id]) l1++;
		while(l1<=r1&&q[r1].num<=f[num[i]]) r1--;
		q[++r1].num=f[num[i]];
		q[r1].id=i;
		dll[++r].num=p[i];
		dll[r].id=i;
		ans=std::min(ans,std::max(std::max(dll[l].num,dist[3][num[i]]),q[l1].num));
	}
	std::cout<<ans;
	return 0;
}
