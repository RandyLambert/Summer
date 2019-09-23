#include <bits/stdc++.h>
using namespace std;
char w[10000+10],t[1000000+10];
int next1[10000+10],ans;
void getnext(){
    int wlen = strlen(w);

    int j = 0,k = -1;
    next1[0] = -1;
    
    while(j < wlen){
        if(k == -1 || w[k] == w[j]){
            ++k;
            ++j;
            next1[j] = k;
        }
        else{
            k = next1[k];
        }
    }

    /* for(int i = 0;i <= wlen;i++){ */
    /*     printf("%d ",next1[i]); */
    /* } */
}

void kmp(){
    int wlen = strlen(w);
    int tlen = strlen(t);
    getnext();

    int i = 0,j = 0;
    while(j < tlen){
        if(i == -1 || w[i] == t[j]){
            i++;
            j++;

            if(i == wlen){
                ans++;
                i = next1[i];
            }
        }
        else{
            i = next1[i];
        }
    }
}
int main(){
    
    int xx;
    scanf("%d\n",&xx);
    while(xx--){
        memset(w,0,sizeof(w));
        memset(t,0,sizeof(t));
        scanf("%s",w);
        scanf("%s",t);
        
        ans = 0;
        kmp();
        printf("%d\n",ans);
        
    }
    return 0;
}

