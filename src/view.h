/*
 * $Revision: 1.2 $
 * $Author: descent $
 * $Date: 2002/07/17 02:49:08 $
 * $Id: view.h,v 1.2 2002/07/17 02:49:08 descent Exp $
 * 程式功能：這是桌面視窗最基本類別，具有移動、放大、縮小的功能。
 */
#ifndef VIEW_H
#define VIEW_H

//#ifdef DEBUG // write debug message to a file
#include <fstream>
#include <sstream>

//#endif

#include "box.h"
#include "port.h"
#include "event.h"
#include "model.h"

namespace DS
{
 class Model;
 class Event;
 //enum ViewStatus {NORMAL=0,MAX=1,FOCUS=2,MOVE=4};// can use | combine these status
 const int NORMAL=0,MAX=1,FOCUS=2,MOVE=4;// can use | combine these status
 class View : public DS::Box
 {
  public:
   View(DS::Model *model,int x1,int y1,int x2,int y2,short f,short b,short focus_color=COLOR_RED,short move_color=COLOR_GREEN,const std::string &title="");

   // event function
   virtual int from_controller(DS::Event &event);
   virtual int key_event(DS::Event event);

   virtual void show();

   void move(int dx,int dy);
   void grow(int dx,int dy);
   void focus()
   {
    if ( (_view_status&=DS::FOCUS)!=DS::FOCUS)
    {
     _view_status |= DS::FOCUS;
     _tmp_focus=_color_pair_num;
     _color_pair_num=_focus_color_pair_num;
    }
    static std::ofstream logfile("log1.log");
    logfile << "_tmp_focus : " << _tmp_focus << std::endl;
    logfile << "_focus_color_pair_num : " << _focus_color_pair_num << std::endl;
    logfile << "_color_pair_num : " << _color_pair_num << std::endl;
    //logfile.close();
   }
   void unfocus()
   {
    if ( (_view_status&=DS::FOCUS)==DS::FOCUS)
    {
     _view_status &= (~DS::FOCUS);
     _color_pair_num=_tmp_focus;
    }
    std::ofstream logfile("log.log");
    logfile << "_color_pair_num : " << _color_pair_num << std::endl;
    logfile.close();
   }

   void on_move()
   {
    //if ( (_view_status&=DS::MOVE)!=DS::MOVE)
    if ( _move_flag != DS::MOVE)
    {
     _move_flag=DS::MOVE;
     set_frame_kind(DS::SL);
     _tmp_move=_color_pair_num;
     _color_pair_num=_move_color_pair_num;
    }
   }
   void off_move()
   {
    //if ( (_view_status&=DS::MOVE)==DS::MOVE)
    if ( _move_flag == DS::MOVE)
    {
     _move_flag=DS::NORMAL;
     set_frame_kind(DS::DL);
     _color_pair_num=_tmp_move;
    }
/*
    #ifdef DEBUG
     void log_info(const std::stringstream &str); // write some debug information to a file
     std::stringstream format;
     format << "in off_move() _color_pair_num : " << _color_pair_num << std::endl;
     log_info(format);
    #endif
*/
   }
   void add_line(const DS::PortString &str){_port.add_line(str);}
   void del_all_str(){_port.del_all_str();}
   DS::Model * get_model(){ return _model; }


  protected:
   DS::Model *_model;
   //ViewStatus _view_status;
   int _min_width,_min_height; // when grow the smallest width and height
   int _view_status;
   int _move_flag; 
   COLOR_PAIR_TYPE _focus_color_pair_num,_tmp_focus;
   COLOR_PAIR_TYPE _move_color_pair_num,_tmp_move;
   DS::Port _port;

 };
#ifdef DEBUG
 inline void log_info(const std::stringstream &str) // write some debug information to a file
 {
  std::ofstream logfile("log.log");
  logfile << str;

 }
#endif



} // end namespace DS


#endif
