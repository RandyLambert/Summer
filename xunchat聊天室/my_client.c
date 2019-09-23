#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "my_recv.h"
#include "all.h"
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include "list.h"
#include "md5.h"
#include <fcntl.h>
#include <sys/stat.h>

#define INVALID_USERINFO 'n' //用户信息无效
#define VALID_USERINFO 'y'   //用户信息有效

int friendnum = 0;
int groupnum = 0;
int messnum = 0;
int useruid;
int chatfd = -1;
int grochatfd = -1;
int grosee = -1;
int firsee = -1;

pthread_mutex_t mutex;
pthread_mutex_t mutex2;
pthread_cond_t cond;
pthread_cond_t cond2;

void judgeaddfri(int mes, int conn_fd);
void judgeaddgro(int mes, int conn_fd);
void watchfrilist(int conn_fd);   //查看好友列表
void watchgrouplist(int conn_fd); //查看群组列表
int login(int conn_fd);
int UI_zhuce(int conn_fd);
void UI_loginin(int conn_fd);
void UI_user(int conn_fd);
int UI_friendadd(int conn_fd);
int UI_frienddel(int delfd, int conn_fd);
int UI_friendchat(int chatfd, int conn_fd);
int UI_groupchat(int grochatfd, int conn_fd);
int UI_groupadd(int conn_fd, int groupid);
int UI_groupmbkick(int groupid, int conn_fd);
int UI_groupout(int groupid, int conn_fd);
int UI_groupdel(int groupid, int conn_fd);
int UI_groupcreate(int conn_fd);
int UI_frimessbox(int chatfd, int conn_fd);
int UI_gromessbox(int grochatfd, int conn_fd);
int UI_filesend(int conn_fd);
void printtype(int type);

void input_userinfo(int conn_fd, const PACK *senddata);

void *clientrecive(void *conn_fd);
void changepassword(int conn_fd);
void findpassword(int conn_fd);

void watchlistbox(int conn_fd);

char username[20], password[20];
box_list_t head;
box_list_t headgroup;
box_list_t headuser;

int main(int argc, char **argv)
{
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex2, NULL);
	pthread_cond_init(&cond, NULL);
	pthread_cond_init(&cond2, NULL);

	List_Init(head, box_node_t);
	List_Init(headgroup, box_node_t);
	List_Init(headuser, box_node_t);

	int i;
	int ret;
	int conn_fd;
	int serv_port;
	struct sockaddr_in serv_addr;
	char recv_buf[BUFSIZE];
	memset(recv_buf, 0, sizeof(recv_buf));
	//检查参数个数
	if (argc != 5)
	{
		printf("Usage:[-p] [serv_port] [-a] [serv_address]\n");
		exit(1);
	}
	//初始化服务器端地址结构
	memset(&serv_addr, 0, sizeof(struct sockaddr));
	serv_addr.sin_family = AF_INET;
	//从命令行获取服务器的端口与地址
	for (i = 1; i < argc; i++)
	{
		if (strcmp("-p", argv[i]) == 0)
		{
			serv_port = atoi(argv[i + 1]);
			if (serv_port < 0 || serv_port > 65535)
			{
				printf("invalid serv_addr.sin_port\n");
				exit(1);
			}
			else
			{
				serv_addr.sin_port = htons(serv_port);
			}

			continue;
		}

		if (strcmp("-a", argv[i]) == 0)
		{
			if (inet_aton(argv[i + 1], &serv_addr.sin_addr) == 0)
			{
				printf("invalid server ip address\n");
				exit(1);
			}

			continue;
		}
	}

	//检查是否少了某项参数
	if (serv_addr.sin_port == 0 || serv_addr.sin_addr.s_addr == 0)
	{
		printf("Usage : [-p] [serv_addr,sin_port] [-a] [serv_address] \n");
		exit(1);
	}
	//创建一个TCP套接字
	conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (conn_fd < 0)
	{
		my_err("clinet socket", __LINE__);
	}

	//向服务器端发送连接请求
	if (connect(conn_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) < 0)
	{
		my_err("client connect", __LINE__);
	}

	UI_loginin(conn_fd);
	pthread_t tid1;
	pthread_create(&tid1, NULL, (void *)clientrecive, &conn_fd);
	UI_user(conn_fd);
}

//然后用过fd 发送出去
void input_userinfo(int conn_fd, const PACK *senddata)
{

	
	if (send(conn_fd, senddata, sizeof(PACK), 0) < 0)
		my_err("send", __LINE__);
}

