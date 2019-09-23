#include <bits/stdc++.h>
using namespace std;
int main(){
    int k,a,b;
    cin>>k>>a>>b;
    if(a/k==0&&b/k==0){
        cout<<"-1"<<"\n";
    }
    else{
        if(a/k!=0&&b/k!=0)
            cout<<a/k+b/k<<"\n";
        else if(a/k==0&&b/k!=0){
            if(b%k==0)
                cout<<a/k+b/k<<"\n";
            else
                cout<<"-1"<<"\n";
        }
        else if(a/k!=0&&b/k==0){
            if(a%k==0)
                cout<<a/k+b/k<<"\n";
            else
                cout<<"-1"<<"\n";
        }
    }
    return 0;
}

