#include <stdio.h>
int main(){
    char *a = "addas";
    printf("%s\n",a);
    a[0] = 'b';
    printf("%s",a);
    return 0;
}

