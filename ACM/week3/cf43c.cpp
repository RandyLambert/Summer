#include <bits/stdc++.h>
using namespace std;
int a[10100],vis[10100];
int main(){

    int n;
    string x;
    cin>>n;
    for(int k = 0;k < n;k++){
        int ans = 0;
        cin>>x;
        for(int i = 0;i < x.length();i++){
            ans = (x[i]-'0') + ans;
        }
        a[k] = ans;
    }
    /* for(int k = 0;k < n;k++) */
    /*     printf("a[%d] = %d\n",k,a[k]); */
    int cnt = 0;
    for(int i = 0;i < n-1;i++){
        for(int j = i+1;j < n;j++){
            if(((a[i] + a[j])%3 == 0) && vis[i] == 0 && vis[j] == 0){
                cnt++;
                vis[i] = 1;
                vis[j] = 1;
            }
        }
    }

    printf("%d\n",cnt);
    return 0;
}

