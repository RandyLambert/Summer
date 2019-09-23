#include <bits/stdc++.h>
using namespace std;
int main(){
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;

        int ans = 0,xx,flag = 0;
        for(int i = 0;i < n;i++){
            cin>>xx;
            if(xx!=1)
                flag = 1;
            ans = ans^xx;
        }

        if(flag == 1){
            if(ans == 0)
                printf("Brother\n");
            else
                printf("John\n");
        }
        else if(flag == 0)
            if(n%2 == 0)
                printf("John\n");
            else
                printf("Brother\n");

    }
    return 0;
}

