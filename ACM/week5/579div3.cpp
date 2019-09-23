#include <bits/stdc++.h>
using namespace std;
int a[1000],b[1000];
int main(){

    int t,n;
    cin>>t;
    while(t--){
        memset(a,0,sizeof(a));
        int cnt;
        cin>>n;
        for(int i = 1;i <= n;i++){
            cin>>a[i];
            /* b[i] = a[i]; */
            if(a[i] == 1){
                cnt = i;
            }
        }
        int x = 0;
        int flag = 0;

        if(cnt - 1 == 0){
            if(a[n] == 2){
                flag = 0;
            }
            else if(a[2] == 2){
                flag = 1;
            }
            else{
                flag = 2;
            }
        }
        else if(cnt == n){
            if(a[1] == 1){
                flag = 1;
            }
            else if(a[n - 1]){

            }
        }
        else if(a[cnt-1] == 2){
            flag = 0;
        }
        else if(a[cnt+1] == 2){
            flag = 1;
        }

        while(x < n){
            if(cnt == 1){
                cnt = n;
            }
            else if(cnt == n){
                cnt = 1;
            }
            else{
                cnt--;
            }
        }
    }

    return 0;
}

