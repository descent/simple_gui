/*
 *
 * $Revision: 1.3 $
 * $Author: descent $
 * $Date: 2002/07/23 09:34:01 $
 * $Id: desktop.h,v 1.3 2002/07/23 09:34:01 descent Exp $
 * 程式功能：這是用來管理所有 view 的 class
*/

#ifndef DESKTOP_H
#define DESKTOP_H

#include <curses.h>

#include "view.h"
#include "event.h"

#include <vector>
#include <algorithm>
#include <fstream>

namespace DS
{

 class Desktop : public DS::View
 {
  public:
   void link(DS::Model *model){_model=model;}
   bool close()
   {
    return true;
   }
   int from_controller(DS::Event &event)   
   {
    int ret; // 處理 event 的傳回結果， ret 為 0 表示該 event 處理函式
	     // 沒有處理該 event，若傳回 1 表示有處理該 event

    if (view_num() == 0) // desktop 沒有 view，將 event 傳給和 desktop 相連的 model
    //if (_cur_focus==-1) // desktop 沒有 view，將 event 傳給和 desktop 相連的 model
     return _model->from_view(this,event);

    if (event.receiver() == 0) // 沒有指定 event receiver 
    {
     // 將 event 傳給目前 focus 的 view
     if ( ret=_view_list[cur_focus()]->from_controller(event) )
     {
      return ret;
     }
     else // event 沒有被處理
      return _model->from_view(this,event);
    }
    if (event.receiver() == this) // event receiver 是桌面自己
     return _model->from_view(this,event);
    else // 找出這個 event 是要給那一個 view 的
    {
     std::vector<DS::View *> :: iterator it;
    
     it=std::find(_view_list.begin(),_view_list.end(),event.receiver());

     if (it != _view_list.end())
     {
      event.receiver()->from_controller(event);
     }

    }

   }

   Desktop(short f,short b,int x1,int y1,int x2,int y2):View(0,x1,y1,x2,y2,f,b)
   {
    _previous_top=_top=_cur_focus=-1;
    /*
    std::ofstream log_f("log.f");
    log_f << _top << std::endl;
    */
   }

   void grow(int dx,int dy,int pos)
   {
    if (pos < _view_list.size())
    {
     _view_list[pos]->grow(dx,dy);
    }
   }

   void previous_view() // focus to previous view
   {
    if (view_num() > 0)
     focus((cur_focus() - 1 + view_num()) % view_num());
   }

   void next_view() // focus to next view
   {
    if (view_num() > 0)
     focus((cur_focus() + 1 ) % view_num());
   }
   void move(int dx,int dy,int pos) // move pos view, if pos=0 move _view_list[0] view
   {
    if (pos < _view_list.size())
    {
     _view_list[pos]->on_move();
     _view_list[pos]->move(dx,dy);
    }
   }
   void off_move(int pos)
   {
    if (pos < _view_list.size())
     _view_list[pos]->off_move();
   }
   int cur_focus(){return _cur_focus;}
   int cur_top(){return _top;}


   void show()
   {
    //View::show();
    paint_desktop();
    // no view in desktop
    if (_view_list.size()==0)
    {
     refresh();
      return;
    }

    for (int i=0 ; i < _view_list.size() ; i++)
    {
     //if (i==_view_list.size()-1)
     std::ofstream view_file("view_order");
     view_file << "_top : " << _top << std::endl;
     view_file << "_previous_top : " << _previous_top << std::endl;
     view_file << "_cur_focus : " << _cur_focus << std::endl;
     view_file << "_view_list.size() : " << _view_list.size() << std::endl;

     if (i==_cur_focus)
      _view_list[i]->focus();
     //if (i!=_top && i!=_previous_top)
      _view_list[i]->show();
    }
    //_view_list[i-1].focus();
    //if (_previous_top >=0 && _previous_top < _view_list.size())
     //_view_list[_previous_top].show();
    //if (_top >=0 && _top < _view_list.size())
     //_view_list[_top].show();
    refresh();
   }

   void focus(int pos)
   {
    if ( 0 <= pos && pos < _view_list.size())
    {
     if ( 0 <= _cur_focus && _cur_focus < _view_list.size() )
      _view_list[_cur_focus]->unfocus();
     _cur_focus=pos;
    }
   }


   void push_back_view(View *view)
   {
    _view_list.push_back(view);
    focus(_view_list.size()-1);
   }
   int view_num(){ return _view_list.size() ; }

   void remove_view(View *view)
   {
    std::vector<DS::View *> :: iterator it;
    
    it=std::find(_view_list.begin(),_view_list.end(),view);

    if (it != _view_list.end())
    {
     _view_list.erase(it);
     previous_view();
    }

   }
   void top(int pos)
   {
    if ( 0 <= pos && pos < _view_list.size())
    {
     //_previous_top=_top;
     //_top=pos;
     if (pos == _cur_focus)
      _cur_focus=_view_list.size()-1;
     _view_list.push_back(_view_list[pos]);
     _view_list.erase(_view_list.begin()+pos);
    }
   }
   View * get_view(int pos)
   {
    if ( 0 <= pos && pos < view_num() )
     return _view_list[pos];
    // if pos is valid , nothing to do
    else
     return 0;

   }
   View * get_top_view()
   {
    return _view_list[view_num()-1];// return top view
   }

  protected:

   inline void paint_desktop();
   int _cur_focus; // need static ??
   //int _previous_focus;
   int _top; // need static ??
   int _previous_top; // need static ??


   std::vector<DS::View *> _view_list;

 };

 void DS::Desktop::paint_desktop()
 {
  /*
  draw_rect();
  */
  unsigned char bg_char=176;
  //bg_char='o';
  for (int x=_rect.tl().x() ; x < _rect.br().x() ; x++) // draw x
   for (int y=_rect.tl().y() ; y < _rect.br().y() ; y++) // draw y
   {
    //mvaddch(y,x,ACS_BOARD | COLOR_PAIR(1));
    mvaddch(y,x,'O' | A_ALTCHARSET | A_BOLD | COLOR_PAIR(LView::_color_pair_num));
    mvaddch(y,x,bg_char | A_ALTCHARSET | A_BOLD | COLOR_PAIR(_color_pair_num));
   }
  //std::ofstream log_file("log.log");
  //log_file << _color_pair_num << std::endl;
 }

 inline void draw_background()
 {
 /*
  unsigned char bg_char=176;
  for (int x=_rect.tl().x() ; x < _rect.br().x() ; x++) // draw x
   for (int y=_rect.tl().y() ; y < _rect.br().y() ; y++) // draw y
   {
    //mvaddch(y,x,ACS_BOARD | COLOR_PAIR(1));
    mvaddch(y,x,'O' | A_ALTCHARSET | A_BOLD | COLOR_PAIR(0));
    mvaddch(y,x,bg_char | A_ALTCHARSET | A_BOLD | COLOR_PAIR(1));
   }
 */
 }

} // end namespace DS

#endif
