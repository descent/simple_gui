/*
 * $Revision$
 * $Author$
 * $Date$
 * $Id$
 * 程式功能：鍵盤事件產生器
 */
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "event.h"
#include "controller_item.h"

#include <curses.h>

namespace DS
{
 class Keyboard : public ControllerItem
 {
  public:
   Keyboard( ){}
   void getKeyEvent( DS::Event *event );  // 內部函式 ,取鍵盤字元
   int pool();
   ~Keyboard(){}
 } ;

} // end namespace DS


#endif
