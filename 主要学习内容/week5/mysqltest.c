#include <stdio.h>  
#include <stdlib.h>  
#include <mysql/mysql.h>
#include <string.h>
#define MAX_CHAR 1024

typedef struct login
{
    char username[20];
    char password[20];
}login_data;
int main() {  
    

    login_data * data1;
    data1  = (login_data *)malloc(sizeof(login_data));

    strcpy(data1->username,"tt");
    strcpy(data1->password,"123456");
    MYSQL conn_ptr;  
    MYSQL_RES *res_ptr;  
    MYSQL_ROW sqlrow;  
    MYSQL_FIELD *fd;  
    int res, i, j;  

    char buffer[MAX_CHAR];
    /* sprintf(buffer,"select password from 用户数据 where `name` = %s",data1->username); */
    /* scanf("%s",); */
    
    sprintf(buffer,"select password from 用户数据 where password = '%s' and name = '%s'",data1->password,data1->username);
    /* printf("%s",data1->password); */

    if (mysql_init(&conn_ptr) == NULL) {  
        return EXIT_FAILURE;  
    }  
    if((mysql_real_connect(&conn_ptr, "127.0.0.1", "root", "123456", "xunchat",0, NULL, 0)) == NULL){
        perror("mysql_real_connect");

    }
    //设置中文字符集
    if(mysql_set_character_set(&conn_ptr, "utf8") < 0){
        perror("mysql_set_character_set");
    }
    if (1) 
    {  
        /* res = mysql_query(&conn_ptr,"select password from 用户数据 where `name` = 'tt'"); //查询语句 */  
        res = mysql_query(&conn_ptr,buffer); //查询语句  
        if (res) 
        {         
            printf("SELECT error:%s\n",mysql_error(&conn_ptr));     
        } else 
        {        
            res_ptr = mysql_store_result(&conn_ptr);             //取出结果集  mysql_store_result()立即检索所有的行，
            if(res_ptr) 
            {   
                //	int num = (unsigned long)mysql_num_rows(res_ptr);
                printf("%lld Rows\n",mysql_num_rows(res_ptr));   //返回所有的行
                j = mysql_num_fields(res_ptr);//获取 列数    
                while((sqlrow = mysql_fetch_row(res_ptr)))  
                {   //依次取出记录  
                    for(i = 0; i < j; i++)
                        printf("%s\t", sqlrow[i]);              //输出  
                    printf("\n");          
                }              
                if (mysql_errno(&conn_ptr)) 
                {                      
                    fprintf(stderr,"Retrive error:s\n",mysql_error(&conn_ptr));               
                }        
            }        
            mysql_free_result(res_ptr);        //释放空间
        }  
    } else 
    {  
        printf("Connection failed\n");  
    }  
    mysql_close(&conn_ptr);  
    return EXIT_SUCCESS;  
}
