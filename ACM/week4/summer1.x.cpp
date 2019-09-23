#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int a[20000005],b[20000005];
int main(){

    int t,n,m,casei = 1;

    cin>>t;
    while(t--){
        cin>>n>>m;
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        
        a[0] = b[0] = 0;

        int i = 0,j = 0;
        while(n > a[i]){
            i++;

            a[i] = b[i-1] + 1;
            while(a[j+1] * m < a[i])
                j++;

            if(m * a[j] < a[i])
                b[i] = b[j] + a[i];
            else
                b[i] = a[i];
        }
        printf("Case %d: ",casei++);
        
        if(n == a[i])
            printf("lose\n");
        else{
            int ans;
            while(n){
                if(n >= a[i]){		
                    n -= a[i];
                    ans = a[i];
                }
                i--;
            }
            printf("%d\n",ans);
        }

        putchar('\n');
        for(int i = 0;i < 20;i++)
            printf("a[i] = %d b[i] = %d \n",a[i],b[i]);

        

    }

    return 0;
}