void *clientrecive(void *conn_fd)
{

	while (1)
	{
		

		PACK *recvdata = NULL;
		recvdata = (PACK *)malloc(sizeof(PACK));

		int len_pack = LEN_PACK;
		char *p = (char *)(recvdata);
		while (len_pack > 0)
		{
			size_t n;
			if ((n = recv(*(int *)conn_fd, p, len_pack, 0)) < 0)
			{
				if (errno != EAGAIN)
				{
					perror("recv");
					exit(1);
				}
			}
			//printf("recv %zd bytes\n", n);
			len_pack -= n;
			p += n;
		}

		if (recvdata->type == FRI_SEE)
		{
			box_node_t *newmessage = NULL;
			newmessage = (box_list_t)malloc(sizeof(box_node_t));
			newmessage->data.type = recvdata->type;
			strcpy(newmessage->data.mes, recvdata->data.mes);
			strcpy(newmessage->data.recv_name, recvdata->data.recv_name);
			strcpy(newmessage->data.send_name, recvdata->data.send_name);
			newmessage->data.recv_fd = recvdata->data.recv_fd;
			newmessage->data.send_fd = recvdata->data.send_fd;
			List_AddHead(headuser, newmessage);
			friendnum++;
			
		}

		if (recvdata->type == GROUP_SEE)
		{
			box_node_t *newmessage = NULL;
			newmessage = (box_list_t)malloc(sizeof(box_node_t));
			grosee = -1;
			newmessage->data.type = recvdata->type;
			strcpy(newmessage->data.mes, recvdata->data.mes);
			strcpy(newmessage->data.recv_name, recvdata->data.recv_name);
			strcpy(newmessage->data.send_name, recvdata->data.send_name);
			newmessage->data.recv_fd = recvdata->data.recv_fd;
			newmessage->data.send_fd = recvdata->data.send_fd;
			List_AddHead(headgroup, newmessage);
			
		}

		if (recvdata->type == GROSEEEND)
		{

			pthread_mutex_lock(&mutex);
			grosee = 1;
			pthread_mutex_unlock(&mutex);
			groupnum = recvdata->data.send_fd;
			pthread_cond_signal(&cond);

		}

		if (recvdata->type == FRISEEEND)
		{

			pthread_mutex_lock(&mutex2);
			firsee = 1;
			pthread_mutex_unlock(&mutex2);
			friendnum = recvdata->data.send_fd;
			pthread_cond_signal(&cond2);

		}

		if (recvdata->type == GRO_MES)
		{

			if (atoi(recvdata->data.recv_name) == grochatfd)
			{

				
				printf("[%d]>>%s\n", recvdata->data.send_fd, recvdata->data.mes);
				printf("you[|]quit>>\n");
			}
			else
			{
				box_node_t *newmessage = NULL;
				newmessage = (box_list_t)malloc(sizeof(box_node_t));
				printf("---------------你有群聊消息来了，在消息盒子！！-----------------\n");
				newmessage->data.type = recvdata->type;
				strcpy(newmessage->data.mes, recvdata->data.mes);
				strcpy(newmessage->data.recv_name, recvdata->data.recv_name);
				strcpy(newmessage->data.send_name, recvdata->data.send_name);
				newmessage->data.recv_fd = 0;
				newmessage->data.send_fd = recvdata->data.send_fd;
				List_AddHead(head, newmessage);
				messnum++;
				
			}
		}

		if (recvdata->type == FRI_MES)
		{

			if (recvdata->data.send_fd == chatfd)
			{
				printf("[%d]>>%s\n", recvdata->data.send_fd, recvdata->data.mes);
				printf("you[|]quit>>\n");
			}
			else
			{
				box_node_t *newmessage = NULL;
				newmessage = (box_list_t)malloc(sizeof(box_node_t));
				printf("---------------你有朋友消息来了，在消息盒子！！-----------------\n");
				newmessage->data.type = recvdata->type;
				strcpy(newmessage->data.mes, recvdata->data.mes);
				strcpy(newmessage->data.recv_name, recvdata->data.recv_name);
				strcpy(newmessage->data.send_name, recvdata->data.send_name);
				newmessage->data.recv_fd = -1;
				newmessage->data.send_fd = recvdata->data.send_fd;
				List_AddHead(head, newmessage);
				messnum++;
				
			}
		}

		if (recvdata->type == CHAT_ONE)
		{
			printf("用户号[%d]|用户号[%d]内容：%s\n", recvdata->data.send_fd, recvdata->data.recv_fd, recvdata->data.mes);
		}

		if (recvdata->type == CHAT_MANY)
		{
			printf("群号[%d]|用户号[%d]|内容：%s\n", recvdata->data.send_fd, recvdata->data.recv_fd, recvdata->data.mes);
		}

		if (recvdata->type == FRIQUE || recvdata->type == GROQUE)
		{

			box_node_t *newmessage = NULL;
			newmessage = (box_list_t)malloc(sizeof(box_node_t));
			printf("---------------你有请求消息来了，在消息盒子！！-----------------\n");

			newmessage->data.type = recvdata->type;
			strcpy(newmessage->data.mes, recvdata->data.mes);
			strcpy(newmessage->data.recv_name, recvdata->data.recv_name);
			strcpy(newmessage->data.send_name, recvdata->data.send_name);
			newmessage->data.recv_fd = recvdata->data.recv_fd;
			newmessage->data.send_fd = recvdata->data.send_fd;
			List_AddHead(head, newmessage);
			messnum++;
			
		}

		if (recvdata->type == FRI_DEL)
		{
			if (recvdata->data.mes[0] == 'y')
			{
				printf("删除好友成功\n");
			}
		}

		if (recvdata->type == GROUP_DEL)
		{
			if (recvdata->data.mes[0] == 'y')
			{
				printf("解散群聊成功\n");
			}
		}

		if (recvdata->type == GROUP_CREATE)
		{
			if (recvdata->data.mes[0] == 'y')
			{
				printf("创建群聊成功,请刷新群列表\n");
			}
		}
		static unsigned long long su = 0, i = 0;

		if (recvdata->type == FILE_SEND_BEGIN_RP)
		{
			/*if(i == 0){
				i++;
				printf("\n---------------你有文件来了，在消息盒子！！-----------------\n");
			}*/
			int sendfd;
			printf("%s", recvdata->data.send_name);
			sendfd = open(recvdata->data.send_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
			if (sendfd < 0)
				my_err(recvdata->data.send_name, __LINE__);

			int sum = 0;
			sum = write(sendfd, recvdata->data.mes, sizeof(recvdata->data.mes));
			su += sum;
			close(sendfd);
			printf("写入接收到的字节数：%lld", su);
			
		}
		free(recvdata);
	}
}

void watchfrilist(int conn_fd)
{
	system("clear");
	List_Free(headuser, box_node_t);
	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = FRI_SEE;
	senddata->data.send_fd = useruid;
	if (send(conn_fd, senddata, sizeof(PACK), 0) < 0)
		my_err("send", __LINE__);
	printf("-----------------------加载中-----------------------\n");

	while (firsee != 1)
	{
		pthread_cond_wait(&cond2, &mutex2);
	}

	int i, id;
	int choice;
	int deluid;
	int delfri = 0;
	char friendname[20];
	memset(friendname, 0, sizeof(friendname));

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = PAGE_SIZE;

	box_node_t *pos;
	box_node_t *pos1;
	paging.totalRecords = friendnum;
	Paging_Locate_FirstPage(headuser, paging);
	do
	{
		printf(
			"\n==========================================\n");
		printf(
			"***************** 好友信息表 *****************\n");

		printf("%-4s|%-24s|%-13s|%-8s\n", "uid", "好友姓名", "n(男)w(女)", "在线状态");
		printf("-----------------------------------------------\n");

		Paging_ViewPage_ForEach(headuser, paging, box_node_t, pos, i)
		{
			printf("%-4d|%-20s|%-11s|%-4d\n", pos->data.recv_fd, pos->data.send_name, pos->data.mes, pos->data.send_fd);
		}

		printf("--------Total Recoeds: %2d--Page %2d  %2d--------\n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));

		printf("*************************************************\n");

		printf("[1]上页|[2]下页|[3]添加用户|[4]删除用户|[5]获取更新|[6]选择私聊|[7]消息记录|[8]返回");
		printf("\n==============================================================\n");
		printf("your choice: ");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case 3:
			if (UI_friendadd(conn_fd))
			{
				paging.totalRecords = friendnum;
				Paging_Locate_LastPage(headuser, paging, box_node_t);
			}
			break;
		case 4:
			delfri = 0;
			printf("[不要输入不是你好友的uid] 请输入你要删除好友的uid：");
			scanf("%d", &deluid);
			getchar();
			system("clear");
			List_ForEach(headuser, pos1)
			{
				if (pos1->data.recv_fd == deluid)
				{
					delfri = 1;
					if (UI_frienddel(deluid, conn_fd))
					{
						List_DelNode(pos1);
						paging.totalRecords = friendnum - 1;
						List_Paging(headuser, paging, box_node_t);
					}
					break;
				}
			}
			if (delfri == 0)
			{
				printf("他不是你的好友，你也可以选择刷新重试\n");
			}
			break;
		case 5:
			List_Free(headuser, box_node_t);
			senddata = (PACK *)malloc(sizeof(PACK));
			senddata->type = FRI_SEE;
			firsee = -1;
			senddata->data.send_fd = useruid;
			if (LEN_PACK == send(conn_fd, senddata, sizeof(PACK), 0))
			{

				printf("-----------------------加载中-----------------------\n");
				while (firsee != 1)
				{
					pthread_cond_wait(&cond2, &mutex2);
				}
				system("clear");
				paging.totalRecords = friendnum;
				List_Paging(headuser, paging, box_node_t);
			}
			break;
		case 6:

			printf("[不要输入不是你好友的uid] 请输入你想要私聊的用户uid：");
			scanf("%d", &chatfd);
			getchar();
			system("clear");
			List_ForEach(headuser, pos1)
			{
				if (pos1->data.recv_fd == chatfd)
				{
					if (UI_friendchat(chatfd, conn_fd))
					{
						paging.totalRecords = friendnum;
						List_Paging(headuser, paging, box_node_t);
						chatfd = 0;
					}
					break;
				}
			}
			break;

		case 7:

			printf("[不要输入不是你好友的uid] 请输入你想要查看用户uid：");
			scanf("%d", &chatfd);
			getchar();
			List_ForEach(headuser, pos1)
			{
				if (pos1->data.recv_fd == chatfd)
				{
					if (UI_frimessbox(chatfd, conn_fd))
					{
						paging.totalRecords = friendnum;
						List_Paging(headuser, paging, box_node_t);
					}
					break;
				}
			}
			break;

		case 1:
			system("clear");

			if (!Pageing_IsFirstPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, -1, box_node_t);
			}
			break;
		case 2:
			system("clear");

			if (!Pageing_IsLastPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, 1, box_node_t);
			}
			break;
		}
	} while (choice != 8);
	firsee = -1;
	free(senddata);
}

