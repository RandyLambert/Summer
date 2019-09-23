#include <bits/stdc++.h>
using namespace std;
int a[2000000+10];
int main(){
    int n,len;
    cin>>n;
    len = n-1;
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }

    for(int i = 0;i < n/2;i++){
        if(i%2 == 0)
            swap(a[i],a[len]);
        len--;
    }


    for(int i = 0;i < n;i++){
        cout<<a[i]<<" ";
    }
    

    return 0;
}

