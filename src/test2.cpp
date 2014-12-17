/*
 * $Revision$
 * $Author$
 * $Id$
 * $Date$
 * 程式功能：測試 MVC 系統
 */
#include "controller.h"
#include "model.h"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;

  // 這是子程式模組，由主程式模組產生。它負責誕生一個 View ，並藉由申請一個時間
  // 事件來更新這個 View 的內容顯示。
class ShowModel : public DS::Model
{
 public:
  ShowModel( int no );
  virtual int key_event( DS::Event &event );
  virtual int from_control( DS::Event &event );

  ~ShowModel();

  protected:
   //static _count;
   DS::View *_view;  // 記錄所誕生的 View 的指標
   char count[30];  // 存放一列顯示子串
   int i; // 此變數記錄在 View 裏顯示了幾列的字串。
   int _id; // ShowModel 的編號
   static int _total_ShowModel; //可以用來紀錄目前有多少的 ShowModel 
};
int ShowModel :: _total_ShowModel=-1;


ShowModel::ShowModel( int  no ):_id(0)
{
 _id = ++_total_ShowModel;
 static int x=1,y=1;
    sprintf( count,"%d%d%d%d%d%d%d%d",no,no,no,no,no,no,no,no );
     // 誕生一個 View
  //_view =new DS::View( this,x++,y++,32+x,7+y,COLOR_MAGENTA,COLOR_GREEN ,COLOR_WHITE,COLOR_CYAN );
  //_view =new DS::View( this,x++,y++,32+x,7+y,COLOR_MAGENTA,COLOR_GREEN);
  _view =new DS::View( this,x++,y++,32+x,7+y,COLOR_WHITE,COLOR_BLUE);
 std::stringstream format;
 format << "View " << _id;
  _view->set_title(format.str());

    //view->move( random(45),random(17) );   // 不讓 View 互相重疊
    //_view->move(x++,y++);
    desktop->push_back_view( _view );

    //timer->apply( this ,300 );  // 申請一個時間事件作為更新 View 內容之用
    i = 0;
}

ShowModel::~ShowModel()
{
   //timer->remove( this );    // 申請的時間事件要記得取消
 //std::ofstream of("smodel");
 //of << "in ShowModel::~ShowModel() " << std::endl;
 desktop->remove_view( _view);   // 記得這道手續最後才做
}

int ShowModel::key_event( DS::Event &event )
{
 // 若使用者按下了 0 - 9 之間的數字按鍵 ,View 中便會秀出 "You Press a key !!"
 if( event.keydown() >= '0' && event.keydown() <= '9' )
 {    
  int color_pair = DS::ColorPair::get_color_pair(COLOR_CYAN,COLOR_RED);
  DS::PortString port_string;
  DS::make_port_string("test port attribute and color pair",port_string,color_pair);
  _view->del_all_str();
  //_view->add_line(std::string("You press ") + static_cast<char>(event.keydown()) + std::string(" key !!") );
  _view->add_line(port_string);
  desktop->show();    
  return 1;      
 }
 return 0;
}

// 由模組直接申請的控制器 ,有事件發生時並不經由 View ,而直接呼叫申請模組的此函式;
// 設計者可藉由此函式定時更新 View 的畫面 ,達到分時多工的效果
int ShowModel::from_control( DS::Event &event )
{
/*
     // 計數器每數到 16 ，便清除 View 中所有的字串，重新開始。
   if( i >16 )
      {  view->delAllStrs();
         i = 0;  }
   else
     { view->addALine( new Line( count ,(COLORS)i,GREEN  ));
       i++;              }

*/
   return 1;
}


class MyApp :public DS::Model     // 主應用程式模組
{
  public:
   MyApp();
   virtual int key_event( DS::Event &event );
   virtual int from_control( DS::Event &event );
   virtual bool close( DS::View* view );
   ~MyApp();

  protected:
   int cnt;  // 記錄目前 Model 的數目
   bool moveFlag; // 記錄目前是否在 move 狀態
};

   // 程式離開前執行的動作
bool MyApp::close(DS::View *view)
{
  DS::Box end( 19,12,60,14, COLOR_WHITE,COLOR_RED );
  end.show();
  //end.putStr( 4,1, "Press any key to \"Exit\" ....." );
  getch();
  //screen.paintDesktop( WHITE,BLACK );
  return 1;
}
MyApp::MyApp() : cnt(0),moveFlag( FALSE )
{
  desktop->link( this );  // 將此模組與桌面鏈結
  timer->apply( this ,200);  // 嘗試申請 Timer and Idler 兩個控制器
  //idler->apply( this );

 // 此段畫目錄列
}

