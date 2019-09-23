
#include "my_recv.h"
//自定义错误处理函数
void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line:%d ", line);
    perror(err_string);
    exit(1);
}

int my_recvlogin(PACK *data2, login_data *data1, int len)
{
    strcpy(data1->password, data2->data.recv_name);
    strcpy(data1->username, data2->data.send_name);
    return 1;
}

int my_recvregister(PACK *data2, info_user *data1, int len)
{

    strcpy(data1->username, data2->data.send_name);
    strcpy(data1->password, data2->data.recv_name);
    strcpy(data1->mibao, data2->data.mes);
    if (data2->data.send_fd == 1)
    {
        strcpy(data1->sex, "n\0");
    }
    else if (data2->data.send_fd == 2)
    {
        strcpy(data1->sex, "w\0");
    }
    return 1;
    //读取成功
}