void watchgrouplist(int conn_fd)
{
	system("clear");
	List_Free(headgroup, box_node_t);
	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = GROUP_SEE;
	senddata->data.send_fd = useruid;
	if (send(conn_fd, senddata, sizeof(PACK), 0) < 0)
		my_err("send", __LINE__);
	printf("-----------------------------加载中---------------------------\n");

	while (grosee != 1)
	{
		pthread_cond_wait(&cond, &mutex);
	}
	int i, id;
	int choice;
	int groupid;

	box_node_t *pos1;
	box_node_t *pos;

	Pagination_t paging;

	paging.offset = 0;
	paging.pageSize = PAGE_SIZE;
	char groupname[10];

	paging.totalRecords = groupnum;
	//返回有多少数量
	Paging_Locate_FirstPage(headgroup, paging);
	do
	{
		printf(
			"\n=============================================\n");
		printf(
			"******************** 群信息 ********************\n");

		printf("%-6s|%-22s|%-7s|%-7s\n", "群id", "群名", "群权限", "群主id");
		printf("---------------------------------------------------\n");

		Paging_ViewPage_ForEach(headgroup, paging, box_node_t, pos, i)
		{
			printf("%-5d|%-20s|%-5d|%-5s\n", pos->data.recv_fd, pos->data.mes, pos->data.send_fd, pos->data.recv_name);
		}

		printf("---Total Recoeds: %2d----Page %2d   %2d ---\n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));

		printf("*************************************************\n");

		printf("[1]上页|[2]下页|[3]添加群组|[4]解散群|[5]建群|[6]选择群聊|[7]退群|[8]踢人|[9]查看群消息记录|[10]刷新|[11]退出");
		printf("\n=======================================================================================\n");
		printf("your choice: ");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case 3:
			printf("[请不要输入已加入群uid] 请输入想要加入群的uid：");
			scanf("%d", &groupid);
			getchar();
			system("clear");
			if (UI_groupadd(conn_fd, groupid))
			{
				paging.totalRecords = groupnum;
				Paging_Locate_LastPage(headgroup, paging, box_node_t);
			}
			break;
		case 4:

			printf("[请不要输入你不是群主的群聊] 请输入解散群的uid：");
			scanf("%d", &groupid);
			getchar();
			system("clear");
			List_ForEach(headgroup, pos1)
			{

				if (pos1->data.recv_fd == groupid && pos1->data.send_fd == 1)
				{

					if (UI_groupdel(groupid, conn_fd))
					{
						List_DelNode(pos1);
						paging.totalRecords = groupnum;
						List_Paging(headgroup, paging, box_node_t);
					}
				}
				break;
				//meizai
			}

			break;
		case 5:
			if (UI_groupcreate(conn_fd))
			{
				paging.totalRecords = groupnum + 1;
				List_Paging(headgroup, paging, box_node_t);
			}
			break;
		case 6:
			printf("[不要输入不是你所加群的uid] 请输入选择的群聊uid：");
			scanf("%d", &grochatfd);
			getchar();
			system("clear");
			List_ForEach(headgroup, pos1)
			{
				if (pos1->data.recv_fd == grochatfd)
				{
					if (UI_groupchat(grochatfd, conn_fd))
					{
						paging.totalRecords = groupnum;
						List_Paging(headgroup, paging, box_node_t);
						grochatfd = 0;
					}
					break;
				}
			}

			break;
		case 7:

			printf("[不要输入不是你所加群的uid,和自己的创建的群] 请输入退出的群的uid：");
			scanf("%d", &groupid);
			getchar();
			system("clear");
			List_ForEach(headgroup, pos1)
			{
				if (pos1->data.recv_fd == groupid && pos1->data.send_fd != 1)
				{
					if (UI_groupout(groupid, conn_fd))
					{
						paging.totalRecords = groupnum - 1;
						List_Paging(headgroup, paging, box_node_t);
					}
					List_DelNode(pos1);
					break;
				}
			}

			break;
		case 8:
			printf("[不要输入你没有权限] 请选择你要踢人的群聊：");
			scanf("%d", &groupid);
			getchar();
			system("clear");
			List_ForEach(headgroup, pos1)
			{
				if (pos1->data.recv_fd == groupid && pos1->data.send_fd == 1)
				{
					if (UI_groupmbkick(groupid, conn_fd))
					{
						paging.totalRecords = groupnum;
						List_Paging(headgroup, paging, box_node_t);
					}
					break;
				}
			}
			break;

		case 9:
			printf("[不要输入不是你所加群的uid] 请输入你想要查看的群uid：");
			scanf("%d", &grochatfd);
			getchar();
			List_ForEach(headgroup, pos1)
			{
				if (pos1->data.recv_fd == grochatfd)
				{
					if (UI_gromessbox(grochatfd, conn_fd))
					{
						paging.totalRecords = groupnum;
						List_Paging(headgroup, paging, box_node_t);
					}
					break;
				}
			}
			break;
		case 10:
			List_Free(headgroup, box_node_t);
			senddata = (PACK *)malloc(sizeof(PACK));
			senddata->type = GROUP_SEE;
			senddata->data.send_fd = useruid;
			grosee = -1;
			if (send(conn_fd, senddata, sizeof(PACK), 0) > 0)
			{

				printf("-----------------------加载中-----------------------\n");
				while (grosee != 1)
				{
					pthread_cond_wait(&cond, &mutex);
				}
				system("clear");
				paging.totalRecords = groupnum;
				List_Paging(headgroup, paging, box_node_t);
			}
			break;
		case 1:
			system("clear");
			if (!Pageing_IsFirstPage(paging))
			{
				Paging_Locate_OffsetPage(headgroup, paging, -1, box_node_t);
			}
			break;
		case 2:
			system("clear");
			if (!Pageing_IsLastPage(paging))
			{
				Paging_Locate_OffsetPage(headgroup, paging, 1, box_node_t);
			}
			break;
		}
	} while (choice != 11);
	grosee = -1;
	free(senddata);
}

