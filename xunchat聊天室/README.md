编译客户端
gcc -o my_client all.h md5.c md5.h my_client.c my_recv.c list.h my_recv.h -lpthread
编译服务器
gcc -I/usr/include/mysql my_server.c md5.c md5.h my_recv.c my_recv.h all.h list.h my_serthread.c my_serthread.h -L/usr/lib/mysql  -lmysqlclient -lpthread -o my_server
运行客户端，参数懂得都懂
./my_client -a 127.0.0.1 -p 4507
运行服务器
./my_server

项目文档https://blog.csdn.net/weixin_43574962/article/details/100026191

