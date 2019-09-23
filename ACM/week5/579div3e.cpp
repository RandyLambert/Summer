#include <bits/stdc++.h>
using namespace std;
int a[150000+10];
int mp[150000+10];
int main(){
 
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n;i++){
        scanf("%d",&a[i]);
        mp[a[i]]++;
    }
 
    sort(a,a+n);
    
    int ans = 0;
    for(int i = 1;i < 150010;i++){
        if(mp[i] == 1){
            if(mp[i-1] == 0 && i-1 != 0){
                mp[i-1] = 1;
                mp[i]--;
            }
        }
        else if(mp[i] == 2){
            if(mp[i-1] == 0 && i-1 != 0){
                    mp[i-1] = 1;
                    mp[i]--;
            }
            mp[i]--;
            mp[i+1]++;
        }
        else if(mp[i] >= 3){
            if(mp[i-1] == 0 && i-1!=0){
                    mp[i]--;
                    mp[i-1] = 1;
            }
            mp[i]--;
            mp[i+1]++;
        }
    }
    for(int i = 0;i < 150010;i++)
        if(mp[i]!=0)
            ans++;
    printf("%d\n",ans);
    return 0;
}
