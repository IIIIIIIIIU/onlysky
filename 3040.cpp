#include <stdio.h>  
    #include <string.h>  
    #include <algorithm>  
    #include <queue>  
    using namespace std;  
    #define ll long long  
        
    const int M=10000005;  
    const int N=1000005;  
    int node[M],nxt[M],head[N];  
    int n,m,tot;  
    int i,j;  
    ll d[N],data[M];  
    ll T,rxa,rxc,rya,ryc,rp;  
        
    void add(int x,int y,ll z){  
        node[++tot]=y;nxt[tot]=head[x];head[x]=tot;data[tot]=z;  
    }  
        
    void init(){  
        long long x,y,z,a,b,l;  
        x=y=z=0;  
        scanf("%lld%lld%lld%lld%lld%lld",&T,&rxa,&rxc,&rya,&ryc,&rp);  
        for (i=1;i<=T;i++){    
            x=(x*rxa+rxc)%rp;  
            y=(y*rya+ryc)%rp;  
            a=min(x%n+1,y%n+1);  
            b=max(y%n+1,y%n+1);  
            l=(ll)1e8-100*a;  
            add(a,b,l);  
        }  
            
        tot=0;  
        memset(head,0,sizeof head);  
        for (i=T+1;i<=m;i++){  
            scanf("%lld%lld%lld",&x,&y,&z);  
            add(x,y,z);  
        }  
    }  
        
    void Dij(){  
        memset(d,10,sizeof d);d[1]=0;  
        priority_queue<pair<long long,int> > heap;  
        heap.push(make_pair(-d[1],1));  
        for (;;){  
            for (;!heap.empty() && -d[heap.top().second]!=heap.top().first;heap.pop());  
            if (heap.empty()) break;  
                
            int now=heap.top().second;  
            heap.pop();  
                    
            for (i=head[now];i;i=nxt[i]){  
                j=node[i];  
                if (d[j]>d[now]+data[i]){  
                    d[j]=d[now]+data[i];  
                    heap.push(make_pair(-d[j],j));  
                }  
            }  
        }  
    }  
        
    int main(){  
        scanf("%d%d",&n,&m);  
        init();  
        Dij();  
        printf("%lld\n",d[n]);  
        return 0;  
    }  
