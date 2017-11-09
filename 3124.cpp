#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=2e5+5;

struct EdgeType
{
	int v,w;
	
	EdgeType *next;
	
	EdgeType(){}
	
	EdgeType(int v_,int w_,EdgeType *next_)
	{
		v=v_;
		w=w_;
		next=next_;
	}
};

struct EdgeType *head[maxn];

int n;

ll maxlen,dis[maxn],updis[maxn],cnt,NUM[maxn],ans;
ll fromfa[maxn],fromfanum[maxn],fromson[maxn],fromsonnum[maxn];

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

void dfs1(int now,int fa)
{
	ll tmp1=0,tmp2=0;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			dis[i->v]=dis[now]+i->w;
			dfs1(i->v,now);
			if(updis[i->v]+i->w>=tmp1)
			{
				tmp2=tmp1;
				tmp1=updis[i->v]+i->w;
			}
			else if(updis[i->v]+i->w>tmp2)
				tmp2=updis[i->v]+i->w;
		}
	updis[now]=tmp1;
	maxlen=std::max(maxlen,tmp1+tmp2);
}

void dfs2(int now,int fa)
{
	ll tmp1=0,tmp2=0,num1=0,num2=0,tmp;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			dfs2(i->v,now);
			tmp=updis[i->v]+i->w;
			if(tmp>tmp1)
			{
				num2=num1;
				tmp2=tmp1;
				tmp1=tmp;
				num1=NUM[i->v];
			}
			else if(tmp==tmp1)
				num1+=NUM[i->v];
			else if(tmp>tmp2)
			{
				tmp2=tmp;
				num2=NUM[i->v];
			}
			else if(tmp==tmp2)
				num2+=NUM[i->v];
		}
	if(num1==1)
	{
		if(tmp1==maxlen)
			cnt+=num1;
		else if(tmp1+tmp2==maxlen)
			cnt+=num1*num2;
	}
	else if(num1>1)
	{
		if(tmp1+tmp1==maxlen)
			cnt+=num1*(num1-1)/2;
		else if(tmp1+tmp2==maxlen)
			cnt+=num1*num2;
	}
	updis[now]=tmp1;
	NUM[now]=std::max(num1,1LL);
}

void dfs3(int now,int fa)
{
	ll tmp1=0,num1=0,tmp2=0,num2=0,tmp;
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			tmp=updis[i->v]+i->w;
			if(tmp>tmp1)
			{
				num2=num1;
				tmp2=tmp1;
				tmp1=tmp;
				num1=NUM[i->v];
			}
			else if(tmp==tmp1)
				num1+=NUM[i->v];
			else if(tmp>tmp2)
			{
				tmp2=tmp;
				num2=NUM[i->v];
			}
			else if(tmp==tmp2)
				num2+=NUM[i->v];
		}
	fromson[now]=tmp1;
	fromsonnum[now]=num1;
	tmp=fromfa[now];
	if(tmp>tmp1)
	{
		num2=num1;
		tmp2=tmp1;
		tmp1=tmp;
		num1=fromfanum[now];
	}
	else if(tmp==tmp1)
		num1+=fromfanum[now];
	else if(tmp>tmp2)
	{
		tmp2=tmp;
		num2=fromfanum[now];
	}
	else if(tmp==tmp2)
		num2+=fromfanum[now];
	for(EdgeType *i=head[now];i!=NULL;i=i->next)
		if(i->v!=fa)
		{
			tmp=updis[i->v]+i->w;
			if(tmp==tmp1)
			{
				if(num1==NUM[i->v])
				{
					fromfa[i->v]=tmp2+i->w;
					fromfanum[i->v]=num2;
				}
				else
				{
					fromfa[i->v]=tmp1+i->w;
					fromfanum[i->v]=num1-NUM[i->v];
				}
			}
			else
			{
				fromfa[i->v]=tmp1+i->w;
				fromfanum[i->v]=num1;
			}
			dfs3(i->v,now);
		}
	if(!fromson[now])
		fromsonnum[now]=1;
	if(fromfa[now]+fromson[now]==maxlen&&fromfanum[now]*fromsonnum[now]==cnt)
		ans++;
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	for(int i=1;i<=n;i++)
		head[i]=NULL;
	for(int i=1,u,v,w;i<n;i++)
	{
		read(u);
		read(v);
		read(w);
		head[u]=new EdgeType(v,w,head[u]);
		head[v]=new EdgeType(u,w,head[v]);
	}
	dfs1(1,0);
	dfs2(1,0);
	dfs3(1,0);
	std::cout<<maxlen<<std::endl<<ans;
	return 0;
}