int login(int conn_fd)
{

	int flag;
	do
	{ //输入用户信息直到正确为止


		PACK *senddata = NULL;
		senddata = (PACK *)malloc(sizeof(PACK));
		senddata->type = LOGIN;

		flag = 0;
		printf("[小于20字节]usrname:");
		scanf("%s", senddata->data.send_name);

		printf("[小于20字节]password:");
		scanf("%s", senddata->data.recv_name);

		senddata->data.send_fd = conn_fd;
		input_userinfo(conn_fd, senddata); //发

		PACK *recvdata = NULL;
		recvdata = (PACK *)malloc(sizeof(PACK));

		int len_pack = LEN_PACK;
		char *p = (char *)(recvdata);
		while (len_pack > 0)
		{
			size_t n;
			if ((n = recv(conn_fd, p, len_pack, 0)) < 0)
			{
				if (errno != EAGAIN)
				{
					perror("recv");
					exit(1);
				}
			}

			len_pack -= n;
			p += n;
		}

		if (recvdata->type == LOGIN)
		{
			if (recvdata->data.mes[0] == 'y')
			{
				flag = 1;
				useruid = recvdata->data.recv_fd;
				strcpy(username, senddata->data.send_name);
				strcpy(password, senddata->data.recv_name);
				printf("useruid = %d", useruid);
				printf("登录成功\n");
				return 1;
			}
			else
			{
				printf("你的用户名和密码不匹配，请重新输入，退出请输【10086】，继续请输【0】");
				scanf("%d", &flag);
				getchar();
				if (flag == 10086)
				{
					return 0;
				}
			}
		}
		free(recvdata);
		free(senddata);
	} while (1);
	
}

