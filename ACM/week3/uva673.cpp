#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    getchar();
    while(n--){

        int flag = 0;
        stack <char> q;
        string a;
        getline(cin,a);
        while(!q.empty()) q.pop();

        while(flag == 0){
            for(int i = 0;i < a.size();i++){
                if(a[i] == '(' || a[i] == '['){
                    q.push(a[i]);
                }
                if(a[i] == ')'){
                    if(q.size() && q.top() == '('){
                        q.pop();
                    }
                    else{
                        flag = 1;
                    }
                }
                if(a[i] == ']'){
                    if(q.size() && q.top() == '['){
                        q.pop();
                    }
                    else{
                        flag = 1;
                    }
                }
            }
            break;
        }

        if(flag == 0 && q.size() == 0){
            cout<<"Yes"<<"\n";
        }
        else{
            cout<<"No"<<"\n";
        }
    }
    return 0;
}

