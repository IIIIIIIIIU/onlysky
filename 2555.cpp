#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e6+2e5+5;

namespace LinkCutTree
{
	int f[maxn],ch[maxn][2],stack[maxn],val[maxn];
	int top,tag[maxn];
	
	inline bool isroot(const int &x)
	{
		return ch[f[x]][1]!=x&&ch[f[x]][0]!=x;
	}
	
	inline void add(const int &x,const int &y)
	{
		if(x)
		{
			tag[x]+=y;
			val[x]+=y;
		}
	}
	
	inline void pushdown(int x)
	{
		if(tag[x])
		{
			add(ch[x][0],tag[x]);
			add(ch[x][1],tag[x]);
			tag[x]=0;
		}
	}
	
	inline void rotate(int x)
	{
		int fa=f[x],ffa=f[fa],l=(ch[fa][1]==x),r=(l^1);
		if(!isroot(fa))
			ch[ffa][ch[ffa][1]==fa]=x;
		f[x]=ffa;
		f[fa]=x;
		ch[fa][l]=ch[x][r];
		ch[x][r]=fa;
		if(ch[fa][l])
			f[ch[fa][l]]=fa;
	}
	
	inline void splay(int x)
	{
		int fa=f[x],ffa=f[fa];
		stack[top=1]=fa=x;
		while(!isroot(fa))
		{
			stack[++top]=f[fa];
			fa=f[fa];
		}
		while(top)
			pushdown(stack[top--]);
		while(!isroot(x))
		{
			fa=f[x];
			ffa=f[fa];
			if(!isroot(fa))
			{
				if(ch[ffa][1]==fa^ch[fa][1]==x)
					rotate(x);
				else
					rotate(fa);
			}
			rotate(x);
		}
	}
	
	inline void access(int x)
	{
		for(int t=0;x;t=x,x=f[x])
		{
			splay(x);
			ch[x][1]=t;
		}
	}
	
	inline void link(int x,int y)
	{
		f[x]=y;
		access(y);
		splay(y);
		add(y,val[x]);
	}
	
	inline void cut(int x)
	{
		access(x);
		splay(x);
		add(ch[x][0],-val[x]);
		ch[x][0]=f[ch[x][0]]=0;
	}
	
	inline int query(int x)
	{
		splay(x);
		return val[x];
	}
}

namespace SuffixAutomaton
{
	int last=1,tot=1,f[maxn],len[maxn],ch[maxn][26],mask=0,ans=0;
	
	char str[3000005];
	
	void extend(int c)
	{
		int np,p,q,nq;
		len[np=++tot]=len[last]+1;
		LinkCutTree::val[np]=1;
		for(p=last;p&&!ch[p][c];p=f[p])
			ch[p][c]=np;
		if(!p)
		{
			f[np]=1;
			LinkCutTree::link(np,1);
		}
		else
		{
			q=ch[p][c];
			if(len[q]==len[p]+1)
			{
				f[np]=q;
				LinkCutTree::link(np,q);
			}
			else
			{
				nq=++tot;
				len[nq]=len[p]+1;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				f[nq]=f[q];
				LinkCutTree::link(nq,f[q]);
				f[np]=f[q]=nq;
				LinkCutTree::cut(q);
				LinkCutTree::link(q,nq);
				LinkCutTree::link(np,nq);
				for(;ch[p][c]==q;p=f[p])
					ch[p][c]=nq;
			}
		}
		last=np;
	}
	
	void build()
	{
		scanf("%s",str);
		int L=strlen(str);
		for(int i=0;i<L;i++)
			extend(str[i]-'A');
	}
	
	int GetString(int Mask)
	{
		char tmp;
		scanf("%s",str);
		int L=strlen(str);
		for(int i=0;i<L;i++)
		{
			Mask=(Mask*131+i)%L;
			tmp=str[i];
			str[i]=str[Mask];
			str[Mask]=tmp;
		}
//		puts(str);
		return L;
	}
	
	void ADD()
	{
		int L=GetString(mask);
		for(int i=0;i<L;i++)
			extend(str[i]-'A');
	}
	
	int QUERY()
	{
		int L=GetString(mask);
		int now=1;
		for(int i=0;i<L;i++)
		{
			now=ch[now][str[i]-'A'];
			if(!now)
				break;
		}
		ans=0;
		if(now)
			ans=LinkCutTree::query(now);
		mask^=ans;
		return ans;
	}
}

int main()
{
	freopen("data.txt","r",stdin);
	freopen("ans1.txt","w",stdout);
	int n;
	scanf("%d",&n);
	SuffixAutomaton::build();
	char op[25];
	while(n--)
	{
		scanf("%s",op);
		if(*op=='A')
			SuffixAutomaton::ADD();
		else
			printf("%d\n",SuffixAutomaton::QUERY());
	}
	return 0;
}
