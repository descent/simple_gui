/*
 *
 * $Revision$
 * $Author$
 * $Id$
 * $Date$
 * 程式功能：此 class 為 event class 用來作事件的傳遞
 */



#ifndef EVENT_H
#define EVENT_H

//#include "view.h"

namespace DS
{
 class View;

 // event name
 const  int   evNothing   = 0 ;
 const  int   evKeyDown   = 1 ;
 const  int   evFunction  = 2 ;
 const  int   evExit      = 3 ;
 const  int   evMessage   = 4 ;
 const  int   evCommand   = 5 ;
 const  int   evHelp      = 6 ;
 const  int   evTimer     = 7 ;
 const  int   evIdler     = 8 ;

 class Event
 {
  public:
   Event(DS::View *s=0,DS::View *r=0):_sender(s),_receiver(r)
   {
   }
   void clear_event(){_what=evNothing;}
   void set_event(int event){_what=event;}
   void set_keydown(int key){_keydown=key;}
   int what(){return _what;} // return what kind of event
   int keydown(){return _keydown;}
   DS::View *receiver(){return _receiver;}
   DS::View *sender(){return _sender;}

  private:
   DS::View *_receiver,
            *_sender;
   int _what;
   int _keydown; // record a key when event is evKeyDown

 };


} // end namespace DS

#endif
