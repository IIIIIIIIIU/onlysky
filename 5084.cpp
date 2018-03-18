#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxn=2e5+5;

int lt,nd,t,l[maxn],nxt[maxn],to[maxn][26],*a[maxn];
int b[maxn],s[maxn];

char q[maxn];

ll ans;

bool f[maxn];

void add(int &x)
{
	a[++t]=&x;
	b[t]=x;
	s[nd]++;
}

void nsrt(int c)
{
	int x=++nd,p=lt,q;
	l[lt=x]=l[p]+1;
	s[nd]=0;
	memset(to[x],0,sizeof(to[x]));
	f[nd]=0;
	while(p&&!to[p][c])
	{
		add(to[p][c]);
		to[p][c]=x;
		p=nxt[p];
	}
	if(!p)
		nxt[x]=1;
	else
		if(l[q=to[p][c]]==l[p]+1)
			nxt[x]=q;
		else
		{
			int y=++nd;
			l[y]=l[p]+1;
			f[nd]=1;
			s[nd]=0;
			memcpy(to[y],to[q],sizeof(to[y]));
			nxt[y]=nxt[q];
			add(nxt[q]);
			nxt[q]=nxt[x]=y;
			while(to[p][c]==q)
			{
				add(to[p][c]);
				to[p][c]=y;
				p=nxt[p];
			}
		}
	ans+=l[x]-l[nxt[x]];
}

int main()
{
	scanf("%s",q+1);
	nd=lt=1;
	for(int i=1;q[i];i++)
	{
		if(islower(q[i]))
			nsrt(q[i]-'a');
		else
			for(int j=0,k=f[nd];j<=k;j++)
			{
				for(int p=1;p<=s[nd];p++,t--)
					*a[t]=b[t];
				if(!f[nd])
					ans-=l[nd]-l[nxt[nd]];
				lt=--nd;
			}
		if(f[lt])
			lt--;
		printf("%lld\n",ans);
	}
	return 0;
}
