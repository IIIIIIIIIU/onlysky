#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e7+5;
const int INF=0x3f3f3f3f;

#define min(x,y) ((x)<(y)?(x):(y))

struct node
{
	short x,y;
	
	int d;
	
	node(){}
	
	node(const register short &x_,const register short &y_,const register int &d_)
	{
		x=x_;
		y=y_;
		d=d_;
	}
	
	inline bool operator<(register const node &tmp)const
	{
		return d>tmp.d;
	}
};

struct Query
{
	int id,x1,y1,x2,y2;
};

struct Query Q[maxn],tagNow;

int n,m,q,ci[151][20001],di[151][20001];
int head[maxn],cnt,E[maxn],sum[maxn],ch[maxn][2];
int dis[151][20001],ans[100005],tot,root;

bool vis[151][20001];

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

void add(int &now,int upX,int downX,int upY,int downY)
{
	if(upX>downX||upY>downY)
		return;
	if(now==0)
		now=++tot;
	sum[now]++;
	E[++cnt]=head[now];
	Q[cnt]=tagNow;
	head[now]=cnt;
	int lenx=downX-upX+1;
	int leny=downY-upY+1;
	if(lenx>leny)
	{
		int mid=downX+upX>>1;
		if(tagNow.x1<mid&&tagNow.x2<mid)
			add(ch[now][0],upX,mid-1,upY,downY);
		else if(tagNow.x1>mid&&tagNow.x2>mid)
			add(ch[now][1],mid+1,downX,upY,downY);
	}
	else
	{
		int mid=downY+upY>>1;
		if(tagNow.y1<mid&&tagNow.y2<mid)
			add(ch[now][0],upX,downX,upY,mid-1);
		else if(tagNow.y1>mid&&tagNow.y2>mid)
			add(ch[now][1],upX,downX,mid+1,downY);
	}
}

void dijkstra(int sx,int sy,int upX,int downX,int upY,int downY,int k)
{
	for(int v,i=upX;i<=downX;i++)
		for(v=upY;v<=downY;v++)
			(k<=0)?dis[i][v]=INF:dis[i][v]+=k;
	for(int v,i=upX;i<=downX;i++)
		for(v=upY;v<=downY;v++)
			vis[i][v]=false;
	dis[sx][sy]=0;
	std::priority_queue<node>que;
	que.push(node(sx,sy,0));
	node now;
	register short x,y;
	while(!que.empty())
	{
		now=que.top();
		que.pop();
		if(vis[now.x][now.y])
			continue;
		vis[now.x][now.y]=true;
		x=now.x-1;
		y=now.y;
		if(x>=upX&&x<=downX&&y>=upY&&y<=downY&&dis[x][y]>dis[now.x][now.y]+di[x][y])
			que.push(node(x,y,dis[x][y]=dis[now.x][now.y]+di[x][y]));
		x=now.x+1;
		if(x>=upX&&x<=downX&&y>=upY&&y<=downY&&dis[x][y]>dis[now.x][now.y]+di[now.x][now.y])
			que.push(node(x,y,dis[x][y]=dis[now.x][now.y]+di[now.x][now.y]));
		x=now.x;
		y=now.y-1;
		if(x>=upX&&x<=downX&&y>=upY&&y<=downY&&dis[x][y]>dis[now.x][now.y]+ci[x][y])
			que.push(node(x,y,dis[x][y]=dis[now.x][now.y]+ci[x][y]));
		y=now.y+1;
		if(x>=upX&&x<=downX&&y>=upY&&y<=downY&&dis[x][y]>dis[now.x][now.y]+ci[now.x][now.y])
			que.push(node(x,y,dis[x][y]=dis[now.x][now.y]+ci[now.x][now.y]));
	}
}

void solve(int now,int upX,int downX,int upY,int downY)
{
	if(!now||upX>downX||upY>downY||!sum[now])
		return;
	int lenx=downX-upX+1;
	int leny=downY-upY+1;
	if(lenx>leny)
	{
		int mid=downX+upX>>1;
		for(int i=upY;i<=downY;i++)
		{
			dijkstra(mid,i,upX,downX,upY,downY,dis[mid][i]);
			for(int v=head[now];v!=0;v=E[v])
				ans[Q[v].id]=min(ans[Q[v].id],dis[Q[v].x1][Q[v].y1]+dis[Q[v].x2][Q[v].y2]);
		}
		solve(ch[now][0],upX,mid-1,upY,downY);
		solve(ch[now][1],mid+1,downX,upY,downY);
	}
	else
	{
		int mid=downY+upY>>1;
		for(int i=upX;i<=downX;i++)
		{
			dijkstra(i,mid,upX,downX,upY,downY,dis[i][mid]);
			for(int v=head[now];v!=0;v=E[v])
				ans[Q[v].id]=min(ans[Q[v].id],dis[Q[v].x1][Q[v].y1]+dis[Q[v].x2][Q[v].y2]);
		}
		solve(ch[now][0],upX,downX,upY,mid-1);
		solve(ch[now][1],upX,downX,mid+1,downY);
	}
}

inline void swap(int &a,int &b)
{
	int t=b;
	b=a;
	a=t;
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	bool rev=false;
	if(n<=m)
	{
		for(int i=1;i<=n;i++)
			for(int v=1;v<m;v++)
				read(ci[i][v]);
		for(int i=1;i<n;i++)
			for(int v=1;v<=m;v++)
				read(di[i][v]);
	}
	else
	{
		rev=true;
		for(int i=1;i<=n;i++)
			for(int v=1;v<m;v++)
				read(di[v][i]);
		for(int i=1;i<n;i++)
			for(int v=1;v<=m;v++)
				read(ci[v][i]);
		swap(n,m);
	}
	read(q);
	for(int i=1;i<=q;i++)
	{
		ans[i]=INF;
		tagNow.id=i;
		read(tagNow.x1);
		read(tagNow.y1);
		read(tagNow.x2);
		read(tagNow.y2);
		if(rev)
		{
			swap(tagNow.x1,tagNow.y1);
			swap(tagNow.x2,tagNow.y2);
		}
		if(tagNow.x1>tagNow.x2)
		{
			swap(tagNow.x1,tagNow.x2);
			swap(tagNow.y1,tagNow.y2);
		}
		add(root,1,n,1,m);
	}
	solve(root,1,n,1,m);
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
