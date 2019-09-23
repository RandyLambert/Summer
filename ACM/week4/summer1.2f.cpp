#include <bits/stdc++.h>
using namespace std;
int main(){
    string b;
    while(getline(cin,b) && b!="#"){
        istringstream sin(b);
        set<string> q;
        string w;
        while(sin >> w){
            q.insert(w);
        }
        cout<<q.size()<<"\n";
    }
    return 0;
}

