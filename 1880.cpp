#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn=2005,maxm=1000005;
struct P
{
	int id,dist;
	bool operator<(const P &pos)const
	{
		return dist>pos.dist;
	}
	P(int id_=0,int dist_=0)
	{
		id=id_,dist=dist_;
	}
};
struct node
{
	int u,v,w;
	void makeit(int u_,int v_,int w_)
	{
		u=u_,v=v_,w=w_;
	}
};
struct node edge[maxm];
int n,m,head[maxn],E[maxm],V[maxm],W[maxm],cnt,dis[4][maxn],S[4];
int times[maxm],que2[maxn],deg[maxn],f[maxn];
bool vis[4][maxn];
inline void in(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}
void dijkstra(int tag)
{
	int s=S[tag];
	priority_queue<P>que;
	dis[tag][s]=0,que.push(P(s,0));
	P now;
	while(!que.empty())
	{
		now=que.top(),que.pop();
		if(vis[tag][now.id]) continue;
		vis[tag][now.id]=true;
		for(int i=head[now.id];i;i=E[i])
			if(dis[tag][V[i]]>dis[tag][now.id]+W[i])
			{
				dis[tag][V[i]]=dis[tag][now.id]+W[i];
				que.push(P(V[i],dis[tag][V[i]]));
			}
	}
}
inline bool can(int tag)
{
	int u=edge[tag].u,v=edge[tag].v,w=edge[tag].w;
//	if(min(dis[0][u],dis[1][u])+min(dis[0][v],dis[1][v])+w!=dis[0][S[1]]) return false;
//	if(min(dis[2][u],dis[3][u])+min(dis[2][v],dis[3][v])+w!=dis[2][S[3]]) return false;
	if(min(dis[0][u],dis[0][v])+min(dis[1][u],dis[1][v])+w!=dis[0][S[1]]) return false;
	if(min(dis[2][u],dis[2][v])+min(dis[3][u],dis[3][v])+w!=dis[2][S[3]]) return false;
	return true;
}
int main()
{
	//freopen("travel!.in","r",stdin);
	//freopen("travel!.out","w",stdout);
	in(n),in(m);
	int u,v,w;
	for(int i=0;i<=3;i++) in(S[i]);
	for(int i=1;i<=m;i++)
	{
		in(u),in(v),in(w);
		E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,head[u]=cnt;
		E[++cnt]=head[v],V[cnt]=u,W[cnt]=w,head[v]=cnt;
		edge[i].makeit(u,v,w);
	}
	memset(dis,0x3f,sizeof(dis));
	for(int i=0;i<=3;i++) dijkstra(i);
	memset(head,0,sizeof(head)),cnt=0;
	for(int i=1;i<=m;i++)
		if(can(i))
		{
			if(dis[0][edge[i].u]<dis[0][edge[i].v]) u=edge[i].u,v=edge[i].v;
			else u=edge[i].v,v=edge[i].u;
			E[++cnt]=head[u],V[cnt]=v,W[cnt]=edge[i].w,head[u]=cnt,deg[v]++;
		}
	int h=0,tail=0,now;
	for(int i=1;i<=n;i++)
		if(!deg[i])
			que2[tail++]=i;
	while(h<tail)
		for(int i=head[now=que2[h++]];i;i=E[i])
		{
			if(f[now]+W[i]>f[V[i]]) f[V[i]]=f[now]+W[i];
			if((--deg[V[i]])==0) que2[tail++]=V[i];
		}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,f[i]);
	cout<<ans;
	return 0;
}
