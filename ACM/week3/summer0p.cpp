#include <bits/stdc++.h>
using namespace std;
int main(){
    string a;
    cin>>a;
    char b = 'a';
    for(int i = 0;i < a.length();i++){
        if(a[i] == b)
            b++;
        if(a[i] > b){
            cout<<"NO"<<"\n";
            exit(0);
        }
    }
    cout<<"YES"<<"\n";

    return 0;
}

