 ///
 /// SpellCorrectionServer.h
 /// Created by yll(1711019653@qq.com).
 /// 2019-2-28 20:31:43 
 /// @Brief: 
 ///

#ifndef __MAINSERVER_H__
#define __MAINSERVER_H__

#include "CacheManager.h"
#include "TcpServer.h"
#include "Threadpool.h"
#include "MyDict.h"
#include "QueryTask.h"
#include "Config.h"
#include "TimerThread.h"
#include "Mylog.h"
#include <iostream>
#include <memory>
void onConnection(const wd::TcpConnectionPtr&);
void onMessage(const wd::TcpConnectionPtr&);
void onClose(const wd::TcpConnectionPtr&);

class MainServer{
    friend void onConnection(const wd::TcpConnectionPtr&);
    friend void onMessage(const wd::TcpConnectionPtr&);
    friend void onClose(const wd::TcpConnectionPtr&);
public:
    MainServer(const string& ConfigPath)
    : _configMap(Config::getInstance(ConfigPath)->getConfigMap())
    , _threadpool(stoi(_configMap["ThreadpoolCap"]),stoi(_configMap["TaskQueSize"]))
    , _tcpserver(_configMap["ServerIP"], (stoi(_configMap["Port"])))
    , _cacheMgr(_configMap["cachePath"])
    , _timer(5, 5, bind(&CacheManager::periodcUpdate, &_cacheMgr))
    {
    }
    void start();
    void stop();
private:
    map<string, string> &_configMap;
    wd::Threadpool _threadpool;
    wd::TcpServer _tcpserver;
    MyDict* _dict;
    CacheManager _cacheMgr;
    wd::TimerThread _timer;
};




#endif 
