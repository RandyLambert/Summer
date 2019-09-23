#include <bits/stdc++.h>
using namespace std;
char xx[200000+10];
int t,n,k;
int judge(int mid){
    int i = 0,ans = 0;
    while(i < n){
        if(xx[i] == '0'){
            i++;
        }
        else if(xx[i] == '1'){
            i+=mid;
            ans = ans+1;
        }

        if(ans > k){
            return 0;
        }
    }

    if(ans > k){
        return 0;
    }
    else{
        return 1;
    }
}
int main(){
    scanf("%d",&t);
    while(t--){
        memset(xx,0,sizeof(xx));
        scanf("%d%d",&n,&k);
        scanf("%s",xx);
        
        int l = 0,r = n,ans = 0;

        while(l<=r){
            int mid = (l+r)>>1;
            if(judge(mid)){
                r = mid - 1;
                ans = mid;
            }
            else{
                l = mid + 1; 
            }
        }
        printf("%d\n",ans);
    }

    return 0;
}

