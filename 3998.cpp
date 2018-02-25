#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxn=1e6+5;
int len[maxn],fa[maxn],ch[maxn][26],las,sz;
int opt,n,val[maxn],sum[maxn],v[maxn],q[maxn];
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
void ins(int c)
{
	int now=++sz;
	len[now]=len[las]+1;
	int p,q;
	val[now]=1;
	for(p=las;~p&&!ch[p][c];p=fa[p])
		ch[p][c]=now;
	if(!~p)
		fa[now]=0;
	else
	{
		q=ch[p][c];
		if(len[q]==len[p]+1)
			fa[now]=q;
		else
		{
			int r=++sz;
			fa[r]=fa[q];
			len[r]=len[p]+1;
			for(int i=0;i<26;i++)
				ch[r][i]=ch[q][i];
			for(;~p&&ch[p][c]==q;p=fa[p])
				ch[p][c]=r;
			fa[now]=fa[q]=r;
		}
	}
	las=now;
}
void init()
{
	for(int i=0;i<=sz;i++)
		v[len[i]]++;
	for(int i=1;i<=n;i++)
		v[i]+=v[i-1];
	for(int i=sz;~i;i--)
		q[v[len[i]]--]=i;
	for(int i=sz+1;i;i--)
	{
		int t=q[i];
		if(opt==1)
			val[fa[t]]+=val[t];
		else
			val[t]=1;
	}
	val[0]=0;
	for(int i=sz+1;i;i--)
	{
		int t=q[i];
		sum[t]=val[t];
		for(int j=0;j<26;j++)
			sum[t]+=sum[ch[t][j]];
	}
}
void dfs(int u,int rk)
{
	if(rk<=val[u])
		return;
	rk-=val[u];
	for(int i=0;i<26;i++)
		if(ch[u][i])
		{
			int t=ch[u][i];
			if(rk<=sum[t])
			{
				putchar(i+'a');
				dfs(t,rk);
				return;
			}
			rk-=sum[t];
		}
}
void solve()
{
	init();
	int k;
	read(k);
	dfs(0,k);
}
char s[maxn];
int main()
{
	scanf("%s",s);
	fa[0]=-1;
	n=strlen(s);
	for(int i=0;i<n;i++)
		ins(s[i]-'a');
	scanf("%d",&opt);
	solve();
	return 0;
}
