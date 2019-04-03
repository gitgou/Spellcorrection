 ///
 /// @file    WorkerThread.cc
 /// @author  yll(1711019653@qq.com)
 /// @date    2018-07-02 17:26:03
 ///
 

#include "WorkerThread.h"
#include "Threadpool.h"


using namespace wd;

void WorkerThread::run()
{
	_threadpool.threadFunc();
}
