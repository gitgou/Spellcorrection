 ///
 /// @file    WorkThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-02 16:57:52
 ///
 
#ifndef __WD_WORKERTHREAD_H__
#define __WD_WORKERTHREAD_H__

#include "Thread.h"
#include <iostream>
using namespace std;

namespace wd
{

class Threadpool;

class WorkerThread
: public Thread
{
public:
	WorkerThread(Threadpool & threadpool)
	: _threadpool(threadpool)
	{	
        LogWarn("A new workerthread was created.");
        cout << "WorkerThread()" << endl;	
    }


	~WorkerThread() {	cout << "~WorkThread()" << endl;	}
private:
	void run();
	Threadpool & _threadpool;
};

}//end of namespace wd

#endif
