#include <bits/stdc++.h>
using namespace std;
int main(){

    set<string> q;
    string s,buf;
    while(cin >> s){
        for(int i = 0;i < s.length();i++)
            if(isalpha(s[i]))
                s[i] = tolower(s[i]);
            else
                s[i] = ' ';
        stringstream ss(s);
        while(ss >> buf){
            q.insert(s);
        }
    }
    for(auto it = q.begin(); it != q.end(); it++)
        cout<<*it<<endl;
    return 0;
}

