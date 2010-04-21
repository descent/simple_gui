#include "color_pair.h"
#include <algorithm>
//#include <iostream>

std::vector<DS::COLOR_PAIR_TYPE> DS::ColorPair::_color_pairs;
int DS::ColorPair::_max_color;
bool DS::ColorPair::init_flag=false;

void DS::ColorPair::init_color()
{
 if (init_flag==true)
  return;
 if (has_colors())
 {
  init_flag=true;
  start_color(); // 初始化顏色
  _max_color=COLOR_PAIRS-1; // _max_color 為最大的 color pair number
  // 加入 1,2,3 等 color pair number ,0 為黑底白字
  init_pair(1,COLOR_BLACK,COLOR_WHITE);
  init_pair(2,COLOR_WHITE,COLOR_BLUE);
  init_pair(3,COLOR_BLUE,COLOR_WHITE);
  _color_pairs.push_back(1);
  _color_pairs.push_back(2);
  _color_pairs.push_back(3);
 }
 else
 {
  throw DS::ColorPairException("The terminal does not support color");
 }

}
   
DS::ColorPair::ColorPair() // 初始化 curses 的 color
{
 init_color(); 
}

// 注意 COLOR_PAIR_TYPE 要寫成 DS::COLOR_PAIR_TYPE，沒想到導入 namespace DS 之後變得很麻煩
// 這是 static member function
DS::COLOR_PAIR_TYPE DS::ColorPair::get_color_pair(short f,short b) // 給前景背景色,傳回一個 color pair number，已經存在該前景背景色則傳回該 color pair number,若無則產生新的 color pair number 並加入 _color_pairs
{
 short foreground,background;
 std::vector<DS::COLOR_PAIR_TYPE> :: iterator it;
 
 DS::COLOR_PAIR_TYPE cur_col_pair=0;
 for (it=_color_pairs.begin() ; it!=_color_pairs.end() ; it++)
 {
  cur_col_pair=*it;
  pair_content(cur_col_pair,&foreground,&background); // find foreground
  if (foreground==f && background==b)
   return cur_col_pair;
 }
 // 目前的沒有 f b 組合的 color pair number
 //cur_col_pair++;
 cur_col_pair=_color_pairs.size()+1;
 if (cur_col_pair > _max_color)
  throw ColorPairException("Color pair number max"); // 所有的 color pair number 已被用完
 init_pair(cur_col_pair,f,b);
 _color_pairs.push_back(cur_col_pair);
 return cur_col_pair;
}

std::pair<short,short> DS::ColorPair::get_colors(DS::COLOR_PAIR_TYPE num) // 給定一個 color pair number 傳回相關的前景背景色,若無此 color pair number 則丟出一個 exception ColorPairException
{
 if (std::find(_color_pairs.begin(),_color_pairs.end(),num)==_color_pairs.end())
  throw ColorPairException("The color pair number does not exist"); 
 short foreground,background;
 pair_content(num,&foreground,&background); // find foreground
 //std::cout << foreground << " " << background << std::endl;
 std::pair<short,short> colors(foreground,background);
 return colors;

}

