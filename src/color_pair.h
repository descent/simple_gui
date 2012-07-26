/*
 * $Revision: 1.2 $
 * $Author: descent $
 * $Date: 2002/07/17 02:46:46 $
 * $Id: color_pair.h,v 1.2 2002/07/17 02:46:46 descent Exp $
 * 程式功能：根據 curses 的特性,提供 color pair number 讓 screen class 使用顏色的功能, screen class 在 constructor 會執行 initscr() 初始化 curses, 希望這個 class 可以用在所有的 curses library,這個 class 在 terminal 有支援顏色才能使用,class 封裝在 DS 的 namespcae,目前沒有處理 color pair number 0,基本上不應該用 color pair number 0
 *
 */
#ifndef COLOR_PAIR_H
#define COLOR_PAIR_H

#include <curses.h>
#include <string>
#include <vector>
#include <utility> // need by pair class

// 用 gcc 3 來 compile 就需要用 namespace
//using std::string;


namespace DS
{
 typedef unsigned long COLOR_PAIR_TYPE;
 // 提供 ColorPair class 的 exception handling
 class ColorPairException
 {
  public:
   ColorPairException(const std::string &msg){_msg=msg;}
   const std::string &msg(){return _msg;}
  private:
   std::string _msg;
 };

 class ColorPair
 {
  public:
   ColorPair();
   // 給前景背景色,傳回一個 color pair number,若已經存在該前景背景色則傳回該 color pair number,若無則產生新的 color pair number 並加入 _color_pairs
   static COLOR_PAIR_TYPE get_color_pair(short f,short b); 
   static std::pair<short,short> get_colors(COLOR_PAIR_TYPE num); // 給定一個 color pair number 傳回相關的前景背景色,若無此 color pair number 則丟出一個 exception ColorPairException
  private:
   static bool init_flag; // 因為 ColorPair 只要初始化一次就可以了。所以用這個 flag 來決定是否已經初始化了。
   static void init_color();
   static std::vector<COLOR_PAIR_TYPE> _color_pairs; // 用來紀錄已使用的 color pair number
   static int _max_color; // 最大的 color pair number

 };

}

#endif
