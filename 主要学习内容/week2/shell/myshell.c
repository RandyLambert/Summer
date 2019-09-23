#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>     // exit
#include <string.h>
#include <fcntl.h>      // O_RDWR
#include <dirent.h>     // DIR, struct dirent 
#include <sys/wait.h>
#include <wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<readline/readline.h>
#include<readline/history.h>

#define BUFFSIZE 64
#define normal 0        // 一般的命令
#define out_redirect 1  // 输出重定向
#define outtwo_redirect 4 //>>
#define in_redirect 2   // 输入重定向
#define have_pipe 3     // 命令中有管道

void print_prompt();    // 打印提示符
// 二维数组作为函数参数，第1维长度可以不指定，但必须指定第2维长度
// 也可使用指向含8个元素一维数组的指针，char (*a)[8]
void explain_input(char *, int *, char a[][256]); // 解析输入的命令
void do_cmd(int, char a[][256]);  // 执行命令
int find_command(char *);       // 查找命令中的可执行程序
char aaa[256];
char past[256];

int main(int argc, char *argv[])
{
    signal(SIGINT,SIG_IGN);
    char arglist[100][256];
    int argcount = 0;
    char **arg = NULL;
    char *buf = NULL;
    buf = (char*)malloc(256);



    while(1)
    {
        memset(buf,0,256);
        print_prompt(); // 打印提示符
        char *str = readline("\033[37mSSX)\033[0m$ ");
        add_history(str);
        strcpy(buf,str);
        
        if(str!=NULL){
            free(str);
            str = NULL;
        }
        if(strcmp(buf,"exit")==0 || strcmp(buf,"logout") == 0){
            break;
        }

        if(strcmp(buf,"\0")==0) continue;

        for(int i=0; i<100; i++)     // 初始化存放命令及其参数的数组
            arglist[i][0] = '\0';

            argcount = 0;   // 计数，命令中词汇数量
            explain_input(buf, &argcount, arglist); // 解析命令
            do_cmd(argcount, arglist);      // 执行命令
            if(str != NULL){
                free(str);
                str = NULL;
        }
    }
    
    if(buf!=NULL){
        free(buf);
        buf = NULL;
    }

    exit(0);

}


void print_prompt()
{
    getcwd(aaa,256);
    printf("\033[34m%s(from \033[0m",aaa);
    //      fflush(stdout); // fflush 冲洗stdout
}


// 解析buf中的命令，结果存入arglist中，命令及其参数个数为argcount
// 如，"ls -l"命令，则arglist[0]、arglist[1]分别为ls、-l
void explain_input(char *buf, int *argcount, char arglist[100][256])
{
    /* printf("%s",buf); */
    char *p = buf;
    char *q = buf;
    int number = 0;

    while(1){
        if(p[0] == '\n')
            break;

        if(p[0] == ' ')
            p++;
        else{
            q = p;
            number = 0;
            while((q[0]!='\n') && (q[0]!=' ')){
                number++;
                q++;
            }
            strncpy(arglist[*argcount],p,number+1);
            arglist[*argcount][number] = '\0';
            *argcount = *argcount + 1;
            p = q;
        }
    }


    /* for(int i = 0;i < *argcount;i++){ */
    /*     printf("dasd:%s\n",arglist[i]); */
    /* } */
}





