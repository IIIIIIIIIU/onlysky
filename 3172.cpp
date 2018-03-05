#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=1e6+5;

int n,m,ch[maxn][26],fail[maxn],ans[maxn],tot=1;
int que[maxn],p[205];

char str[maxn];

int main()
{
	std::cin>>n;
	for(int i=1,now;i<=n;i++)
	{
		now=1;
		std::cin>>str+1;
		int len=strlen(str+1);
		for(int v=1;v<=len;v++)
		{
			if(!ch[now][str[v]-'a'])
				ch[now][str[v]-'a']=++tot;
			now=ch[now][str[v]-'a'];
			ans[now]++;
		}
		p[i]=now;
	}
	int h=0,tail=1;
	que[0]=1;
	while(h<tail)
	{
		int now=que[h++];
		for(int i=0;i<26;i++)
			if(ch[now][i])
			{
				if(now==1)
					fail[ch[now][i]]=1;
				else
				{
					int temp=fail[now];
					while(temp&&!ch[temp][i])
						temp=fail[temp];
					if(!temp)
						fail[ch[now][i]]=1;
					else
						fail[ch[now][i]]=ch[temp][i];
				}
				que[tail++]=ch[now][i];
			}
	}
	for(int i=tail-1;i>=1;i--)
		ans[fail[que[i]]]+=ans[que[i]];
	for(int i=1;i<=n;i++)
		std::cout<<ans[p[i]]<<std::endl;
	return 0;
}
