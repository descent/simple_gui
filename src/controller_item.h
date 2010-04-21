/*
 */

#ifndef CONTROLLER_ITEM_H
#define CONTROLLER_ITEM_H

namespace DS
{
 class ControllerItem
 {
  public:
   ControllerItem(){}
   virtual int pool()=0;
   virtual ~ControllerItem(){}
  private:
 };


}// namespace DS

#endif
