#include "shadow_view.h"

void DS::ShadowView::show()
{
 draw_shadow();

 // DS::LView::show() 會呼叫 refresh() 將螢幕重新畫過，所以要在 draw_dhadow()
 // 之後呼叫
 DS::LView::show(); // the function will call fresh() so it must in after
}

void DS::ShadowView::draw_shadow()
{
 for (int i=0 ; i < 2 ; i++)
  for (int x=_rect.tl().x()+3 ; x < _rect.br().x()+3 ; x++) // draw x
  {
   chtype c;
   c=mvwinch(stdscr,_rect.br().y()+i,x);
   mvaddch(_rect.br().y()+i,x,(c & A_CHARTEXT) >= 128 ? c & A_CHARTEXT | A_ALTCHARSET : (c & A_CHARTEXT));
  }

 for (int i=0 ; i < 3 ; i++)
  for (int y=_rect.tl().y()+3 ; y < _rect.br().y() ; y++) // draw y
  {
   chtype c;
   c=mvwinch(stdscr,y,_rect.br().x()+i);
   mvaddch(y,_rect.br().x()+i,(c & A_CHARTEXT) >= 128 ? c & A_CHARTEXT | A_ALTCHARSET  : (c & A_CHARTEXT));
   //mvaddch(y,_rect.br().x()+i,ACS_BOARD | COLOR_PAIR(0));
  }


}
