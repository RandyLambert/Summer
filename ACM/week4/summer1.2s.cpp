#include <bits/stdc++.h>
using namespace std;
char a[1005],b[1005];
int next1[1005],ans;
void getnext(){
    
    int blen = strlen(b),i = -1,j = 0;
    next1[0] = -1;
    while(blen > j){
        if(i == -1 || next1[i] == next1[j]){
            i++;
            j++;
            next1[j] = i;
        }
        else{
            i = next1[i];
        }
    }
}

void kmp(){

    getnext();
    int i = 0,j = 0;
    int alen = strlen(a);
    int blen = strlen(b);

    while(i < alen){
        if(j == -1 || a[i] == b[j]){
            i++;
            j++;
            if(j == blen){
                j = 0;
                ans++;
            }
        }
        else{
            j = next1[j];
        }

    }
}

int main(){

    while(1){
        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        memset(next1,0,sizeof(next1));
        cin>>a;
        if(a[0] == '#')
            break;
        cin>>b;
        ans = 0;

        kmp();
        cout<<ans<<"\n";
    }
    return 0;
}

