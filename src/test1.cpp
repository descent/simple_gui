#include "controller.h"
#include "model.h"
#include <time.h>

class MyApp :public DS::Model     // 主應用程式模組
{
 public:
  MyApp();
  // 由於我們只測試 Controller 所以我們只重覆宣告這兩個函式
  int key_event( DS::Event &event );
};

MyApp::MyApp()
{
 desktop->link( this );  // 將此模組與桌面鏈結
 //timer->apply( this ,1 );  // 嘗試申請 Timer and Idler 兩個 控制器
 //idler->apply( this );
}

int MyApp::key_event( DS::Event &event )
{
 //if( event.keyDown.keyCode == kbAltX )  //若使用者按下 Alt-X ,則程式離開
 if( event.keydown() == 'q' )  //若使用者按下 Alt-X ,則程式離開
  event.set_event(DS::evExit);
 else
 {
  mvprintw(10,20,"%c",event.keydown());
  refresh();
 }
 return 1;
}

int main( )
{
 try
 {
  initscr();
  DS::Controller drive;  // 標準程式寫法 ,還算不錯吧 !!
  new MyApp;       // 但還 View 及 Model 要努力 ,加油 !! (-:
  desktop->show();
  //signal(SIGALRM,catch_alarm);
  drive.run();
  endwin();
 } // end try
 catch(...)
 {
  
  endwin();
 }
}
