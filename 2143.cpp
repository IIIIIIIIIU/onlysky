#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int dx[5]={0,-1,0,1,0},dy[5]={0,0,1,0,-1};

const ll INF=1e15;

struct node
{
	int x,y,z,d;

	bool operator<(const node &tmp)const
	{
		return d>tmp.d;
	}

	node(int x_=0,int y_=0,int z_=0,int d_=0)
	{
		x=x_,y=y_,z=z_,d=d_;
	}
};

int n,m,ai[155][155],bi[155][155],xi[4],yi[4],ans_id;

ll dis[155][155][305],ans=INF,count[4][4];

bool vis[155][155][305];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

void dijkstra(int x,int y,int tmp)
{
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			for(int e=0;e<=300;e++)
				dis[i][v][e]=INF;
	memset(vis,false,sizeof(vis));
	dis[x][y][0]=0,vis[x][y][0]=false;
	std::priority_queue<node>que;
	que.push(node(x,y,0,0));
	node now;
	int z;
	while(!que.empty()&&(!vis[xi[1]][yi[1]][0]||!vis[xi[2]][yi[2]][0]||!vis[xi[3]][yi[3]][0]))
	{
		now=que.top(),que.pop();
		if(vis[now.x][now.y][now.z]) continue;
		vis[now.x][now.y][now.z]=true;
		if(now.x==3||now.y==4)
		{
			int redwqe=0;
		}
		if(now.z==0)
		{
			if(now.d+ai[now.x][now.y]<dis[now.x][now.y][bi[now.x][now.y]])
			{
				dis[now.x][now.y][bi[now.x][now.y]]=now.d+ai[now.x][now.y];
				que.push(node(now.x,now.y,bi[now.x][now.y],dis[now.x][now.y][bi[now.x][now.y]]));
			}
		}
		else
		{
			if(now.d<dis[now.x][now.y][0])
			{
				dis[now.x][now.y][0]=now.d;
				que.push(node(now.x,now.y,0,now.d));
			}
			for(int i=1;i<=4;i++)
			{
				x=now.x+dx[i],y=now.y+dy[i],z=now.z-1;
				if(x>0&&x<=n&&y>0&&y<=m)
					if(dis[x][y][z]>now.d)
					{
						dis[x][y][z]=now.d;
						que.push(node(x,y,z,now.d));
					}
			}
		}
	}
	count[tmp][1]=dis[xi[1]][yi[1]][0];
	count[tmp][2]=dis[xi[2]][yi[2]][0];
	count[tmp][3]=dis[xi[3]][yi[3]][0];
}

int main()
{
//	freopen("nt2011_fly.in","r",stdin);
//	freopen("nt2011_fly.out","w",stdout);
	read(n),read(m);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
			read(bi[i][v]);
	for(int i=1;i<=n;i++)
		for(int v=1;v<=m;v++)
		{
			read(ai[i][v]);
			if(bi[i][v]>300) bi[i][v]=300;
		}
	for(int i=1;i<=3;i++)
		read(xi[i]),read(yi[i]);
	for(int i=1;i<=3;i++) dijkstra(xi[i],yi[i],i);
	for(int i=1;i<=3;i++)
	{
		if(count[1][i]+count[2][i]+count[3][i]<ans) ans_id=i,ans=count[1][i]+count[2][i]+count[3][i];
	}
	if(ans==INF) std::cout<<"NO";
	else
	{
		if(ans_id==1) puts("X");
		else if(ans_id==2) puts("Y");
		else puts("Z");
		std::cout<<ans;
	}
	return 0;
}
