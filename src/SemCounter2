#ifndef SEMCOUNTER
#define SEMCOUNTER

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

class SemCounter {
private:
  int value;
  std::mutex mutex_;
  std::mutex mutex_block;

  void block();
  void unblock();
  
public:
  SemCounter(int value);  
  void wait();
  void signal();
  int getValue();
};

SemCounter::SemCounter(int v): value(v){};
	

void SemCounter::block(){mutex_block.lock();}
void SemCounter::unblock(){mutex_block.unlock();}

void SemCounter::wait() {
  
  mutex_.lock();
  if(--value <= 0){
    mutex_.unlock();
    block();
    mutex_.lock();
  }
  mutex_.unlock();
  
}
 

void SemCounter::signal() {
    
  mutex_.lock();
  if(++value <= 0){
       unblock();
       /*damos tiempo para que se realice el desbloqueo correctamente*/
       std::this_thread::sleep_for(std::chrono::milliseconds(200));

  }
   mutex_.unlock();
}

int SemCounter::getValue(){
  return value;
}

#endif