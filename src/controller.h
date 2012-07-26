/*
 * $Revision$
 * $Author$
 * $Date$
 * $Id$
 * 程式功能：這是 controller class 用來控制整個程式的流程
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "desktop.h"
//#include "idler.h"
#include "keyboard.h"
#include "timer.h"
#include "controller_item.h"

#include <vector>
#include <queue>



// 以下為公用物件
extern DS::Desktop* desktop;  // 桌面公用物件
//extern  DoubleList* msgQueue; // 訊息佇列指標
//extern DoubleList* contrlQueue; // 事件產生器佇列
//extern std::vector<CObject *> contrlQueue;
//extern Timer *timer; // 時間事件產生器之公用物件
//extern Idler *idler; // 空閒事件產生器之公用物件
extern DS::Keyboard *keyboard; // 鍵盤事件產生器之公用物件
extern DS::Timer *timer; // 鍵盤事件產生器
extern std::vector<DS::ControllerItem *> controller_queue;
extern std::queue<DS::Event *> event_queue;


namespace DS
{
 class Controller
 {
  public:
   Controller();
   //virtual unsigned is()  {  return ControllerCls;  }
   virtual int run();
   // 此函式負責開始整個訊息迴圈的動作。換句話說：程式由此開始接受外部的訊
   // 息。若說的更明白一點 ,在 main() 中 ,在 new 完一些必要的個體後 ,就是呼
   // 叫這個程式啟動的。並由此函式呼叫 pool() 及 View 的 fromControler() 函式
   virtual void pool()  // 輪詢各事件產生器的副程式
   {
    std::vector<ControllerItem *> :: iterator it;
    for ( it=controller_queue.begin() ; it !=controller_queue.end() ; it++)
     (*it)->pool() ;
     //dynamic_cast<ControllerItem*>(*it)->pool() ;
   }
   virtual int addController( ControllerItem* controller );
   // 增加事件產生器至事件產生器串列之中
   virtual ~Controller();
  protected:
 } ;

inline int Controller::addController(ControllerItem * controller )
{
  // 此函式只單純的將事件產生器放入事件產生器佇列中而已
   //contrlQueue->add( controller );
 controller_queue.push_back( controller );
   return 1;
}

} // end namespace DS



#endif
