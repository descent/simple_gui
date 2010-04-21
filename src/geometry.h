#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace DS
{

 class Point
 {
  public:
   Point(int x=0,int y=0){_x=x;_y=y;}
   int x(){return _x;}
   int y(){return _y;}
   void set_x(int x){_x=x;}
   void set_y(int y){_y=y;}


  private:
   int _x,_y;

 };

 class Rect
 {
  public:
   Rect(int x1=0,int y1=0,int x2=0,int y2=0):_tl(x1,y1),_br(x2,y2){}
   Rect(const Point &tl,const Point &br):_tl(tl),_br(br){}
   void set_tl(Point p){_tl=p;}
   void set_br(Point p){_br=p;}
   Point tl(){return _tl;}
   Point br(){return _br;}
  private:
   Point _tl,_br;
 };
} // end namespace DS

#endif
