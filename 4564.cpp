#include <bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm 300005
struct QueryType
{
	int l,r,y,id,key,op;
	bool operator<(const QueryType &pos) const
	{
		if(key==pos.key) return r<pos.r;
		return key<pos.key;
	}
};
struct QueryType qu[maxn];
int n,m,ai[maxn],head[maxn],E[maxm],V[maxm],bel[maxn];
int dfn[maxn],low[maxn],sta[maxn],top,f[maxn],tag,cnt=1;
int li[maxn],ri[maxn],num[maxn],bi[maxn],size,ans[maxn];
int blo3[2][maxn],litb[maxn],numb,ci[maxn],sta2[maxn];
bool vis[maxn];
inline void in(int &now)
{
	char Cget=getchar();now=0;
	while(Cget>'9'||Cget<'0') Cget=getchar();
	while(Cget>='0'&&Cget<='9')
	{
		now=now*10+Cget-'0';
		Cget=getchar();
	}
}
void tarjan(int now,int fa,int last)
{
	dfn[now]=low[now]=++tag,f[now]=fa,sta[++top]=now;
	for(int i=head[now];i;i=E[i])
	{
		if(i==last||i==(last^1)) continue;
		if(dfn[V[i]]) low[now]=min(low[now],dfn[V[i]]),vis[V[i]]=true;
		else tarjan(V[i],now,i),low[now]=min(low[now],low[V[i]]);
	}
	if(low[now]==dfn[now])
	{
		while(sta[top]!=now)
			f[sta[top--]]=now;
		top--;
	}
	else if(vis[now])
	{
		int top2=0;
		while(sta[top]!=now)
		{
			if(low[sta[top]]<=low[now]) sta2[++top2]=sta[top--];
			else f[sta[top--]]=now;
		}
		while(top2) sta[++top]=sta2[top2--];
	}
}
void dfs(int now)
{
	li[now]=++cnt,ci[cnt]=ai[now];
	for(int i=head[now];i;i=E[i])
		if(V[i]!=f[now]) dfs(V[i]);
	ri[now]=cnt;
}
inline int find(int x)
{
	int l=1,r=size,mid,res=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(bi[mid]<=x) res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}
void updata(int now,bool di)
{
	int x=ci[now];
	if(di)
	{
		if(num[x]) blo3[num[x]%2][bel[x]]--;
		num[x]++,blo3[num[x]%2][bel[x]]++;
	}
	else
	{
		blo3[num[x]%2][bel[x]]--,num[x]--;
		if(num[x]) blo3[num[x]%2][bel[x]]++;
	}
}
int main()
{
	in(n),in(m);int u,v;
	for(int i=1;i<=n;i++) in(ai[i]),bi[i]=ai[i];
	sort(bi+1,bi+n+1),size=unique(bi+1,bi+n+1)-bi-1;
	int blo=sqrt(n),blo2=sqrt(size);
	for(int i=1;i<=n;i++) ai[i]=find(ai[i]);
	for(int i=1;i<=size;i++) bel[i]=((i-1)/blo2)+1,numb=bel[i],litb[bel[i]]=i;
	for(int i=1;i<=m;i++)
	{
		in(u),in(v);
		E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
		E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
	}
	tarjan(1,0,0),cnt=0;
	for(int i=1;i<=n;i++) head[i]=0;
	for(int i=2;i<=n;i++)
	{
		u=i,v=f[i];
		E[++cnt]=head[u],V[cnt]=v,head[u]=cnt;
		E[++cnt]=head[v],V[cnt]=u,head[v]=cnt;
	}
	cnt=0,dfs(1),in(m);
	for(int i=1;i<=m;i++)
	{
		in(qu[i].op),in(qu[i].l),in(qu[i].y);
		qu[i].r=ri[qu[i].l],qu[i].l=li[qu[i].l],qu[i].id=i,qu[i].key=qu[i].l/blo;
	}
	sort(qu+1,qu+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++)
	{
		while(l>qu[i].l) updata(--l,true);
		while(r<qu[i].r) updata(++r,true);
		while(r>qu[i].r) updata(r--,false);
		while(l<qu[i].l) updata(l++,false);
		int res=0,lit=find(qu[i].y);
		for(int v=1;v<=numb;v++)
			if(lit>=litb[v]) res+=blo3[qu[i].op][v];
			else
			{
				for(int k=litb[v-1]+1;k<=lit;k++)
					if(num[k]%2==qu[i].op&&num[k]) res++;
				break;
			}
		ans[qu[i].id]=res;
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
