#include "Thread.h"

Thread::Thread(ThreadFunc func, const string& name) 
	: started_(false),
	  joined_(false),
	  pthreadId_(0),
	  tid_(0),
	  func_(std::move(func)),
	  name_(name) {
	setDefaultName();
}	

Thread::~Thread() {

}