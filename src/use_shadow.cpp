/*
 *
 * $Revision: 1.2 $
 * $Author: descent $
 * $Date: 2002/07/17 02:49:08 $
 * $Id: use_shadow.cpp,v 1.2 2002/07/17 02:49:08 descent Exp $
 * 程式功能：畫出 shadow，在一個 text window 的右方及下方畫出 shadow，
 *           使用 curses 來實作
 */

#include <curses.h>

#include "desktop.h"
#include "geometry.h"
/*
#include "shadow_view.h"
#include "box.h"
*/
#include "view.h"


int main()
{
 initscr();
 cbreak();
 noecho();
 curs_set(0);
 keypad(stdscr,true);
 //start_color();
 //init_pair(1,COLOR_WHITE,COLOR_BLUE);
 //init_pair(2,COLOR_BLUE,COLOR_WHITE);



 // 畫出背景桌面

 //DS::View view(10,5,50,20);
/*
 DS::LView lview(10,5,50,20,COLOR_WHITE,COLOR_BLUE);
 lview.show();


 DS::ShadowView shadow_view1(10+5,5+5,50+5,20+5,COLOR_WHITE,COLOR_BLUE);
 shadow_view1.show();

 DS::ShadowView shadow_view(10,5,50,20,COLOR_WHITE,COLOR_BLUE);
 shadow_view.show();
 DS::Box box1(10,5,50,20,COLOR_WHITE,COLOR_BLUE);
 box1.set_title("abcdefghijklmnopqrstuvwxyz--ABCDEFGHIJKLMNOPQRSTUVWXYZ");
 box1.set_title("abc");
 //box1.set_frame_kind(DS::SL);
 box1.set_frame_flag(false);
 box1.show();
*/
 // 背景桌面的大小
 DS::Desktop *desktop=new DS::Desktop(COLOR_WHITE,COLOR_BLUE,0,0,COLS,LINES);
 DS::View view(0,10,5,50,20,COLOR_WHITE,COLOR_BLUE);
 DS::View *view1= new DS::View(0,10+2,5+2,50+2,20+2,COLOR_WHITE,COLOR_BLUE);
 DS::View view2(0,10+5,5,50+5,20,COLOR_WHITE,COLOR_BLUE);
 view.set_title("I am view");
 std::string ch_str="test port this is a very long strings let me test my port and view";
 //DS::ch_string ch_str;
 view.add_line(ch_str);
 ch_str="This is another string let me test second line";
 view.add_line(ch_str);
 view1->set_title("I am view1");
 view2.set_title("I am view2");
 view2.add_line("I am view2 and test view port hope success");
 desktop->push_back_view(*view1);
 //desktop->push_back_view(view1);
 //desktop->push_back_view(view2);
 //desktop.focus(1);
 desktop->show();
 
 //view.focus();
 //view.show();


 int ch;
 enum Status {NORMAL=0,MOVE,GROW,FOCUS};

 Status status=NORMAL;
 int cur_focus=desktop->cur_focus();
 while((ch=getch())!='q')
 {
  switch (ch)
  {
   case 'm' :
   {
    status=MOVE; 
    break;
   }
   case 'g' :
   {
    status=GROW; 
    break;
   }
   
   case KEY_UP :
   {
//    view.focus();
    if (status==MOVE)
    {
     //view.on_move();
     //view.move(0,-1);
     desktop->move(0,-1,cur_focus);
    }
    if (status==GROW)
     desktop->grow(0,-1,cur_focus);
    desktop->show();
    //view.show();
    //refresh();
    break;
   }
   case KEY_DOWN:
   {
    //view.focus();
    //view.on_move();
    if (status==MOVE)
    {
     //view.on_move();
     //view.move(0,1);
     desktop->move(0,1,cur_focus);
    }
    if (status==GROW)
     desktop->grow(0,1,cur_focus);
    desktop->show();
    //view.show();
    //refresh();
    break;
   }
   case KEY_LEFT:
   {
    //view.focus();
    //view.on_move();
    if (status==MOVE)
    {
     //view.on_move();
     //view.move(-1,0);
     desktop->move(-1,0,cur_focus);
    }
    if (status==GROW)
     desktop->grow(-1,0,cur_focus);
    desktop->show();
    //view.show();
    //refresh();
    break;
   }
   case KEY_RIGHT:
   {
    //view.focus();
    //view.on_move();
    if (status==MOVE)
    {
     //view.on_move();
     //view.move(1,0);
     desktop->move(1,0,cur_focus);
    }
    if (status==GROW)
     desktop->grow(1,0,cur_focus);
    desktop->show();
    //view.show();
    //refresh();
    break;
   }
   case 9: // TAB key
   {
    cur_focus=(cur_focus+1)%3;
    desktop->focus(cur_focus);
    desktop->show();
    break;
   }
   case '1':
   {
    desktop->top(0);
    desktop->show();
    break;
   }
   case '2':
   {
    desktop->top(1);
    desktop->show();
    break;
   }
   case '3':
   {
    desktop->top(2);
    desktop->show();
    break;
   }

   //case KEY_ENTER:
   case 10: // 10 is ENTER use gdb to find it
   {
    if (status==MOVE)
    {
     desktop->off_move(cur_focus);
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
    //view.focus();
    status=NORMAL;
    //view.unfocus();
    //if (desktop.cur_top()==cur_focus)
    desktop->top(cur_focus);
    desktop->show();
    //view.show();
    //refresh();
    break;
   }
  } // end case
  

 } // end while()


 endwin();
}

