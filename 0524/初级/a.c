hello world
#pragma  once
#include"UdpNet.h"


UdpNet::UdpNet(INetMediator* pMediator):m_sock(INVALID_SOCKET),m_hthreadHandle(0),m_bIsStop(false)
{
	m_pMediator = pMediator;
}
UdpNet::~UdpNet()
{
	UnInitNet();
}
//初始化网络
bool  UdpNet::InitNet()
{
	//1.选个项目-加载库   wsa-windows socket api
	WORD wVersionRequested={0};
	WSADATA wsaData={0};
    int result=0;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2,2);

    result = WSAStartup(wVersionRequested, &wsaData);
    if (result != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        return false;
    }

	/* Confirm that the WinSock DLL supports 2.2.*/
	/* Note that if the DLL supports versions greater    */
	/* than 2.2 in addition to 2.2, it will still return */
	/* 2.2 in wVersion since that is the version we      */
	/* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        //printf("Could not find a usable version of Winsock.dll\n");
		UnInitNet();//关闭网络
        return false;
    }
    /*else
        printf("The Winsock 2.2 dll was found okay\n");
 */
	//2.(雇个人)创建套接字
	m_sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (m_sock == INVALID_SOCKET) 
	{
		//WSAGetLastError获取具体的错误码
		//printf("socket function failed with error = %d\n", WSAGetLastError());
		UnInitNet();//关闭网络
        return false;
	}

	//3.设置广播权限
	BOOL bflag=TRUE;
	setsockopt(m_sock,SOL_SOCKET,SO_BROADCAST,(char*)&bflag,sizeof(bflag));

	//4.绑定IP地址
	sockaddr_in addrClient;
	addrClient.sin_family = AF_INET;//IPV4协议族
	addrClient.sin_addr.S_un.S_addr=INADDR_ANY;//绑定任意网卡，推荐服务器端使用
	addrClient.sin_port = htons(_DEF_UDP_PORT);//htons将证书转为网络字节序
	result = bind(m_sock,(SOCKADDR*) &addrClient,sizeof(addrClient));
	if (result == SOCKET_ERROR) {
		UnInitNet();//关闭网络
        return false;
	}
	
    //接收数据-创建线程     C/C++ RunTime 库  strcpy  创建内存块  CreateThread创建的线程不会回收内存块，造成内存泄露
	//ExitThread退出线程   _beginthreadex底层也是调用CreateThread，退出时调用ExitThread，并且回收创建的内存块
	m_hthreadHandle =(HANDLE)_beginthreadex(NULL,0,&recvThread,this,0,NULL);



	return true;
}
unsigned int _stdcall UdpNet::recvThread(void* lpvoid)
{
	UdpNet* pThis = (UdpNet*)lpvoid;
	pThis->RecvData();
	return 0;
}
//关闭网络
void  UdpNet::UnInitNet()
{
	//线程退出
	if(m_hthreadHandle)
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hthreadHandle,100))
		{
			TerminateThread(m_hthreadHandle,-1);
		}
		m_hthreadHandle = 0;
		m_bIsStop = true;
	}
	//关闭socket
	if(m_sock != INVALID_SOCKET)
	{
		closesocket(m_sock);
	}
	//卸载库
	WSACleanup();
}
//发送数据
bool  UdpNet::SendData(long lSendIp,char  *buf,int  nLen)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_DEF_UDP_PORT);
	addr.sin_addr.S_un.S_addr=lSendIp;
	if( sendto(m_sock,buf,nLen,0,(sockaddr*)&addr,sizeof(addr))<=0 )
	{
		return false;
	}
	return true;
}
void  UdpNet::RecvDa
{
	char recvBuf[_DEF_BUFFER_SIZE]="";
	sockaddr_in addr;
	int nSize = sizeof(addr);
	int recvNum=0;
	while(!m_bIsStop)
	{
		recvNum = recvfrom(m_sock,recvBuf,sizeof(recvBuf),0,(sockaddr*)&addr,&nSize);
		if(recvNum > 0)
		{//转发给中介者类
			char* Packbuf = new char[recvNum];
			memcpy(Packbuf,recvBuf,recvNum);
			if(m_pMediator)
			{
				m_pMediator->DealData(addr.sin_addr.S_un.S_addr,Packbuf,sizeof(Packbuf));
				//记得回收空间  delete[] Packbuf
			}
		}
	}
	


}


