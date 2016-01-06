//***************************************************************
//*              Name of File : timer.cpp                       *
//*              for :  Time-Event generator                    *
//*                  by : 古清德                                *
//***************************************************************

#include "timer.h"

#include <algorithm>
#include <fstream>

// anonymous namespace 表示在該 namespace 內的變數只能用在該檔案之內
namespace
{
 //const int TIME_UP=1;
 unsigned long int cur_time=0;
 //bool timer_on=false; 
}

bool DS::Timer::timer_on;


DS::TimerCounter::TimerCounter( Model *app, unsigned long msec ):_cur_time(0)
{
 _model = app;
 _event.set_event(DS::evTimer);
 _time=msec;

}

// 每 1 microsecond 呼叫一次,當 static 變數 time 為所設定的時間 _time,
// 呼叫 linkApp 之 from_controller()
void DS::TimerCounter::go() 
{
 static int time=0;
 //_cur_time=cur_time;
 //if (_cur_time==_time)
 static std::ofstream f("time"); 
 if (time==_time)
 {
  //f << _time << std::endl;
  _model->from_control(_event);
  //_cur_time=0;
  time=0;
 }
 else
 {
  ++time;
  f << time << std::endl;
 }
}

DS::Timer::Timer()
{
 //DS::alarm(TIME_UP);
 //timer_on=false; 

 signal(SIGALRM,catch_alarm);
 Timer::alarm(TIME_UP);
}

int DS::Timer::pool()
{
 if (timer_on == true)  // timer_on 若為 true ，表示 1 microsecond 的間隔已到
 {
  std::vector<TimerCounter *> :: iterator it;
  for (it = _applier.begin() ; it != _applier.end() ; it++)
   (*it)->go();
  timer_on=false;
 }
 return 1;
}

void DS::Timer::apply( Model *app, unsigned int msec )
{
 // 每多一個申請者 ,便 new 一個 TimerCounter 與之鏈結 ,然後加入申請者串列中即可
 _applier.push_back( new TimerCounter( app ,msec ) );
}


// static function
void DS::Timer::catch_alarm(int sig)
{
 timer_on=true;
 ++cur_time;
 //DS::alarm(TIME_UP);
 signal(sig,catch_alarm);
 Timer::alarm(TIME_UP);
}


// 設定計時器以 microsecond 為單位
// static function
unsigned long int DS::Timer::alarm(unsigned long int msec)
{
 struct itimerval old_time,new_time;
 new_time.it_interval.tv_usec=0;
 new_time.it_interval.tv_sec=0;
 new_time.it_value.tv_usec=msec;
 new_time.it_value.tv_sec=0;
 if (setitimer(ITIMER_REAL,&new_time,&old_time) < 0) // error
  return 0;
 else
  return old_time.it_value.tv_usec;
}
