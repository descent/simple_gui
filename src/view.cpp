#include "view.h"
#include <curses.h>

DS::View::View(DS::Model *model,int x1,int y1,int x2,int y2,short f,short b,short focus_color,short move_color,const std::string &title):Box(x1,y1,x2,y2,f,b)
{
 _model=model;
 _min_width=10;
 _min_height=6; 
    
 _focus_color_pair_num=_color_pair.get_color_pair(focus_color,_color_pair.get_colors(_color_pair_num).second);
 _move_color_pair_num=_color_pair.get_color_pair(move_color,_color_pair.get_colors(_color_pair_num).second);
 _view_status=DS::NORMAL;
 _move_flag=NORMAL;
}


void DS::View::move(int dx,int dy)
{
 Point new_tl(_rect.tl().x()+dx,_rect.tl().y()+dy),new_br(_rect.br().x()+dx,_rect.br().y()+dy);

 _rect.set_tl(new_tl);
 _rect.set_br(new_br);
}

void DS::View::grow(int dx,int dy)
{
 int grow_x,grow_y;
 ( (_rect.br().x() + dx - _rect.tl().x() ) > _min_width) ? ( grow_x=_rect.br().x() + dx  ) : (grow_x=_rect.tl().x() + _min_width);
 ( (_rect.br().y() + dy - _rect.tl().y() ) > _min_height ) ? (grow_y=_rect.br().y() + dy ) : (grow_y=_rect.tl().y() + _min_height) ;
 Point new_br(grow_x,grow_y);
 _rect.set_br(new_br);
}

int DS::View::from_controller(DS::Event &event)
{
 int ret;

 if (event.receiver() == 0 || event.receiver() == this)
 {
  if (event.what()==DS::evKeyDown)
   if (ret=key_event(event))
    return ret;
   else
    if (_model!=0)
     return _model->from_view(this,event);
  } 
 }

int DS::View::key_event(DS::Event event)
{
 return 0;
}

void DS::View::show()
{
 //Box::show();
 if (_frame_flag==true)
  draw_frame();
 draw_title();
 draw_shadow();
 draw_rect();
 _port.draw(_rect.tl().x()+1,_rect.tl().y()+1,_rect.br().x()-1,_rect.br().y()-1);
 //refresh();
}
