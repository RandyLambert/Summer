#include <bits/stdc++.h>
using namespace std;
int a[1000000+10],b[10010];
int next1[10010];

int t,n,m;

void getnext(int *p){

    int plen = m,k = -1,j = 0;
    next1[0] = -1;
    
    while(j < plen){
        if(k == -1 || p[j] == p[k]){
            ++k;
            ++j;
            next1[j] = k;
        }
        else{
            k = next1[k];
        }
    }

    /* for(int i = 0;i <= plen;i++){ */
    /*     printf("%d ",next1[i]); */
    /* } */
    /* putchar('\n'); */
}


int kmp(int *a,int *b){
    
    int slen = n;
    int plen = m;

    int i = 0,j = 0;

    while(i < slen && j < plen){
        if(j == -1 || a[i] == b[j]){
            j++;
            i++;
        }
        else{
            j = next1[j];
        }
    }

    if(j == plen)
        return i - j;
    else
        return -1;
}

int main(){

    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i = 0;i < n;i++){
            scanf("%d",&a[i]);
        }
        for(int i = 0;i < m;i++){
            scanf("%d",&b[i]);
            next1[i] = 0;
        }
        getnext(b);
        int ans = kmp(a,b);
        if(ans!=-1)
            printf("%d\n",ans+1);
        else
            printf("%d\n",ans);
    }
    return 0;
}

