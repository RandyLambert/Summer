#include <bits/stdc++.h>
using namespace std;
int main(){

    string a;
    map<string,int>q;
    while(getline(cin,a)){
        if(a.size() == 0){
            break;
        }
        int x = a.size();
        for(int i = 0;i < x;i++){
            cout<<a<<"\n";
            q[a]++;
            a.erase(--a.end());
        }
    }

    while(cin>>a){

        if(q.count(a) == 1){
            cout<<q[a]<<"\n";
        }
        else{
            cout<<0<<"\n";
        }
    }
    return 0;
}
