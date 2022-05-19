/****************************************************“
  > File Name: socket_api.c
  > Author: youzhiwei
  > EMail: 859971493@qq.com
  > Created Time: 2022年04月21日 星期四 19时49分28秒
    > Modified Time:2022年04月21日 星期四 21时04分07秒
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	//网络信息结构体，网络数据缓存在网络设备中，采用大断存储，低地址高字节，高地址低字节
	//大小端转换的常用函数接口
	//htonl()
	//htons()
	//ntohl()
	//ntohs()
	//inet_pton()字符串ip地址转为大端序ip地址
	//inet_ntop()大端序ip地址转换为字符串ip
	//
	//linux操作系统下，所有设备的访问方式都是文件方式，socket访问也是文件描述符
	//
	//
	//socket创建之后默认就有缺省内容，port为随机端口，ip 为本机任意ip 0.0.0.0 如果不需要自定义指定ip或端口，那么这个socket可以直接使用
	//socket(AF_INET,SOCK_STREAM|SOCK_DGRAM,0)protocal = 0表示采用默认协议
	//
	//bind(socketfd,(socket*)&addr,sizeof(addr))
	//
	//
}
