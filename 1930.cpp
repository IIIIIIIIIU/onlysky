#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=4005,maxm=5000005,INF=0x3f3f;

struct node
{
	int x,y;
	
	bool operator<(const node &pos)const
	{
		if(x==pos.x) return y<pos.y;
		return x<pos.x;
	}
};

struct node point[maxn];

int head[maxn*2],E[maxm],cnt=1,n,s,s_,t;

short V[maxm],W[maxm],F[maxm],que[maxm],pre[maxn*2],dis[maxn*2];

bool vis[maxn*2];

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

inline void edge_add(int u,int v,int w,int f)
{
	E[++cnt]=head[u],V[cnt]=v,W[cnt]=w,F[cnt]=f,head[u]=cnt;
	E[++cnt]=head[v],V[cnt]=u,W[cnt]=-w,F[cnt]=0,head[v]=cnt;
}

bool spfa()
{
	for(int i=s;i<=s_;i++) dis[i]=-INF,pre[i]=-1,vis[i]=false;
	dis[s]=0,que[0]=s,vis[s]=true;int h=0,tail=1,now;
	while(h<tail)
	{
		now=que[h++],vis[now]=false;
		for(int i=head[now];i;i=E[i])
		{
			if(F[i]&&dis[V[i]]<dis[now]+W[i])
			{
				dis[V[i]]=dis[now]+W[i],pre[V[i]]=i;
				if(!vis[V[i]]) que[tail++]=V[i],vis[V[i]]=true;
			}
		}
	}
	return dis[t]!=-INF;
}

int main()
{
//	freopen("data.txt","r",stdin);
//	freopen("data2.txt","r",stdin);
	read(n),s=0,t=n*2+1,s_=t+1;
	for(int i=1;i<=n;i++) read(point[i].x),read(point[i].y);
	std::sort(point+1,point+n+1);
	for(int i=1;i<=n;i++)
		edge_add(i,i+n,1,1),edge_add(i+n,t,0,1),edge_add(s_,i,0,1),edge_add(i,i+n,0,1);
	for(int i=1;i<=n;i++)
	{
		int pos=-1;
		for(int v=i-1;v>=1;v--)
			if(point[v].y>pos&&point[v].y<=point[i].y)
				edge_add(v+n,i,0,2),pos=point[v].y;
	}
	edge_add(s,s_,0,2);
	int ans=0;
	while(spfa())
	{
		int now=t;
		while(pre[now]!=-1) F[pre[now]]--,F[pre[now]^1]++,now=V[pre[now]^1];
		ans+=dis[t];
	}
	std::cout<<ans;
	return 0;
}
