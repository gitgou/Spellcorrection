 ///
 /// @file    testTimer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-07-06 16:34:56
 ///
 
#include "TimerThread.h"

#include <unistd.h>
#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

struct Producer
{
	void getNumber()
	{
		::srand(::time(NULL));
		int number = ::rand() % 100;
		cout << "TimerThread: " << pthread_self() << ">>> getNumber = " << number << endl;
	}
};
 
int main(void)
{
	wd::TimerThread timer(3, 6, std::bind(&Producer::getNumber, Producer()));
	timer.start();
	sleep(30);
	//....
	timer.stop();
	return 0;
}
