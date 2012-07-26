/*
 * $Revision: 1.2 $
 * $Author: descent $
 * $Date: 2002/07/17 02:49:08 $
 * $Id: port.h,v 1.2 2002/07/17 02:49:08 descent Exp $
 * 程式功能： Port 為與其相關聯 view 的內容
*/
#ifndef PORT_H
#define PORT_H
#include <string>
#include <vector>
#include <curses.h>
#include "geometry.h"

namespace DS
{
/*
 class ChType
 {
  public:
   operator chtype*(){return &_ch;}
  private:
   chtype _ch;


 };
 typedef std::basic_string<ChType> ch_string;  // ch_string 為 chtype 構成的字串
 */

 // 這是在 port 裡顯示的字元，有顏色，屬性等。
 class PortCh
 {
  public:
   PortCh(int ch=' ',int color_pair=0,int attr=0):_ch(ch),_color_pair(color_pair),_attribute(attr)
   {
   }
   int ch(){return _ch;}
   int color_pair(){return _color_pair;}
   int attribute(){return _attribute;}
  private:
   int _ch;
   int _color_pair;
   int _attribute;
 };

 typedef std::vector<PortCh> PortString;

 // 這個 function 方便建立 PortString，要自己手工建立也可以。
 // 由 port_string 這個 reference 傳回所建立的 PortString
 // make_port_string function 會把 str 加上傳入的 color pair and attribute
 // 所以這個字串便會有這個 color pair and attribute
 inline void make_port_string(const std::string &str,PortString &port_string,int color_pair=0,int attr=0)
 {
  port_string.clear();
  for (int i=0 ; i < str.length() ; i++)
   port_string.push_back(PortCh(str[i],color_pair,attr) );
 }

 class Port
 {
  public:
   Port(){_line=0,_column=0;}
   void draw(const DS::Rect &rect,int line=0,int column=0);
   void draw(int x1,int y1,int x2,int y2,int line=0,int column=0);

   int get_str_num(){return _strings.size();}

   //void add_line(const std::string &str){_strings.push_back(str);}
   void add_line(const DS::PortString &str){_port_strings.push_back(str);}
   void del_all_str(){_port_strings.clear();} // del this port all ch_string

  private:

   //std::vector<ch_string> _strings;
   std::vector<std::string> _strings;
   std::vector<PortString> _port_strings;
   int _line; // 紀錄 line 的偏移值 
   int _column; // 紀錄 column 的偏移值

 };


}
#endif
