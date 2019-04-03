 ///
 /// @file    TcpServer.h
 /// @author  yll(1711019653@qq.com)
 /// @date    2018-08-12 16:21:37
 ///
 
#ifndef __WD_TCPSERVER_H__
#define __WD_TCPSERVER_H__

#include "Acceptor.h"
#include "EpollPoller.h"
#include "Mylog.h"
#include <string>

using std::string;

namespace wd
{


class TcpServer
{
public:
	typedef EpollPoller::EpollCallback TcpServerCallback;
	TcpServer(const string & ip, unsigned short port);
	TcpServer(unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);
private:
	Acceptor acceptor_;
	EpollPoller poller_;

	TcpServerCallback connectionCallback_;
	TcpServerCallback messageCallback_;
	TcpServerCallback closeCallback_;
};


}//end of namespace wd

#endif
