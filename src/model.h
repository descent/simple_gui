/*
 *
 * $Revision$
 * $Author$
 * $Id$
 * $Date$
 * 程式功能：Model class 用來讓其他的 class 繼承完成該程式 model
 */
#ifndef MODEL_H
#define MODEL_H

#include "event.h"
#include "view.h"

namespace DS
{
 //class LView;
 //class ContlItem;
 class DS::View;
 class Model
 {
  public:
   Model( ){}
   //virtual unsigned is()  {  return ModelCls;  }
   virtual void init_menu( ){}
   virtual void init_statusLine(){}
   virtual void from_menu( DS::Event& event ){}
   virtual int from_view( DS::LView* view, DS::Event& event )
   {
    // -Y傳入的"ぁ颽O鍵盤"ぁ鞳A則傳給 keyEvent(...) 處理
    if( event.what() == evKeyDown )
     return key_event( event );
    else
     return 0;
   }

   virtual int key_event( DS::Event &event ){return 0;}

   virtual int from_control( DS::Event &event )  { return 1; }
   virtual bool close( DS::View* view ){return true;}
   virtual ~Model(){}
 } ;

} // end namespace DS



#endif
