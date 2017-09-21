#include<bits/stdc++.h>  
using namespace std;  
int main()  
{  
    int n,q=1;  
    scanf("%d",&n);  
    for(int i=1;;i++)  
    {  
        q*=2;  
        if(q>n)  
        {     
            cout<<i;  
            return 0;  
        }     
    }  
    return 0;  
}
