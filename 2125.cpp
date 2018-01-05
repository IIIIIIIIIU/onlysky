#include <map>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e5+5;
int n,head[maxn],E[maxn],V[maxn],cnt=1,seq[maxn],kop,dfn[maxn];
int m,q,W[maxn],f[maxn],tag[maxn],ai[maxn],li[maxn],ri[maxn],size[maxn];
int col,stack[maxn],top,num,deep[maxn],val[maxn],gi[maxn],stackw[maxn];
int fi[maxn][21],ci[maxn][21];
bool vis[maxn];
std::map<int,int>Map[maxn/10+1];
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
void dfs(int now,int last,int w)
{
	dfn[now]=++kop;
	vis[now]=true;
	stack[++top]=now;
	stackw[top]=w;
	for(int i=head[now];i!=0;i=E[i])
		if(i!=(last^1))
		{
			if(dfn[V[i]]>dfn[now])
				continue;
			if(vis[V[i]])
			{
				int v;
				++col;
				li[col]=num;
				ri[col]=num;
				seq[li[col]]=V[i];
				Map[col][V[i]]=li[col];
				++n;
				tag[n]=col;
				stackw[top+1]=W[i];
				for(v=top;stack[v]!=V[i];v--)
				{
					seq[++ri[col]]=stack[v];
					f[stack[v]]=n;
					Map[col][stack[v]]=ri[col];
					gi[ri[col]]=gi[ri[col]-1]+stackw[v+1];
				}
				seq[++ri[col]]=V[i];
				gi[ri[col]]=stackw[v+1]+gi[ri[col]-1];
				size[col]=ri[col]-li[col];
				f[n]=V[i];
				for(v=li[col]+1;v<ri[col];v++)
				{
					f[seq[v]]=n;
					val[seq[v]]=std::min(gi[v]-gi[li[col]],gi[ri[col]]-gi[v]);
				}
				for(v=top;stack[v]!=V[i];v--)
				{
					seq[++ri[col]]=stack[v];
					gi[ri[col]]=gi[ri[col]-1]+stackw[v+1];
				}
				num=ri[col]+1;
			}
			else
			{
				dfs(V[i],i,W[i]);
				if(!f[V[i]])
				{
					f[V[i]]=now;
					val[V[i]]=W[i];
				}
			}
		}
	vis[now]=false;
	top--;
}
void dfs2(int now)
{
	deep[now]=deep[f[now]]+1;
	val[now]+=val[f[now]];
	for(int i=head[now];i!=0;i=E[i])
		dfs2(V[i]);
}
int getval(int bel,int x,int y)
{
	int idx=Map[bel][x],idy=Map[bel][y];
	if(idx>idy)
		std::swap(idx,idy);
	return std::min(gi[idy]-gi[idx],gi[idx+size[bel]]-gi[idy]);
}
int getdis(int x,int y)
{
	int a=x,b=y;
	if(deep[a]<deep[b])
		std::swap(a,b);
	int t=deep[a]-deep[b];
	for(int i=17;i>=0;i--)
		if(t&(1<<i))
			a=fi[a][i];
	for(int i=17;i>=0;i--)
		if(fi[a][i]!=fi[b][i])
		{
			a=fi[a][i];
			b=fi[b][i];
		}
	if(a!=b)
		a=fi[a][0];
	if(!tag[a])
		return val[x]+val[y]-val[a]*2;
	else
	{
		int X=x;
		t=deep[x]-deep[a]-1;
		for(int i=17;i>=0;i--)
			if(t&(1<<i))
				X=fi[X][i];
		int Y=y;
		t=deep[y]-deep[a]-1;
		for(int i=17;i>=0;i--)
			if(t&(1<<i))
				Y=fi[Y][i];
		return val[x]-val[X]+val[y]-val[Y]+getval(tag[a],X,Y);
	}
}
int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	read(n);
	read(m);
	read(q);
	for(int i=1,u,v,w;i<=m;i++)
	{
		read(u);
		read(v);
		read(w);
		E[++cnt]=head[u];
		V[cnt]=v;
		W[cnt]=w;
		head[u]=cnt;
		E[++cnt]=head[v];
		V[cnt]=u;
		W[cnt]=w;
		head[v]=cnt;
	}
	dfs(1,0,0);
	memset(head,0,sizeof(head));
	cnt=0;
	for(int i=1;i<=n;i++)
	{
		fi[i][0]=f[i];
		if(f[i])
		{
			E[++cnt]=head[f[i]];
			V[cnt]=i;
			W[cnt]=val[i];
			head[f[i]]=cnt;
		}
	}
	dfs2(1);
	for(int i=1;i<=17;i++)
		for(int v=1;v<=n;v++)
			fi[v][i]=fi[fi[v][i-1]][i-1];
	for(int i=1,x,y;i<=q;i++)
	{
		read(x);
		read(y);
		printf("%d\n",getdis(x,y));
	}
	return 0;
}
