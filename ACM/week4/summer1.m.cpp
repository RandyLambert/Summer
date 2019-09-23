#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,x,a[110];
    while(scanf("%d",&n)&&n){
        int ans = 0;
        for(int i = 0;i < n;i++){
            scanf("%d",&a[i]);
            ans^=a[i];
        }
        if(ans == 0)
            printf("0\n");
        else{
            int cnt = 0;
            for(int i=0;i<n;i++)
                if((a[i]^ans)<=a[i])
                    cnt++;
            printf("%d\n",cnt);
        } 
    }
    return 0;
}