void UI_loginin(int conn_fd)
{
	int choice;
	do
	{
		system("clear");
		printf("\n==============================\n");
		printf("*********** xunchat ************\n");
		printf("[1]  登录\n");
		printf("[2]  注册\n");
		printf("[3]  找回密码\n");
		printf("[4]  退出\n");

		printf("\n==============================\n");
		printf("请输出你的选择：");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
			//输入用户名和密码
		case 1:
			if (login(conn_fd))
			{
				return;
			}
			break;
		case 2:
			if (UI_zhuce(conn_fd))
			{
				return;
			}
			break;
		case 3:
			findpassword(conn_fd);
			break;
		case 4:
			exit(0);
			break;
		default:
			break;
		}
	} while (1);
}

int UI_zhuce(int conn_fd)
{

	int flag = 0;
	do
	{

		PACK *senddata = NULL;
		senddata = (PACK *)malloc(sizeof(PACK));
		senddata->type = REGISTER;

		printf("[请小于20个字符]usrname:");
		scanf("%s", senddata->data.send_name);

		printf("[请小于20个字符]password:");
		scanf("%s", senddata->data.recv_name);

		printf("[请小于20个字符]mibao:");
		scanf("%s", senddata->data.mes);

		printf("[1]是n|[2]是w|sex:");
		scanf("%d", &senddata->data.send_fd);

		input_userinfo(conn_fd, senddata); //发

		PACK *recvdata = NULL;
		recvdata = (PACK *)malloc(sizeof(PACK));

		int len_pack = LEN_PACK;
		char *p = (char *)(recvdata);
		while (len_pack > 0)
		{
			size_t n;
			if ((n = recv(conn_fd, p, len_pack, 0)) < 0)
			{
				if (errno != EAGAIN)
				{
					perror("recv");
					exit(1);
				}
			}
			printf("recv %zd bytes\n", n);
			len_pack -= n;
			p += n;
		}

		if (recvdata->type == REGISTER)
		{
			if (recvdata->data.mes[0] == 'y')
			{
				flag = 1;
				//recive(conn_fd,recvdata);
				printf("注册成功,输回车返回登录\n");
				getchar();
				return 0;
			}
			else
			{
				printf("你的用户名以使用过，请重新输入，或者选择退出，退出请输【10086】，继续请输【0】");
				scanf("%d", &flag);
				getchar();
				if (flag == 10086)
				{
					return 0;
					//exit(0);
				}
			}
		}
		free(senddata);
		free(recvdata);
	} while (1);
}

