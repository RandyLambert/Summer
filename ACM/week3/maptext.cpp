#include <bits/stdc++.h>
using namespace std;
int main(){
    
    string a = "dasdasdsadsah";
    vector<char>h;
    queue<char>q;
    stack<char>p;

    p.push('d');
    p.push('c');


    q.push('q');
    q.push('k');
    q.push('l');
    q.push('o');
    
    h.push_back('d');
    h.push_back('h');
    h.push_back('w');

    cout<<(a.back())<<endl;
    cout<<(h.back())<<endl;
    cout<<(q.back())<<endl;
    /* auto p = q.find("da"); */
    /* cout<<p->second<<"\n"; */

    

    return 0;
}

