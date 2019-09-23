#include<bits/stdc++.h>
using namespace std;
int a[1000+10];
int main(){
    int q;
    cin >> q;
    while(q--){
        memset(a,0,sizeof(a));
        int n;
        cin >> n;
        int sum = 1;
        for(int i = 1;i <= n;i++)
            cin >> a[i];
        if(n <= 2){
            cout<<"YES"<<"\n";
            continue;
        }
        for(int i = 1;i <= n-1;i++){
            if((abs(a[i]-a[i+1])) == 1){
                sum++;
            }
            else
                break;
        }
        if(sum < n){
            if((abs(a[1] - a[n])) == 1)
                sum++;
            if(sum < n){
                for(int i=n;i>=2;i--){
                    if((abs(a[i]-a[i-1]))==1)
                        sum++;
                    else
                        break;
                }
            }
        }
        if(sum==n)
            cout<<"YES"<<"\n";
        else
            cout<<"NO"<<"\n";
    }
    return 0;
}

