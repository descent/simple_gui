/*
 * $Revision: 1.2 $
 * $Author: descent $
 * $Date: 2002/07/17 02:49:08 $
 * $Id: shadow_view.h,v 1.2 2002/07/17 02:49:08 descent Exp $
 * 程式功能：畫出 shadow
 */

#ifndef SHADOW_VIEW_H
#define SHADOW_VIEW_H

#include "lview.h"

namespace DS
{
 class ShadowView : public DS::LView
 {
  public:
   ShadowView(int x1,int y1,int x2,int y2,short f,short b):LView(x1,y1,x2,y2,f,b)
   {

   }
   void show(); // a virtual function
  protected:
   void draw_shadow(); // non virtual function
 


 };


}


#endif
