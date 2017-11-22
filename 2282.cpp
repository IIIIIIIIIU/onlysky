#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=3e5+5;

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

struct node
{
	int c,p;
	
	node(){}
	
	node(int c_,int p_)
	{
		c=c_;
		p=p_;
	}
};

struct node Q[maxn];

int n,S,deep[maxn],f[maxn],que[maxn],seq[maxn],cnt;
int val[maxn],deep2[maxn],val2[maxn],ci[maxn];

bool vis[maxn];

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

void bfs(int s)
{
	f[s]=0;
	for(int i=1;i<=n;i++)
		vis[i]=false;
	int h=0,tail=1,now;
	que[0]=s;
	vis[s]=true;
	deep[s]=0;
	while(h<tail)
	{
		now=que[h++];
		for(EdgeType *i=head[now];i!=NULL;i=i->next)
			if(!vis[i->v])
			{
				f[i->v]=now;
				vis[i->v]=true;
				deep[i->v]=deep[now]+i->w;
				que[tail++]=i->v;
			}
	}
}

int bfs2(int s)
{
	int h=0,tail=1;
	que[0]=s;
	int res=0,now;
	val[s]=0;
	while(h<tail)
	{
		now=que[h++];
		for(EdgeType *i=head[now];i!=NULL;i=i->next)
			if(!vis[i->v])
			{
				vis[i->v]=true;
				val[i->v]=val[now]+i->w;
				que[tail++]=i->v;
				if(val[i->v]>res)
					res=val[i->v];
			}
	}
	return res;
}

int main()
{
	freopen("data.txt","r",stdin);
	read(n);
	read(S);
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
	bfs(1);
	int root,s=0,root2;
	for(int i=1;i<=n;i++)
		if(deep[i]>s)
		{
			s=deep[i];
			root=i;
		}
	bfs(root);
	s=0;
	for(int i=1;i<=n;i++)
		if(deep[i]>s)
		{
			s=deep[i];
			root2=i;
		}
	s=root2;
	for(int i=1;i<=n;i++)
		vis[i]=false;
	while(s)
	{
		seq[++cnt]=s;
		s=f[s];
		vis[s]=true;
	}
	int l=1,r=cnt;
	while(l<r)
	{
		std::swap(seq[l],seq[r]);
		l++;
		r--;
	}
	for(int i=1;i<=cnt;i++)
	{
		val[i]=bfs2(seq[i]);
		ci[i]=val[i];
	}
	for(int i=1;i<=n;i++)
		deep2[i]=deep[root2]-deep[i];
	for(int i=1;i<=cnt;i++)
		val2[i]=val[i];
	for(int i=1;i<=cnt;i++)
		val[i]=std::max(val[i-1]+deep[seq[i]]-deep[seq[i-1]],val[i]);
	seq[cnt+1]=0;
	for(int i=cnt;i>=1;i--)
		val2[i]=std::max(val2[i+1]+deep2[seq[i]]-deep2[seq[i+1]],val2[i]);
	l=1;
	int h=0,tail=-1,ans=0x3f3f3f3f;
	for(int i=1;i<=cnt;i++)
	{
		while(deep[seq[i]]-deep[seq[l]]>S)
			l++;
		while(h<=tail&&Q[h].p<l)
			h++;
		while(tail>=h&&ci[i]>=Q[h].c)
			tail--;
		Q[++tail]=node(ci[i],i);
		ans=std::min(ans,std::max(Q[h].c,std::max(val[l],val2[i])));
	}
	std::cout<<ans;
	return 0;
}
