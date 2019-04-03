 ///
 /// @file    TaskQueue.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-02 15:33:17
 ///

 
#include "TaskQueue.h"

using namespace wd;
 
//生产者所在的线程
void TaskQueue::push(Task * t)
{
	MutexLockGuard autoLock(_mutex);

	while(full())	
	{
		_notFull.wait();
	}

	_que.push(t);
	_notEmpty.notify();
}

//消费者所在的线程
Task * TaskQueue::pop()
{
	MutexLockGuard autoLock(_mutex);
	while(_flag && empty())
	{
		_notEmpty.wait();//在这里阻塞
	}

	if(_flag) {
		Task * t = _que.front();
		_que.pop();
		_notFull.notify();
		return t;
	} else
		return NULL;
}
