#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=100005,maxm=maxn*10;
const int dx[9]={0,-1,-1,-1,0,1,1,1,0};
const int dy[9]={0,-1,0,1,1,1,0,-1,-1};

struct point
{
	int x,y,t,id;
	point(int x_=0,int y_=0,int t_=0,int id_=0)
	{
		x=x_,y=y_,t=t_,id=id_;
	}

	bool operator<(const point &pos)const
	{
		if(x==pos.x) return y<pos.y;
		return x<pos.x;
	}
	
	bool operator==(const point &pos)const
	{
		return x==pos.x&&y==pos.y;
	}
};
struct point pi[maxn],ai[maxn];

struct node
{
	int pos,id;
	node(int id_=0,int pos_=0)
	{
		id=id_,pos=pos_;
	}

	bool operator<(const node &tmp)const
	{
		return pos<tmp.pos;
	}
};

int n,r,c,D[maxn],f[maxn],size[maxn],bel[maxn],col,Stack[maxn];
int top,tag,dfn[maxn],low[maxn],que[maxn];

bool vis[maxn];

using std::vector;
using std::set;

vector<int>X[maxm];
vector<int>Y[maxm];
vector<int>Z[maxn];
vector<int>B[maxn];

//map<int,int>has[maxm];

set<point>has;

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

bool cmp(const point &a,const point &b)
{
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}

using std::min;

void tarjan(int now)
{
	dfn[now]=low[now]=++tag,Stack[++top]=now;
	if(ai[now].t==1)
	{
		int pos=ai[now].x;
		for(int i=0;i<X[pos].size();i++)
			if(X[pos][i]!=now&&!bel[X[pos][i]])
			{
				int to=X[pos][i];
				if(dfn[to]) low[now]=min(low[now],dfn[to]);
				else tarjan(to),low[now]=min(low[now],low[to]);
			}
	}
	else if(ai[now].t==2)
	{
		int pos=ai[now].y;
		for(int i=0;i<Y[pos].size();i++)
			if(Y[pos][i]!=now&&!bel[Y[pos][i]])
			{
				int to=Y[pos][i];
				if(dfn[to]) low[now]=min(low[now],dfn[to]);
				else tarjan(to),low[now]=min(low[now],low[to]);
			}
	}
	else
	{
		for(int i=0;i<Z[now].size();i++)
			if(!bel[Z[now][i]])
			{
				int to=Z[now][i];
				if(dfn[to]) low[now]=min(low[now],dfn[to]);
				else tarjan(to),low[now]=min(low[now],low[to]);
			}
	}
	if(low[now]==dfn[now])
	{
		col++;
		while(Stack[top]!=now) ++size[col],bel[Stack[top]]=col,top--;
		++size[col],bel[now]=col,top--;
	}
}

using std::max;

int main()
{
//	freopen("data.txt","r",stdin);
	read(n),read(r),read(c);
	int x,y,t;
	for(int i=1;i<=n;i++)
	{
		read(x),read(y),read(t);
		ai[i]=pi[i]=point(x,y,t,i);
		has.insert(point(x,y,t,i));
	}
	for(int i=1;i<=n;i++) X[pi[i].x].push_back(pi[i].id);
	for(int i=1;i<=n;i++) Y[pi[i].y].push_back(pi[i].id);
	point tmp;
	for(int i=1;i<=n;i++)
		if(ai[i].t==3)
		{
			x=ai[i].x,y=ai[i].y;
			for(int v=1;v<=8;v++)
			{
				int x_=x+dx[v],y_=y+dy[v];
				if(x_>0&&x_<=r&&y_>0&&y_<=c)
				{
					set<point>::iterator it=has.find(point(x_,y_));
					if(it!=has.end()) Z[i].push_back(it->id);
				}
			}
		}
	for(int i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	for(int i=1;i<=n;i++)
	{
		B[bel[i]].push_back(i);
		if(ai[i].t==1)
		{
			int pos=ai[i].x;
			for(int v=0;v<X[pos].size();v++)
				if(X[pos][v]!=i&&bel[X[pos][v]]!=bel[i]) ++D[bel[X[pos][v]]];
		}
		else if(ai[i].t==2)
		{
			int pos=ai[i].y;
			for(int v=0;v<Y[pos].size();v++)
				if(Y[pos][v]!=i&&bel[Y[pos][v]]!=bel[i]) ++D[bel[Y[pos][v]]];
		}
		else
		{
			for(int v=0;v<Z[i].size();v++)
				if(bel[Z[i][v]]!=bel[i]) ++D[bel[Z[i][v]]];
		}
	}
	int h=0,tail=0,ans=0;
	for(int i=1;i<=col;i++) if(!D[i]) que[tail++]=i,vis[i]=true;
	while(h<tail)
	{
		int now=que[h++];
		f[now]+=size[now],ans=std::max(ans,f[now]);
		for(int e=0;e<B[now].size();e++)
		{
			int i=B[now][e];
			if(ai[i].t==1)
			{
				int pos=ai[i].x;
				for(int v=0;v<X[pos].size();v++)
				{
					if(X[pos][v]!=i)
					{
						if(bel[X[pos][v]]!=bel[i]) --D[bel[X[pos][v]]];
						f[bel[X[pos][v]]]=max(f[bel[X[pos][v]]],f[now]);
						if(!D[bel[X[pos][v]]]&&!vis[bel[X[pos][v]]]) que[tail++]=bel[X[pos][v]],vis[bel[X[pos][v]]]=true;
					}
				}
			}
			else if(ai[i].t==2)
			{
				int pos=ai[i].y;
				for(int v=0;v<Y[pos].size();v++)
				{
					if(Y[pos][v]!=i)
					{
						if(bel[Y[pos][v]]!=bel[i]) --D[bel[Y[pos][v]]];
						f[bel[Y[pos][v]]]=max(f[bel[Y[pos][v]]],f[now]);
						if(!D[bel[Y[pos][v]]]&&!vis[bel[Y[pos][v]]]) que[tail++]=bel[Y[pos][v]],vis[bel[Y[pos][v]]]=true;
					}
				}
			}
			else
			{
				for(int v=0;v<Z[i].size();v++)
				{
					if(bel[Z[i][v]]!=bel[i]) --D[bel[Z[i][v]]];
					f[bel[Z[i][v]]]=max(f[bel[Z[i][v]]],f[now]);
					if(!D[bel[Z[i][v]]]&&!vis[bel[Z[i][v]]]) que[tail++]=bel[Z[i][v]],vis[bel[Z[i][v]]]=true;
				}
			}
		}
	}
	std::cout<<ans;
//	vector<int>del;
//	for(int i=0;i<maxm;i++) vector<int>(del).swap(X[i]);
//	for(int i=0;i<maxm;i++) vector<int>(del).swap(Y[i]);
//	std::cout<<std::endl<<(sizeof(X)+sizeof(Y)+sizeof(Z)+sizeof(B))/1024/1024;
//	std::cout<<std::endl<<(sizeof(size)+sizeof(low)+sizeof(dfn)+sizeof(que)+sizeof(vis)+sizeof(f)+sizeof(D))/1024/1024;
	return 0;
}
