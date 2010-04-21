
#include "controller.h"
#include "event.h"

// 以下為公用物件的定義
DS::Desktop *desktop; // 桌面物件
//DoubleList* msgQueue; // 事件存放佇列
//DoubleList* contrlQueue; // 事件產生器佇列
std::vector<DS::ControllerItem *> controller_queue;
std::queue<DS::Event *> event_queue;

//Timer* timer; // 時間事件產生器
//Idler* idler; // 系統空閒事件產生器
DS::Keyboard *keyboard; // 鍵盤事件產生器
DS::Timer *timer; // 鍵盤事件產生器

DS::Controller::Controller()
{
 desktop = new DS::Desktop(COLOR_WHITE,COLOR_BLUE,0,0,COLS,LINES);
  // Controller 的構件者負責產生所有公用物件及各事件產生器
   //msgQueue = new DoubleList();
   //contrlQueue = new DoubleList();
   //idler = new Idler();
   keyboard = new Keyboard();
   timer = new Timer();
   // 事件產生器誕生後，一個一個加入事件產生器佇列中
   //contrlQueue->add( keyboard );
   //contrlQueue->add( timer );
   //contrlQueue->add( idler );
   controller_queue.push_back( keyboard );
   controller_queue.push_back( timer );
   //contrlQueue.push_back( idler );
   // menubar 的顏色由 Color 類別的公用物件 menubarColor 來決定。它存放在 userdef.cpp 。
   // 這是一個可供使用者修改的檔案，可在程式 link 時，一起 link 起來。
   //menubar = new Menubar( menubarColor.textColor, menubarColor.bkGroundColor,
   //menubarColor.revTxtColor,menubarColor.revBkGdColor,menubarColor.hotkeyColor );
   // statusLine 的顏色同樣由 userdef.cpp 中的公用物件 statusLineClr 決定
   //statusLine = new StatusLine(  statusLineClr.textColor, statusLineClr.bkGroundColor,statusLineClr.hotkeyColor );

}

int DS::Controller::run()
{
 curs_set(0); // hide cursor
  //_setcursortype( _NOCURSOR ); // 將游標隱藏

 // 實際所有程式中唯一主動的部分 ---- 事件輪詢迴圈
 while(true)
 {
  pool();
  //for (int i=0 ; i < event_queue.size() ; i++)
  {
   //DS::Event* event = event_queue[i];
   if (!event_queue.empty())
   {

    DS::Event* event = event_queue.front();
    event_queue.pop();
    desktop->from_controller( *event );
    if( event->what() == DS::evExit )
     if( desktop->close() )
      goto end_loop;
   }
  }
 } // end while(true)
 end_loop:
 return 1;
}


DS::Controller::~Controller()
{
 delete desktop;
  //delete msgQueue;  // 在串列中的物件由串列自行殺去
  //delete contrlQueue;
  //delete menubar;
  //delete statusLine;
}
