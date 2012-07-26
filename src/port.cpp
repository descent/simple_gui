#include "port.h"

void DS::Port::draw(const DS::Rect &rect,int line,int column)
{

}

void DS::Port::draw(int x1,int y1,int x2,int y2,int line,int column)
{
// int addchnstr(const chtype *chstr, int n)
	/*
 int width,height;
 ( (_strings.size() < (y2-y1)) ? (height=_strings.size()) : (height=(y2-y1)) );
 for (int i=0 ; i < height ; i++)
 {
  (_strings[i].length() < (x2-x1)) ? (width=_strings[i].length()) : (width=(x2-x1));
  for (int j=0 ; j < width ; j++)
   mvaddch(y1+i,x1+j,_strings[i][j]);
 }
 */
 int width,height;
 ( (_port_strings.size() < (y2-y1)) ? (height=_port_strings.size()) : (height=(y2-y1)) );
 for (int i=0 ; i < height ; i++)
 {
  (_port_strings[i].size() < (x2-x1)) ? (width=_port_strings[i].size()) : (width=(x2-x1));
  for (int j=0 ; j < width ; j++)
   //mvaddch(y1+i,x1+j,_port_strings[i][j].ch() );
   mvaddch(y1+i,x1+j,_port_strings[i][j].ch() | COLOR_PAIR(_port_strings[i][j].color_pair() ) | _port_strings[i][j].attribute());
 }
}
