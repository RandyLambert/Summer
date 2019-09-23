#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    while(scanf("%d",&n)&&n!=0){
        int a[105],b[105],c[105],ans = 0;
        for(int i = 0;i < n;i++){
            scanf("%d%d%d",&a[i],&b[i],&c[i]);
        }
        int cnt = 0;
        for(int i = 1000;i <= 9999;i++){
            int flag = 1;
            for(int j = 0;j < n;j++){
                int a1 = 0,b1 = 0,yyy = 1,vis1[10],vis2[10];

                memset(vis1,0,sizeof(vis1));
                memset(vis2,0,sizeof(vis2));

                for(int k = 0;k < 4;k++){
                    int xxx = i/yyy%10;
                    int zzz = a[j]/yyy%10;
                    if(xxx == zzz){
                        b1++;
                    }
                    vis1[xxx]++;
                    vis2[zzz]++;
                    yyy = yyy*10;
                }

                for(int h = 0;h < 10;h++){
                    if(vis1[h]!=0 && vis2[h]!=0){
                        a1 = a1 + min(vis1[h],vis2[h]);
                    }
                }

                if(a1 != b[j] || b1 != c[j]){
                    flag = 0;
                    break;
                }
            }
            if(flag == 1){
                cnt++;
                ans = i;
                if(cnt>1){
                    break;
                }
            }
        }

        if(cnt > 1 || cnt == 0){
            printf("Not sure\n");
        }
        else{
            printf("%d\n",ans);
        }
    }
    return 0;
}

