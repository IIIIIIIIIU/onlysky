#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        int n;
        scanf("%d",&n);
        int ans=0,pos;
        bool ok=true;
        while(n--)
        {
            scanf("%d",&pos),ans^=pos;
            if(pos!=1) ok=false;
        }
        if ((ok&&!ans)||(!ok&&ans)) printf("John\n");
        else printf("Brother\n");
    }
    return 0;
}
