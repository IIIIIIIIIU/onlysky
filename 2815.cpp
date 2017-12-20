#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=7e4+5;
struct EdgeType
{
	int v;
	EdgeType *next;
	EdgeType(){}
	EdgeType(int v_,EdgeType *next_)
	{
		v=v_;
		next=next_;
	}
};
struct EdgeType *head[maxn],*head2[maxn],*head3[maxn];
int n,du[maxn],f[maxn][22],que[maxn],deep[maxn],size[maxn];
inline void read(int &now)
{
	char Cget;
	now=0;
	while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
void add(int x,int fa)
{
	head3[x]=new EdgeType(fa,head3[x]);
	head3[fa]=new EdgeType(x,head3[fa]);
	f[x][0]=fa;
	deep[x]=deep[fa]+1;
	for(int i=1;i<=20;i++)
		f[x][i]=f[f[x][i-1]][i-1];
}
inline int getlca(int x,int y)
{
	if(deep[x]<deep[y])
		std::swap(x,y);
	while(deep[x]!=deep[y])
	{
		for(int i=20;i>=0;i--)
			if((deep[x]-deep[y])&(1<<i))
				x=f[x][i];
	}
	for(int i=20;i>=0;i--)
	{
		if(f[x][i]!=f[y][i])
		{
			x=f[x][i];
			y=f[y][i];
		}
	}
	if(x==y)
		return x;
	return f[x][0];
}
void dfs(int now,int fa)
{
	for(EdgeType *i=head3[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			dfs(i->v,now);
			size[now]+=size[i->v]+1;
		}
}
int main()
{
	read(n);
	++n;
	for(int i=1;i<=n;i++)
	{
		head[i]=NULL;
		head2[i]=NULL;
		head3[i]=NULL;
	}
	for(int i=2,tmp;i<=n;i++)
	{
		read(tmp);
		while(tmp)
		{
			tmp++;
			head[i]=new EdgeType(tmp,head[i]);
			head2[tmp]=new EdgeType(i,head2[tmp]);
			du[i]++;
			read(tmp);
		}
	}
	int h=0,tail=0,now,lca;
	deep[1]=1;
	for(int i=2;i<=n;i++)
		if(!du[i])
		{
			que[tail++]=i;
			head[i]=new EdgeType(1,head[i]);
		}
	while(h<tail)
	{
		now=que[h++];
		lca=head[now]->v;
		for(EdgeType *i=head[now]->next;i!=NULL;i=i->next)
			lca=getlca(lca,i->v);
		add(now,lca);
		for(EdgeType *i=head2[now];i!=NULL;i=i->next)
			if(!(--du[i->v]))
				que[tail++]=i->v;
	}
	dfs(1,0);
	for(int i=2;i<=n;i++)
		printf("%d\n",size[i]);
	return 0;
}