MyApp::~MyApp()
{
  //timer->remove( this );
  //idler->remove( this );
}




// 桌面中，子 View 沒有處理的鍵盤事件由此繼續處理
int MyApp::key_event( DS::Event &event )
{
 enum Status {NORMAL=0,MOVE,GROW,FOCUS};

 static Status status=NORMAL;
 //int cur_focus=desktop->cur_focus();


 switch( event.keydown())
 {
  // 若使用者按下 q ，則程式離開。
  case 'q' :  
  {
   event.set_event(DS::evExit);
   break;
  }
  case 'm':
  {
   status=MOVE;
   break;
  }
  case 'g' :
  {
   status=GROW;
   break;
  }

  //case KEY_ENTER:
  case 9: // 9 is TAB use gdb to find it
  {
   //desktop->next_view();
   desktop->previous_view();
   desktop->show();
   break;
  }
  case 10: // 10 is ENTER use gdb to find it
  {
   desktop->top(desktop->cur_focus());
   if (status==MOVE)
   {
    desktop->off_move(desktop->cur_focus());
    desktop->show();
    status=NORMAL;
    break;
   }
   if (status==GROW)
   {
    desktop->show();
    status=NORMAL;
    break;
   }
  }
  case KEY_UP :
  {
   if (status==MOVE)
    desktop->move(0,-1,desktop->cur_focus());
   if (status==GROW)
    desktop->grow(0,-1,desktop->cur_focus());
   desktop->show();

   break;
  }
  case KEY_DOWN :
  {
   if (status==MOVE)
    desktop->move(0,1,desktop->cur_focus());
   if (status==GROW)
    desktop->grow(0,1,desktop->cur_focus());
   desktop->show();

   break;
  }
  case KEY_LEFT :
  {
   if (status==MOVE)
    desktop->move(-1,0,desktop->cur_focus());
   if (status==GROW)
    desktop->grow(-1,0,desktop->cur_focus());
   desktop->show();
   break;
  }
  case KEY_RIGHT :
  { // 將 desktop->show 用這樣的寫法才不會每次都要重畫 desktop
    // 只有在 move 和 grow 才會重畫
   if (status==MOVE)
   {
    desktop->move(1,0,desktop->cur_focus());
    desktop->show();
   }
   if (status==GROW)
   {
    desktop->grow(1,0,desktop->cur_focus());
    desktop->show();
   }
   break;
  }

  // 按 F5 會誕生一個子 Model ；而此子 Model 會在構建者函式中
  // new 一個 View ，然後加入桌面。
  // 原本是 F3, 但是和我設定的終端機 hotkey 衝突, 所以改 F5
  case KEY_F(5) :
  {
   new ShowModel( cnt );
   //desktop->focus(desktop->cur_focus());
   ofstream f3_s("f3");
   f3_s << desktop->cur_focus() << std::endl;

   desktop->show(); 
   //cnt++;
   break;
  }

  // close a view
  case KEY_F(6) :
  {
   //desktop->remove_view(); 
   if (desktop->view_num() > 0)
   {
    delete (desktop->get_view(desktop->cur_focus())->get_model());
    desktop->show(); 
   }
   break;
  }

  /*
         // 按 Alt + F3 將殺去與桌面端 View 鏈結的 Model ，而此 Model 在構除者
         // 函式中，再要求桌面殺去此 View 。
       case kbAltF3 : if( desktop->getViewQnty() )
                          delete desktop->getTopView()->getModel() ; // 殺去模組
                      break;
         // 按 Alt + D 是 DOS SHELL 的功能
       case kbAltD  : system( "\command.com" );
                      break;
         // 按 Alt + F5 能使桌面頂端的 View 在最大化和還原之間切換。
       case kbF5    : desktop->maxTop();
                      break;
         // 按 Alt+ (2-9) 分別將 Top-View 底下的 View 移到頂端來。
       case kbAlt2  : desktop->top( 2 );
                      break;
       case kbAlt3  : desktop->top( 3 );
                      break;
       case kbAlt4  : desktop->top( 4 );
                      break;
       case kbAlt5  : desktop->top( 5 );
                      break;
       case kbAlt6  : desktop->top( 6 );
                      break;
       case kbAlt7  : desktop->top( 7 );
                      break;
       case kbAlt8  : desktop->top( 8 );
                      break;
       case kbAlt9  : desktop->top( 9 );
                      break;
         // 開始 move 狀態
       case kbAltM  : desktop->onMoveTop();
                      desktop->lockKeyTop();
                      moveFlag = TRUE;
                      break;
         // 結束 move 狀態
   // 10 is ENTER key 
   case 10 : desktop->offMoveTop();
                      desktop->unlockKeyTop();
                      moveFlag = FALSE;
                      break;
         // 按 Alt + (Up、Down、Left、Right) 為移動或放大縮小 View 的功能。
         // 若按下 Shift ，則為 grow 模式； 若不按，則為 move 模式。
         // grow 為橫向時，一次改變兩個字元；以免在中文系統下方框產生亂碼。
       case kbRight : if( moveFlag )
                        if( keyboard->isShiftPressed() )
                              desktop->growTop( 2, 0);
                        else
                              desktop->moveTop( 1,0 );
                      break;
       case kbLeft  : if( moveFlag )
                         if( keyboard->isShiftPressed() )
                              desktop->growTop( -2, 0);
                         else
                              desktop->moveTop( -1,0 );
                      break;
       case kbUp    : if( moveFlag )
                         if( keyboard->isShiftPressed() )
                              desktop->growTop( 0, -1);
                         else
                              desktop->moveTop( 0,-1 );
                      break;
       case kbDown  : if( moveFlag )
                         if( keyboard->isShiftPressed() )
                              desktop->growTop(0, 1);
                         else
                              desktop->moveTop( 0, 1 );
                      break;
 */
       default      : break;
    }
  return 1;
}