void UI_user(int conn_fd)
{
	int choice;
	do
	{
		system("clear");
		printf("\n=======================\n");
		printf("******** xunchat ********\n");
		printf("【1】查看好友列表\n");
		printf("【2】查看群列表\n");
		printf("【3】修改密码\n");
		printf("【4】查看消息盒子\n");
		printf("【5】退出登录\n");
		printf("【6】发送文件\n");
		printf("\n=======================\n");
		printf("请输出你的选择：");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case 1:
			watchfrilist(conn_fd);
			break;
		case 2:
			watchgrouplist(conn_fd);
			break;
		case 3:
			changepassword(conn_fd);
			break;
		case 4:
			watchlistbox(conn_fd);
			break;
		case 6:
			UI_filesend(conn_fd);
		default:
			break;
		}

	} while (5 != choice);

	close(conn_fd);
	return;
}

void changepassword(int conn_fd)
{

	char password1[20], password3[20];
	memset(password3, 0, sizeof(password3));
	memset(password1, 0, sizeof(password1));
	int cnt = 3;

	while (cnt--)
	{
		printf("你有%d次机会，请输入新密码:", cnt);
		scanf("%s", password1);
		getchar();
		//printf("%s%s",password1,password);

		if (strcmp(password1, password) == 0)
		{
			printf("新密码与旧密码相同，请重新输入\n");
			continue;
		}

		printf("请重新输入新密码:");
		scanf("%s", password3);
		getchar();

		if (strcmp(password1, password3) == 0)
		{
			strcpy(password, password3);

			PACK *senddata = NULL;
			senddata = (PACK *)malloc(sizeof(PACK));
			senddata->type = CHANGE_NUM;
			strcpy(senddata->data.mes, password3);
			strcpy(senddata->data.send_name, username);
			input_userinfo(conn_fd, senddata); //发
			free(senddata);
			break;
		}
		else
		{
			printf("两次密码输入不一致，请重新输入\n");
		}
	}
}

void findpassword(int conn_fd)
{
	char zhanghu[20], daan[20];
	memset(zhanghu, 0, sizeof(zhanghu));
	memset(daan, 0, sizeof(daan));

	printf("****** 找回密码 *******\n");
	printf("请输入账户:");
	scanf("%s", zhanghu);
	getchar();

	printf("请输入预留密保答案:");
	scanf("%s", daan);
	getchar();

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = FIND_PASSWD;
	strcpy(senddata->data.mes, daan);
	strcpy(senddata->data.send_name, zhanghu);
	input_userinfo(conn_fd, senddata); //发

	PACK *recvdata = NULL;
	recvdata = (PACK *)malloc(sizeof(PACK));

	int len_pack = LEN_PACK;
	char *p = (char *)(recvdata);
	while (len_pack > 0)
	{
		size_t n;
		if ((n = recv(conn_fd, p, len_pack, 0)) < 0)
		{
			if (errno != EAGAIN)
			{
				perror("recv");
				exit(1);
			}
		}
		//printf("recv %zd bytes\n", n);
		len_pack -= n;
		p += n;
	}

	senddata = (PACK *)malloc(sizeof(PACK));

	if (recvdata->data.mes[0] == 'y')
	{
		printf("答案正确！！！！请输入新密码：");
		scanf("%s", daan);
		getchar();
		senddata->type = CHANGE_NUM;
		strcpy(senddata->data.mes, daan);
		senddata->data.send_fd = conn_fd;
		strcpy(senddata->data.send_name, zhanghu);
		input_userinfo(conn_fd, senddata); //发

		PACK *recvdata = NULL;
		recvdata = (PACK *)malloc(sizeof(PACK));

		int len_pack = LEN_PACK;
		char *p = (char *)(recvdata);
		while (len_pack > 0)
		{
			size_t n;
			if ((n = recv(conn_fd, p, len_pack, 0)) < 0)
			{
				if (errno != EAGAIN)
				{
					perror("recv");
					exit(1);
				}
			}
			len_pack -= n;
			p += n;
		}
		if (recvdata->type == CHANGE_NUM)
		{
			if (recvdata->data.mes[0] == 'y')
			{
				printf("重置密码成功，按下回车键退出，请用新密码登录\n");
				getchar();
			}
		}
	}
	else
	{
		printf("密保问题错误，重置失败！,输入回车退出\n");
		getchar();
	}
	free(senddata);
	free(recvdata);
}

