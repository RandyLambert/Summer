#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    string a;
    cin>>n;
    while(n--){
        cin>>a;
        if(a.length()<=10){
            cout<<a<<endl;
        }
        else{
            cout<<(*a.begin())<<a.length()-2<<(*(a.end()-1))<<endl;
        }
    }
    return 0;
}

