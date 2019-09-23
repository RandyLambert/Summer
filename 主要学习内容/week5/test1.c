#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct login{
    char username[20];
    char password[20];
}login_data;
int main(){

    char data[1024] = "hhhhhhhhhhhh\nsadasdasa\n";
    static char *pread; //指向下一次读取数据的位置
    static int len_remain = 0;
    int i;

    login_data *data1 = NULL;
    data1 = (login_data *)malloc(sizeof(login_data));

    //如果自定义缓冲区没有数据，则从套接字中读取数据
    
    pread = data; //初始化pread指针

    //从自定义缓冲区中读取一次数据

    int wei = 0;
    for(int j = 0;j < 2;j++){
        for(i = 0;*pread != '\n';i++){
            if(j == 0){
                data1->username[i] = *pread++;
                len_remain--;
            }
            else if(j == 1){
                data1->password[i] = *pread++;
                len_remain--;
            }
        }
        *pread++;
    }

    //去除结束标志
    len_remain--;
    pread++;
    printf("%s\n%s",data1->password,data1->username);

    return 0;
}

