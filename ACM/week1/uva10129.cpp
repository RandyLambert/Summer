#include <bits/stdc++.h>
using namespace std;

int xx[30],n,m,chu[30],ru[30],f[30];

int findf(int x){
    if(x==f[x]){
        return x;
    }
    else{
        f[x] = findf(f[x]);
        return f[x];
    }
}
void init(){
    for(int i = 0;i < 30;i++){
        f[i] = i;
        chu[i] = 0;
        ru[i] = 0;
        xx[i] = 0;
    }
}
int main(){
    
    cin>>n;
    while(n--){
        cin>>m;
        init();
        int cnt = 0,ans = 0,flag = 0,tt = 0;
        for(int i = 0;i < m;i++){
            string temp;
            cin>>temp;
            int x1 = *temp.begin()-96;
            int x2 = *(temp.end()-1)-96;
            chu[x2]++;
            ru[x1]++;
            xx[x1] = 1;
            xx[x2] = 1;
            int f1 = findf(x1);
            int f2 = findf(x2);
            if(f1!=f2){
                f[f1] = f2;
            }
        }
        for(int i = 1;i < 27;i++){
            if(xx[i] == 1){
                if(f[i] == i){
                    cnt++;
                }
            }
        }
        if(cnt==1){
            for(int i = 1;i < 27;i++){
                if(ru[i]!=chu[i]){
                    if(ru[i]-chu[i]==1){
                        ans++;
                    }
                    else if(chu[i]-ru[i]==1){
                        flag++;
                    }
                    else{
                        tt = 1;
                    }
                }
            }
            if(tt == 1){
                cout<<"The door cannot be opened."<<endl;
                continue;
            }
            if((ans == 1 && flag == 1) || (ans ==0 && flag ==0)){
                cout<<"Ordering is possible."<<endl;
            }
            else{
                cout<<"The door cannot be opened."<<endl;

            }
        }
        else{
            cout<<"The door cannot be opened."<<endl;
        }
    }
    return 0;
}

