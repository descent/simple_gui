/*
 * $Revision: 1.2 $
 * $Author: descent $
 * $Date: 2002/07/17 02:49:08 $
 * $Id: box.h,v 1.2 2002/07/17 02:49:08 descent Exp $
 * 程式功能：畫出外框、抬頭字串
*/
#ifndef BOX_H
#define BOX_H

#include "shadow_view.h"

#include <string>

namespace DS
{
 enum FrameKind {SL=0,DL}; // SL is single line , DL is double line
 class Box : public DS::ShadowView
 {
  public:
   Box(int x1,int y1,int x2,int y2,short f,short b,FrameKind frame_kind=DL,const std::string &title=""):ShadowView(x1,y1,x2,y2,f,b)
   {
    _frame_kind=frame_kind;
    _frame_flag=true;
   }
   void set_frame_kind(FrameKind frame_kind){_frame_kind=frame_kind;}
   void set_frame_flag(bool flag){_frame_flag=flag;}
   void set_title(const std::string &title){_title=" "+title+" ";}
   inline void show();


  protected:
   FrameKind _frame_kind; // 紀錄外框的種類是單線還是雙線
   bool _frame_flag; //紀錄要不要畫出外框的旗標，frame_flag=true 表示要畫出外框
   //bool _title_flag; //紀錄要不要畫出外框的旗標，frame_flag=true 表示要畫出外框
   std::string _title; //抬頭字串

   void draw_frame();
   void draw_title();

   // 水平、垂直與四個角
   static unsigned char _tl[]; // top left
   static unsigned char _tr[]; // top right
   static unsigned char _bl[]; // bottom left
   static unsigned char _br[]; // bottom right
   static unsigned char _hl[]; // 水平直線
   static unsigned char _vl[]; // 垂直直線
 };

 inline void Box::show()
 {
  if (_frame_flag==true)
   draw_frame();
  draw_title(); // fraw_title() 要在 draw_frame() 之後，否則抬頭字串會被外框覆蓋

  ShadowView::show();

 }
} // end namespace DS


#endif
