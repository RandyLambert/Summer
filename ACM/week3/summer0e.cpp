#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,k,i = 0;
    cin>>n>>k;

    string a = "abcdefghijklmnopqrstuvwxyz";
    while(1){
        for(int j = 0;j < k;j++){
            cout<<a[j];
            i++;
            if(i == n)
                exit(0);
        }
    }

    return 0;
}

