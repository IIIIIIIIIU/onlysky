#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int maxn=200005,INF=0x3f3f3f3f;

class LinkCutTreeType
{
	private:
		struct TreeNode
		{
			int BaseKey,BaseID,key,id;

			bool rev;

			TreeNode *f,*ch[2];

			TreeNode(int BaseKey_=-1,int BaseID_=0)
			{
				id=BaseID=BaseID_;
				key=BaseKey=BaseKey_;
				rev=false;
				f=ch[0]=ch[1]=NULL;
			}

			inline void updata()
			{
				key=BaseKey;
				id=BaseID;
				if(ch[0])
					if(ch[0]->key>key) key=ch[0]->key,id=ch[0]->id;
				if(ch[1])
					if(ch[1]->key>key) key=ch[1]->key,id=ch[1]->id;
			}

			inline void rotate()
			{
				TreeNode *fa=this->f,*ffa=fa->f;bool l=(fa->ch[1]==this),r=l^1;
				if(!fa->isroot()) ffa->ch[ffa->ch[1]==fa]=this;
				this->f=ffa,fa->ch[l]=this->ch[r],fa->f=this,this->ch[r]=fa;
				if(fa->ch[l]!=NULL) fa->ch[l]->f=fa;fa->updata();
			}

			inline bool isroot()
			{
				if(this->f==NULL) return true;
				return f->ch[1]!=this&&f->ch[0]!=this;
			}

			inline void pushdown()
			{
				if(rev)
				{
					std::swap(ch[0],ch[1]);
					if(ch[0]!=NULL) ch[0]->rev^=1;
					if(ch[1]!=NULL) ch[1]->rev^=1;
					rev^=1;
				}
			}
		};

		struct TreeNode *Stack[maxn],node[maxn];

		int top;

		int findroot(int x)
		{
			access(x);
			splay(x);
			TreeNode *res=&node[x];
			while(res->ch[0]!=NULL) res=res->ch[0];
			return res->BaseID;
		}

	public:
		void splay(int x)
		{
			TreeNode *tmp=&node[x],*fa,*ffa;
			top=0;
			Stack[++top]=tmp;
			for(tmp=&node[x];!tmp->isroot();tmp=tmp->f) Stack[++top]=tmp->f;
			while(top)
			{
				Stack[top]->pushdown();
				top--;
			}
			tmp=&node[x];
			while(!tmp->isroot())
			{
				fa=tmp->f;
				if(!fa->isroot())
				{
					ffa=fa->f;
					if((ffa->ch[1]==fa)^(fa->ch[1]==tmp)) tmp->rotate();
					else fa->rotate();
				}
				tmp->rotate();
			}
			tmp->updata();
		}

		void access(int x)
		{
			for(TreeNode *tmp=NULL,*now=&node[x];now!=NULL;tmp=now,now=now->f)
			{
				splay(now->BaseID);
				now->ch[1]=tmp;
				now->updata();
			}
		}

		void makeroot(int x)
		{
			access(x);
			splay(x);
			node[x].rev^=1;
		}

		bool connect(int x,int y)
		{
			return findroot(x)==findroot(y);
		}

		void link(int x,int y)
		{
			makeroot(x);
			node[x].f=&node[y];
//			splay(x);
//			access(x);
		}

		void cut(int x,int y)
		{
			makeroot(x);
			access(y);
			splay(y);
			node[y].ch[0]=node[x].f=NULL;
			node[y].updata();
		}

		int getkey(int x,int y)
		{
			makeroot(x);
			access(y);
			splay(y);
			return node[y].key;
		}

		inline int getid(int y)
		{
			return node[y].id;
		}

		void makeit(int key,int id)
		{
			node[id]=TreeNode(key,id);
		}
};

class LinkCutTreeType LCT;

struct EdgeType
{
	int u,v,a,b;
	EdgeType(int u_=0,int v_=0,int a_=0,int b_=0)
	{
		u=u_,v=v_,a=a_,b=b_;
	}

	bool operator<(const EdgeType &pos)const
	{
		return a<pos.a;
	}
};

struct EdgeType edge[maxn];

int n,m,ans=INF;

inline void read(int &now)
{
	char Cget;now=0;while((Cget=getchar())>'9'||Cget<'0');
	while(Cget>='0'&&Cget<='9')now=now*10+Cget-'0',Cget=getchar();
}

int main()
{
//	freopen("data.txt","r",stdin);
	read(n),read(m);
	int u,v,a,b;
	for(int i=1;i<=m;i++)
	{
		read(u),read(v),read(a),read(b);
		edge[i]=EdgeType(u,v,a,b);
	}
	std::sort(edge+1,edge+m+1);
	for(int i=1;i<=m;i++) LCT.makeit(edge[i].b,i+n);
	for(int i=1;i<=n;i++) LCT.makeit(-1,i);
	for(int i=1;i<=m;i++)
	{
		EdgeType tmp=edge[i];
		if(LCT.connect(tmp.u,tmp.v))
		{
			int tmpkey=LCT.getkey(tmp.u,tmp.v);
			if(tmpkey>tmp.b)
			{
				int tmpid=LCT.getid(tmp.v)-n;
				LCT.cut(edge[tmpid].u,tmpid+n);
				LCT.cut(edge[tmpid].v,tmpid+n);
				LCT.link(edge[i].u,i+n);
				LCT.link(edge[i].v,i+n);
				if(LCT.connect(1,n))
				{
					ans=std::min(ans,edge[i].a+LCT.getkey(1,n));
				}
			}
		}
		else
		{
			LCT.link(tmp.u,i+n);
			LCT.link(tmp.v,i+n);
			if(LCT.connect(1,n))
			{
				ans=std::min(ans,edge[i].a+LCT.getkey(1,n));
			}
		}
	}
	if(ans==INF) std::cout<<-1;
	else std::cout<<ans;
	return 0;
}