int UI_friendadd(int conn_fd)
{
	char friendname[20];
	memset(friendname, 0, sizeof(friendname));
	printf("请输入你要添加的好友名：");
	scanf("%s", friendname);
	getchar();

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = FRI_ADD;
	senddata->data.send_fd = useruid;
	strcpy(senddata->data.send_name, username);
	strcpy(senddata->data.mes, friendname);
	input_userinfo(conn_fd, senddata); //发
	printf("发送成功\n");
	free(senddata);
}

int UI_frienddel(int delfd, int conn_fd)
{

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = FRI_DEL;
	senddata->data.send_fd = delfd;
	strcpy(senddata->data.send_name, username);
	sprintf(senddata->data.mes, "%d", useruid);
	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}
int UI_groupadd(int conn_fd, int groupid)
{

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = GROUP_JOIN;
	senddata->data.send_fd = useruid;
	strcpy(senddata->data.send_name, username);
	sprintf(senddata->data.mes, "%d", groupid);

	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}

int UI_groupcreate(int conn_fd)
{

	char groupname[20];
	memset(groupname, 0, sizeof(groupname));
	printf("[在20个字符之内]请输入你要创建的群名：");
	scanf("%s", &groupname);
	getchar();

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));

	senddata->type = GROUP_CREATE;
	senddata->data.send_fd = useruid;
	strcpy(senddata->data.send_name, username);
	strcpy(senddata->data.mes, groupname);
	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}

int UI_groupmbkick(int groupid, int conn_fd)
{

	int friendname;
	printf("请输入你要清除的人uid号：");
	scanf("%d", &friendname);
	getchar();

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));

	senddata->type = GROUP_KICK;
	senddata->data.send_fd = groupid;
	sprintf(senddata->data.send_name, "%d", friendname);
	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}

int UI_groupout(int groupid, int conn_fd)
{

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));

	senddata->type = GROUP_QIUT;
	senddata->data.send_fd = groupid;
	sprintf(senddata->data.send_name, "%d", useruid);
	printf("%s", useruid);
	getchar();
	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}

int UI_groupdel(int groupid, int conn_fd)
{
	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));

	senddata->type = GROUP_DEL;
	senddata->data.send_fd = groupid;
	sprintf(senddata->data.send_name, "%d", useruid);
	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}

int UI_friendchat(int chatfd, int conn_fd)
{

	system("clear");
	char frimessage[MAX_CHAR];

	do
	{
		memset(frimessage, 0, sizeof(frimessage));
		PACK *senddata = NULL;
		senddata = (PACK *)malloc(sizeof(PACK));

		printf("you[|键退出]<<\n");
		gets(frimessage);
		//scanf("%s", frimessage);

		senddata->data.send_fd = chatfd;
		sprintf(senddata->data.send_name, "%d", useruid);
		//printf("%s\n",senddata->data.send_name);
		senddata->type = FRI_MES;
		strcpy(senddata->data.mes, frimessage);
		input_userinfo(conn_fd, senddata); //发
		free(senddata);

	} while (frimessage[0] != '|');
	chatfd = -1;
	return 1;
}

int UI_groupchat(int grochatfd, int conn_fd)
{

	system("clear");
	char gromessage[MAX_CHAR];
	do
	{
		memset(gromessage, 0, sizeof(gromessage));
		PACK *senddata = NULL;
		senddata = (PACK *)malloc(sizeof(PACK));
		strcpy(senddata->data.send_name, gromessage);

		printf("you[|键退出]<<\n");
		gets(gromessage);
		//sizeof(gromessage)
		//scanf("%s", gromessage);

		senddata->type = GRO_MES;
		senddata->data.send_fd = grochatfd;
		strcpy(senddata->data.recv_name, username);

		sprintf(senddata->data.send_name, "%d", useruid);
		strcpy(senddata->data.mes, gromessage);
		input_userinfo(conn_fd, senddata); //发
		free(senddata);

	} while (gromessage[0] != '|');
	grochatfd = -1;
}

