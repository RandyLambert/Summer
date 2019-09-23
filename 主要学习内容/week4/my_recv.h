#ifndef __MY_RECV_H
#define __MY_RECV_H
#include "all.h"
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include "my_recv.h"
#include <stdlib.h>
#include "all.h"
void my_err(const char * err_string,int line);
int my_recvlogin(PACK *data2,login_data *data1,int len);
int my_recvregister(PACK *data2,info_user *data1,int len);
#endif