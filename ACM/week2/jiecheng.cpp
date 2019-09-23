#include <bits/stdc++.h>
using namespace std;
const int maxn=60100;
int f[maxn]; 
int main(){
    int n;
    while(scanf("%d",&n)!=EOF){
		
    	memset(f,0,sizeof(f));   
    	
        f[0]=1;         
        int c;
    	for(int i=2;i<=n;i++){
            /* int tt = (10000-i)*(10000-i-1); */
    	    for(int j=0;j<maxn;j++){
                
    	        int s=f[j]*i+c;  
    	        f[j]=s%10;         
    	        c=s/10;         
    	    }
    	}

        int ans;
    	for(int j=maxn-1;j>=0;j--)
            if(f[j]){
                ans = j;
    		    break;
            }

		for(int i=ans;i>=0;i--)
    	printf("%d",f[i]);
    	printf("\n");
	}
return 0;
}

