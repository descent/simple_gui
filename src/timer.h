/*
 * $Revision$
 * $Author$
 * $Id$
 * $Date$
 * function : 時間產生器，所申請的時間以秒為單位
 */

#ifndef TIMER_H
#define TIMER_H

//#include "contitem.h"
//#include "type.h"
//#include "struct.h"
//#include "dlist.h"
#include "model.h"
#include "controller_item.h"
#include "event.h"

#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#include <vector>

// TimerCounter 為一設計用來管理每一個時間申請者的類別。個體中計錄了所代表的模組
// 及它所申請的時間間隔 ,每 1/18 秒呼叫一次 ++ 函式 ,此個體自動統計時間 ,而時間
// 一到 ,自動將訊息傳給所代表的個體 ,不需程式設計者再操心
// 被我所更改的 timer 目前只能以秒為單位來申請時間

// function object
/*
class FindModel
{
 public:
  bool operator(const TimerCounter & t1,const TimerCounter & t2)
  {
  }

};
*/

namespace DS
{
 // 設定計時器以 microsecond 為單位
 //void catch_alarm(int sig);

 class TimerCounter
 {
  //friend void DS::catch_alarm(int sig);
  public:
   TimerCounter( Model *app ,unsigned long msec );
   // app 為時間到時呼叫之模組, msec 為 microsecond
   //virtual unsigned is()  {  return TimerCounterCls;  }
   void go(); //每 1 秒呼叫一次 ,次數一到,自動呼叫 linkApp 之 from_controller()
   //const Model* getModel() { return _linkApp;  }
   TimerCounter() {}

  private:
   unsigned long _time; // Model 申請的時間，以 microsecond 為單位
   unsigned long _cur_time; // 目前累積的時間，以 microsecond 為單位

   DS::Model *_model;   // 保存與之鏈結的 Model 模組
   DS::Event _event;  // 內部使用之事件，what 記錄著 evTimer
 }; // end class TimerCounter

 class Timer : public ControllerItem  // 時間之事件產生器
 {
  public:
   static const int TIME_UP=1;
   static void catch_alarm(int sig);
   static unsigned long int alarm(unsigned long int msec);
   Timer();
   //virtual unsigned is()  {  return TimerCls;  }
   virtual int pool();
   void apply( Model *app, unsigned int msec );
       // 此函式供 Model 申請 Timer 事件之用
       // app 為申請之 Model ， sec 為呼叫之間隔,單位為秒
   void remove( Model *app )  // 撤消原先申請的 Model
   {
   }
  private:
   std::vector<TimerCounter *> _applier;
   static bool timer_on;

 };
} // end namespace DS





#endif