void do_cmd(int argcount, char arglist[100][256])
{
    // 指针数组，每个元素指向二维数组中的一行
    // arg存放所有命令及其参数，argnext存放管道符后的命令
    char *arg[argcount+1], *argnext[argcount+1];
    int i, flag = 0, how = 0, background = 0, cnt = 0;
    char *file;
    pid_t pid;
    int fd,status;

    // 提取命令
    for(int i = 0;i < argcount;i++){
        arg[i] = (char *)arglist[i];
        /* printf("%s\n",arg[i]); */
    }
    
    arg[argcount] = NULL;
    /* printf("%s\n",arg[0]); */




    //查看命令行是否有后台运行符


    for(int i = 0;i < argcount;i++){
        if(strncmp(arg[i],"&",1) == 0){
            if(i == argcount - 1){
                background = 1;
                arg[argcount-1] = NULL;
                break;
            }
            else{
                printf("wrong command\n");
                return ;
            }
        }
    }

    for(i=0; arg[i]!=NULL; i++)
    {
        if(strcmp(arg[i], ">") == 0)
        {
            flag++;
            how = out_redirect;
            if(arg[i+1] == NULL)    // 输出重定向符在最后面
                flag++; // 使flag大于1，告知命令格式错误
        }
        if(strcmp(arg[i], "<") == 0)
        {
            flag++;
            how = in_redirect;
            if(i == 0)      // 输入重定向符在最前面
                flag++;//使flag大于1，告知命令格式错误
        }
        if(strcmp(arg[i], "|") == 0)
        {
            flag++;
            how = have_pipe;
            if(arg[i+1] == NULL)    // 管道符在最后面
                flag++;
            if(i == 0)      // 管道符在最前面
                flag++;         //同上
        }
        if(strcmp(arg[i], ">>") == 0)
        {
            flag++;
            how = outtwo_redirect;
            if(arg[i+1] == NULL)    // 输出重定向符在最后面
                flag++; // 使flag大于1，告知命令格式错误
        }
        
    }
    // flag大于1，说明同时含有>,<,|中的两个或以上，本程序不支持
    // 或者命令格式错误
    if(flag > 1){
        printf("ERROR: wrong command about >,<,|\n");
        return;
    }

    if(strcmp(arg[0],"ls") == 0){
        strcpy(arglist[argcount],"--color");
        arg[argcount] = (char *)arglist[argcount];

        argcount = argcount + 1;
        arg[argcount] = NULL;
    }
    else{
        arg[argcount] = NULL;
    }
    
    if(strncmp(arg[0],"cd",2) == 0){
        
        if(argcount == 1){
            strcpy(past,aaa);
            chdir("/home/sunxiaochuan/");
            return ;
        }
        if(strncmp(arg[1],"~",1) == 0 || argcount == 1){
            strcpy(past,aaa);
            chdir("/home/sunxiaochuan/");
            return ;
        }
        else if(strncmp(arg[1],"-",1) == 0){
            if(past[0] == '\0' && past[1] == '\0'){
                printf("ERROR: wrong command about cd\n");
                return ;
            }
            else{
                if(chdir(past) == -1){
                    printf("bash: cd: %s: 没有那个文件或目录\n",arg[1]);
                }
            }
        }
        else if(argcount == 2){
            strcpy(past,aaa);
            if(chdir(arg[1]) == -1){
                printf("bash: cd: %s: 没有那个文件或目录\n",arg[1]);
            }
        }
        return ;
    }

    if(how == outtwo_redirect){
        for(i = 0; arg[i]!=NULL;i++){
            if(strcmp(arg[i], ">>") == 0)
            {
                file = arg[i+1]; // 获取输出重定向的文件名
                arg[i] = NULL;
            }
        }
    }
    if(how == out_redirect) // 命令中只含有一个输出重定向符
    {
        for(i=0; arg[i]!=NULL; i++)
            if(strcmp(arg[i], ">") == 0)
            {
                file = arg[i+1]; // 获取输出重定向的文件名
                arg[i] = NULL;
            }
    }

    if(how == in_redirect)  // 命令中只含有一个输入重定向符
    {
        for(i=0; arg[i] != NULL; i++)
            if(strcmp(arg[i], "<") == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
    }

    if(how == have_pipe)    // 命令中只含有一个管道符号
    {
        for(i=0; arg[i]!=NULL; i++)
            if(strcmp(arg[i], "|") == 0)
            {
                arg[i] = NULL;
                i++;
                int j = 0;
                // 将管道符后面的命令存入argnext中
                while(arg[i] != NULL)
                {
                    argnext[j++] = arg[i++];
                }
                argnext[j] = NULL;
                break;
            }
    }
    if((pid = fork()) < 0){
        printf("fork error\n");
    }


    switch(how){
    case 0:
        //pid为0说明是子进程，在子进程中执行输入的命令
        //输入的命令中不含》《|
        if(pid == 0){
            if(!(find_command(arg[0]))){
                printf("%s : command not found\n",arg[0]);
                exit(0);
            }
            execvp(arg[0],arg);
            exit(0);
        }
        break;
    case 1:
        if(pid == 0)//>
        {
            if(!find_command(arg[0]))
            {
                printf("%s: command not found\n", arg[0]);
                exit(0);
            }
            // 打开或新建输出重定向的文件
            int fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
            // 将标准输出复制到打开的文件描述符，即用文件描述符替换标准输出
            dup2(fd, 1);    // dup2(int oldfd, int newfd)
            execvp(arg[0], arg);    // execvp
            exit(0);
        }
        break;
    case 2: // 命令中含有输入重定向符
        if(pid == 0)//<
        {
            if(!find_command(arg[0]))
            {
                printf("%s: command not found\n", arg[0]);
                exit(0);
            }
            int fd = open(file, O_RDONLY);
            dup2(fd, 0);
            execvp(arg[0], arg);
            exit(0);
        }
        break;
    case 3:
        if(pid == 0){
            int pid2;
            int status2;
            int fd2;

            if((pid2 = fork()) < 0){
                printf("fork2 error\n");
                return ;
            }
            else if(pid2 == 0){
                if(!(find_command(arg[0]))){
                    printf("%s : command not found\n",arg[0]);
                    exit(0);
                }
                fd2 = open("/tmp/youdonotknowfile",O_WRONLY|O_CREAT|O_TRUNC,0664);
                dup2(fd2,1);
                execvp(arg[0],arg);
                exit(0);
            }

            if(waitpid(pid2,&status2,0)==-1){
                printf("wait for child process error\n");
            }

            if(!(find_command(argnext[0]))){
                printf("%s: command not found\n", argnext[0]);
                exit(0);
            }
            fd2 = open("/tmp/youdonotknowfile",O_RDONLY);
            dup2(fd2,0);
            execvp(argnext[0],argnext);
            if(remove("/tmp/youdonotknowfile"))
                printf("remove error\n");
            exit(0);
        }
        break;
    case 4:
        if(pid == 0)//>>
        {
            if(!find_command(arg[0]))
            {
                printf("%s: command not found\n", arg[0]);
                exit(0);
            }
            // 打开或新建输出重定向的文件
            int fd = open(file, O_RDWR | O_APPEND | O_CREAT , 0644);
            // 将标准输出复制到打开的文件描述符，即用文件描述符替换标准输出
            dup2(fd, 1);    // dup2(int oldfd, int newfd)
            execvp(arg[0], arg);    // execvp
            exit(0);
        }
        break;
    default:
        break;

    }

    //如果命令中有&则在后台清空
    if(background == 1){
        printf("[process id %d]\n",pid);
        return ;
    }

    if(waitpid (pid,&status,0) == -1){
        printf("wait for child process error\n");
    }

    //
}


int find_command(char *command){
    DIR *dp;
    struct dirent *dirp;
    char *path[] = {"./", "/bin", "/usr/bin", NULL};
    // 当输入命令"./build"时，将build命令与目录中的build文件进行匹配
    if(strncmp(command,"./",2) == 0){
        command = command + 2;
    }
    int i = 0;
    //分别在当前目录，/bin,/usr/bin目录下查找要执行的程序
    while(path[i]!=NULL){
        if( (dp = opendir(path[i])) == NULL){
            printf("opendir error\n");
        }
        while((dirp = readdir(dp)) != NULL){
            if(strcmp(dirp->d_name,command) == 0){
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}