void watchlistbox(int conn_fd)
{
	system("clear");
	int i, id;
	int choice;

	int mes;

	box_node_t *pos;
	Pagination_t paging;

	paging.offset = 0;
	paging.pageSize = PAGE_SIZE;

	paging.totalRecords = messnum;
	//返回有多少数量
	Paging_Locate_FirstPage(head, paging);
	do
	{
		printf(
			"\n=================================================\n");
		printf(
			"******************** 消息盒子信息 ********************\n");

		printf("%-3s|%-4s|%-4s|%-15s|%-50s\n", "uid", "发送fd", "接受fd", "type", "消息内容");
		printf("---------------------------------------------------\n");

		Paging_ViewPage_ForEach(head, paging, box_node_t, pos, i)
		{
			printf("%-3d|%-4d|%-4s|", pos->data.recv_fd, pos->data.send_fd, pos->data.recv_name);
			printtype(pos->data.type);
			printf("|%-50s\n", pos->data.mes);
		}

		printf("---Total Recoeds: %2d----Page %2d   %2d ---\n", paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));

		printf("*************************************************\n");

		printf("[1]上页 | [2]下页 | [3]回复消息 | [4]退出");
		printf("\n=======================================================================================\n");
		printf("your choice: ");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case 3:
			printf("请选择你要回复的消息的uid：");
			scanf("%d", &mes);
			List_ForEach(head, pos)
			{
				if (mes == pos->data.recv_fd)
				{
					if (pos->data.type == FRIQUE)
					{
						List_DelNode(pos);
						messnum--;
						judgeaddfri(mes, conn_fd);
					}
					else if (pos->data.type == GROQUE)
					{
						List_DelNode(pos);
						messnum--;
						judgeaddgro(mes, conn_fd);
					}
					else if (pos->data.type == FRI_MES)
					{
						List_DelNode(pos);
						messnum--;
						printf("请去查看好友哪里去回复此人\n");
					}
					else if (pos->data.type == GRO_MES)
					{
						List_DelNode(pos);
						messnum--;
						printf("请去查看群聊的哪里回复该群\n");
					}
				}
			}

			paging.totalRecords = messnum;
			List_Paging(head, paging, box_node_t);
			break;
		case 1:
			system("clear");
			if (!Pageing_IsFirstPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, -1, box_node_t);
			}
			break;
		case 2:
			system("clear");
			if (!Pageing_IsLastPage(paging))
			{
				Paging_Locate_OffsetPage(head, paging, 1, box_node_t);
			}
			break;
		}
	} while (choice != 4);
	//List_FreeNode(node);
}

int UI_frimessbox(int chatfd, int conn_fd)
{

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = CHAT_ONE;
	senddata->data.send_fd = chatfd;
	sprintf(senddata->data.send_name, "%d", useruid);

	ssize_t n = send(conn_fd, senddata, sizeof(PACK), 0);
	//printf("send %zd bytes\n", n);
	printf("-----------------------加载中------------------------\n");
	printf("输入回车退出\n");
	getchar();
	free(senddata);
}

int UI_gromessbox(int grochatfd, int conn_fd)
{

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	senddata->type = CHAT_MANY;
	senddata->data.send_fd = grochatfd;
	ssize_t n = send(conn_fd, senddata, sizeof(PACK), 0);
	//printf("send %zd bytes\n", n);
	printf("-----------------------加载中-----------------------\n");
	printf("输入回车退出\n");
	getchar();
	free(senddata);
}

void judgeaddfri(int mes, int conn_fd)
{

	printf("请输入你是否同意好友添加[y] or [n] \n");

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	scanf("%s", senddata->data.mes);
	senddata->type = FRIQUE;
	senddata->data.send_fd = mes;
	strcpy(senddata->data.send_name, username);
	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}
void judgeaddgro(int mes, int conn_fd)
{

	printf("请输入你是否同意群组添加[y] or [n] \n");

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	scanf("%s", senddata->data.mes);
	senddata->type = GROQUE;
	senddata->data.send_fd = mes;
	strcpy(senddata->data.send_name, username);
	input_userinfo(conn_fd, senddata); //发
	free(senddata);
}

int UI_filesend(int conn_fd)
{

	PACK *senddata = NULL;
	senddata = (PACK *)malloc(sizeof(PACK));
	int sum = 0, re, fd;

	printf("请输入对方的uid:");
	scanf("%d", &senddata->data.send_fd);
	printf("请输入本目录下的文件名:");
	scanf("%s", senddata->data.send_name);

	fd = open(senddata->data.send_name, O_RDONLY);

	senddata->type = FILE_SEND_BEGIN_RP;
	sum = read(fd, senddata->data.mes, sizeof(senddata->data.mes));

	//printf( "sum = %d\n",sum);
	while (sum != 0)
	{

		if ((re = (send(conn_fd, senddata, sizeof(PACK), 0))) < 0)
			my_err("send", __LINE__);

		printf("sum = %d\n", sum);

		sum = read(fd, senddata->data.mes, sizeof(senddata->data.mes));

		if (sum < 0)
			break;
	}
	close(fd);
	free(senddata);
	printf("客户端发送成功！\n");
}

void printtype(int type)
{

	switch (type)
	{
	case FRI_ADD:
		printf("addfriend  ");
		break;
	case FRI_MES:
		printf("frienchat  ");
		break;
	case GRO_MES:
		printf("groupchat  ");
		break;

	case GROUP_JOIN:
		printf("groupjoin  ");
		break;

	case FRIQUE:
		printf("judgeaddfri");
		break;

	case GROQUE:
		printf("judgeaddgro");
		break;
	default:
		break;
	}
}