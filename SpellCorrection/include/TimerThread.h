 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-06 16:43:53
 ///
 
#ifndef __WD_TIMERTHREAD_H__
#define __WD_TIMERTHREAD_H__

#include "Timer.h"
#include "bo_Thread.h"

#include <functional>

namespace wd
{
	
class TimerThread
{
public:
	using TimerCallback = std::function<void()>;
	TimerThread(int, int, TimerCallback && cb);

	void start();
	void stop();

	~TimerThread();

private:
	Timer _timer;
	boThread _subThread;
	bool _isStarted;
};
}//end of namespace wd

#endif