int MyApp::from_control( DS::Event &event )
{   // Timer and Idler 皆由此函式傳事件過來
 static int x=9,counter=0,color=1;  // 這些靜態變數控制座標、顏色、及計數。

 if( event.what() == DS::evTimer )
 {
  // 若是由 timer 傳來 ,在螢幕右上角印出現在時間。
  char buf[30];
  time_t t = time (NULL);
  struct tm *tb = localtime (&t);
        //screen.printf( 70,0,WHITE,CYAN,"%02d:%02d:%02d", tb->tm_hour, tb->tm_min, tb->tm_sec);
  mvwprintw(stdscr,0,70,"%02d:%02d:%02d", tb->tm_hour, tb->tm_min, tb->tm_sec);
  //mvwprintw(stdscr,0,70,"test timer");
  refresh();

  // 我們固定由主程式模組每 1/200 秒更新一次畫面，而不這樣做的目的是為了增進系統的效率。
  //desktop->show();
 }
 else       // Idler 事件產生器產生的事件由此區塊處理
 {    // 在下方印出一長條形 ,並改變顏色 ,並嘗試呼叫 remove() 停止顯示
	 /*
  counter++;
  if( counter >1000 )  // 我們控制此計數器的值，以延遲顯示的速度。
  {     if( x<70 )   x++;   // 印 70 個 char(32) 後，改變顏色。
   else      
   {  
    x=9;
    if( color >14 ) 
    { // 顯示 15 種顏色後，就停止顯示時間和顏色
     //idler->remove( this );
     timer->remove( this ); 
    }
    else   
     color++;    
   }
   //screen.putChar( x,24,' ',GREEN,color );
   counter =0;                           
  } 
  */
 } // end else
}

  // 自設的桌面重畫函式
/*
void myDesktop()
{
   desktop->paintDesktop(  YELLOW,BLUE );
   desktop->printf( 15,10,YELLOW,BLUE,"%s", "**********************************************");
   desktop->printf( 15,11,YELLOW,BLUE,"%s","*              Name : Test2.cpp              *");
   desktop->printf( 15,12,YELLOW,BLUE,"%s","*   for : testing View and Desktop class     *");
   desktop->printf( 15,13,YELLOW,BLUE,"%s","*                by : Nick Gue               *");
   desktop->printf( 15,14,YELLOW,BLUE,"%s","**********************************************");
   desktop->printf( 15,15,YELLOW,BLUE,"%s","          Press Alt-X to Exit .....");
}
*/

int main( )
{
 initscr();
 keypad(stdscr,true);
 DS::Controller drive;  // 標準程式寫法 ,相當不賴吧 !!
 //desktop->setGroundFunc( myDesktop );
 desktop->show();
 new MyApp;
 drive.run();
 endwin();
}
