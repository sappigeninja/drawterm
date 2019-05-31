#ifndef RGB_H
#define RGB_H

#include <ncurses.h>

#include <vector>

//the colors that reside in there might need its own file for this
class RGB
{
private:
  //defining one color
  short m_r {0},
    m_g {0},
    m_b {0};

public:

  RGB();
  RGB(const RGB& t_rhs);
  
  bool Set_Character(char t_character);
  
  bool Set_R(short t_r);
  bool Set_G(short t_g);
  bool Set_B(short t_b);
  
  bool CheckValues();
  void ResetValues();

  RGB operator=(const RGB& t_rhs);
};

#endif // RGB_H
