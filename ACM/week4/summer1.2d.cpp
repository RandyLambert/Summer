#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e6+10;
char str1[MAXN],str2[MAXN];
int next1[MAXN];
int len;

void getnext()
{
    len=strlen(str1);
    int j=0;
    int k= -1;
    next1[0]=-1;
    while(j<len){
        if(k==-1||str1[j]==str1[k]){
            j++;
            k++;
            next1[j]=k;
        }
        else
            k=next1[k];
    }
}

int main(){
    
    int t;
    int xx = 1;
    while(cin>>t&&t){
        scanf("%s",str1);
        printf("Test case #%d\n",xx++);
        
        getnext();

        for(int i = 1;i < len;i++){
            int k = i+1;
            if(k%(k - next1[k]) == 0 && k/(k-next1[k])!=1){
                printf("%d %d\n",k,k/(k-next1[k]));
            }
        }
        putchar('\n');
    }
    return 0;
}
