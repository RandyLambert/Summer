#ifndef __MY_SERTHREAD_H
#define __MY_SERTHREAD_H
#include "all.h"
#include <mysql/mysql.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include "my_recv.h"
#include <stdlib.h>
#include "list.h"

infouser_list_t head;
infouser_node_t * pos;
void myallthread(PACK *pack);
int threadlogin(PACK *pack);
void userregister(PACK *pack);
void mysqlinit(MYSQL *mysql);
void srv_deletefriend(PACK *pack);
void srv_addfriend(PACK *pack);
void srv_groupquit(PACK *pack);
void srv_groupdel(PACK *pack);
void srv_groupjoin(PACK *pack);
void srv_findpassword(PACK *pack);
void srv_frienchat(PACK *pack);
void srv_groupchat(PACK *pack);
void srv_creategroup(PACK *pack);
void srv_groupkick(PACK *pack);
void srv_groupsee(PACK *pack);
void srv_friendsee(PACK *pack);
void srv_changenum(PACK *pack);
int close_mysql(MYSQL mysql);
void judgeaddfri(PACK *pack);
void judgeaddgro(PACK *pack);
void srv_frimessbox(PACK *pack);
void srv_gromessbox(PACK *pack);
int Filetran(PACK *pack);
#endif
