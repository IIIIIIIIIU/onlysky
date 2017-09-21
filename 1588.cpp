#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
struct TreeNode {
    int key,fix,weight,size;
     
    TreeNode *left,*right;
};
 
class TreapType {
    private:
        TreeNode *null,*root,*start;
         
        int n,if_z,pos,ans;
         
        char Cget;
         
        inline void read_int(int &now)
        {
            now=0,if_z=1,Cget=getchar();
            while(Cget>'9'||Cget<'0')
            {
                if(Cget=='-') if_z=-1;
                Cget=getchar();
            }
            while(Cget>='0'&&Cget<='9')
            {
                now=now*10+Cget-'0';
                Cget=getchar();
            }
            now*=if_z;
        }
         
    public:
        TreapType()
        {
            null=new TreeNode;
            null->left=null;
            null->right=null;
            root=null;
            start=new TreeNode;
            start->key=0x7ffffff;
            start->left=null;
            start->right=null;
            read_int(n);
            read_int(pos);
            ans+=abs(pos);
            Insert(root,pos);
            for(int i=2;i<=n;i++)
            {
                read_int(pos);
                Insert(root,pos);
                int pre=Predecessor(root,pos,start);
                int suc=Successor(root,pos,start);
                ans+=min(abs(pre-pos),abs(suc-pos));
            }
            printf("%d\n",ans);
        }
         
        void Rotato_Left(TreeNode *&now)
        {
            TreeNode *tmp=now->right;
            now->right=tmp->left;
            tmp->left=now;
            now=tmp;
            now->left->size=now->left->left->size+now->left->weight+now->left->right->size;
            now->size=now->left->size+now->right->size+now->weight;
        }
         
        void Rotato_Right(TreeNode *&now)
        {
            TreeNode *tmp=now->left;
            now->left=tmp->right;
            tmp->right=now;
            now=tmp;
            now->right->size=now->right->left->size+now->right->weight+now->right->left->size;
            now->size=now->left->size+now->weight+now->right->size;
        }
         
        void Insert(TreeNode *&now,int key)
        {
            if(now==null)
            {
                now=new TreeNode;
                now->fix=rand();
                now->key=key;
                now->left=null;
                now->right=null;
                now->size=1;
                now->weight=1;
                return ;
            }
            if(now->key==key)
            {
                now->weight++;
            }
            else if(now->key<key)
            {
                Insert(now->right,key);
                if(now->right->fix>now->fix) Rotato_Left(now);
            }
            else if(now->key>key)
            {
                Insert(now->left,key);
                if(now->left->fix>now->fix) Rotato_Right(now);
            }
            now->size=now->left->size+now->right->size+now->weight;
        }
         
        int Predecessor(TreeNode *&now,int key,TreeNode *&optimal)
        {
            if(now==null) return optimal->key;
            if(now->key==key)
            {
                if(now->weight>1) return key;
                else return Predecessor(now->left,key,optimal);
            }
            else
            {
                if(now->key<key) return Predecessor(now->right,key,now);
                else return Predecessor(now->left,key,optimal);
            }
        }
         
        int Successor(TreeNode *&now,int key,TreeNode *&optimal)
        {
            if(now==null) return optimal->key;
            if(now->key==key)
            {
                if(now->weight>1) return key;
                else return Successor(now->right,key,optimal);
            }
            else
            {
                if(now->key>key) return Successor(now->left,key,now);
                else return Successor(now->right,key,optimal);
            }
        }
};
class TreapType do_;
 
int main()
{
    return 0;
}
