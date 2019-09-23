#include <bits/stdc++.h>
using namespace std;

struct node{
    map<string,int> shuiw;
};

map<string,node> q;

int main(){

    string di,guo;
    int n,m,jia;
    cin>>n;
    while(n--){
        q.clear();
        cin>>m;
        while(m--){
            cin>>guo>>di>>jia;
            if(q.count(di) == 0){
                node nod;
                nod.shuiw[guo] = jia;
                q[di] = nod;
            }
            else{
                if(q[di].shuiw.count(guo) == 0){
                    q[di].shuiw[guo] = jia;
                }
                else{
                    q[di].shuiw[guo] = jia + q[di].shuiw[guo];
                }
            }
        }
        for(auto it = q.begin();it!=q.end();it++){
            cout<<it->first<<"\n";
            for(auto itt = it->second.shuiw.begin();itt != it->second.shuiw.end();itt++){
                cout<<"   |----"<<itt->first<<"("<<itt->second<<")"<<"\n";
            }
        }
        if(n > 0){
            putchar('\n');
        }
    }
    return 0;
}

