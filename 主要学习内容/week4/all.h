#ifndef __MY_CLIENT_H
#define __MY_CLIENT_H

#define MAX_CHAR                 1024
#define LOGIN                    1
#define REGISTER                 2
#define FRI_CHA                  3
#define FRI_ADD                  4
#define FRI_DEL                  5
#define GROUP_SEE                6  
#define GROUP_CREATE             7
#define GROUP_JOIN               8
#define GROUP_QIUT               9
#define GROUP_DEL                10
#define CHAT_ONE                 11
#define CHAT_MANY                12
#define FIND_PASSWD              13
#define FILE_SEND_BEGIN_RP       14
#define FILE_SEND                17
#define GROSEEEND                18 
#define FILE_RECV                21
#define FRISEEEND                22
#define MES_RECORD               23
#define GROUP_KICK               24
#define GROUP_SET                25
#define FRI_SEE                  26
#define CHANGE_NUM               27
#define FRI_MES                  28
#define GRO_MES                  29
#define FRIQUE                   30
#define GROQUE                   31


#define EXIT                     -1
#define USER_MAX                 100
#define GROUP_MAX                100

#define USER_NAMEMAX             100
#define GROUP_NAMEMAX            100

#define BUFSIZE                  1024
#define PAGE_SIZE                10
#define LEN_PACK                 1236

typedef struct datas{
    char     send_name[USER_NAMEMAX];
    char     recv_name[USER_NAMEMAX];
    int      send_fd;
    int      recv_fd;
    //time_t   time;
    char     mes[MAX_CHAR];
}DATA;
 
typedef struct package{
    int   type;
    DATA  data;
}PACK;

typedef struct box{
    char     send_name[USER_NAMEMAX];
    char     recv_name[USER_NAMEMAX];
    int      send_fd;
    int      recv_fd;
    //time_t   time;
    char     mes[MAX_CHAR];
    int      type;
}BOX;

typedef struct box_message{
    BOX  data;
    struct box_message *next;
	struct box_message *prev;
}box_node_t,*box_list_t;


typedef struct info_group{
    char  group_name[MAX_CHAR];
    int   member_num;
    char  member_name[USER_MAX][MAX_CHAR];  //begin from 1
}info_group;
 
typedef struct infogroup_node{
    info_group data;
	struct infogroup_node *next;
	struct infogroup_node *prev;
}infogroup_node_t,*infogroup_list_t;


typedef struct info_user 
{
    char username[MAX_CHAR];
    int uid;
    char password[20];
    int  statu;//don't foget to change is to 0 when the server begin
    int  socket_id;
    char sex[3];
    char mibao[100];
}info_user;


typedef struct infouser_node
{
    info_user data;
	struct infouser_node *next;
	struct infouser_node *prev;
}infouser_node_t,* infouser_list_t;


typedef struct login{
    char username[20];
    char password[20];
}login_data;


#endif