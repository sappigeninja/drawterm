#include "Frame.hpp"

//FRAME

Frame::Frame()
{
  m_matrix.resize(1, std::vector<Character>(1, Character{' ', 0}));
}

bool Frame::CheckPos(std::size_t t_x, std::size_t t_y)
{
  return (t_x < m_matrix.front().size()) && (t_y < m_matrix.size());
}

void Frame::SetPoint(const std::size_t t_x, const std::size_t t_y, Character&& t_color) noexcept
{
  if(CheckPos(t_x, t_y))
    m_matrix[t_y][t_x] = std::forward<Character>(t_color);
}

void Frame::SetPoint(const std::size_t t_x, const std::size_t t_y, const char t_character, const int t_color_pair) noexcept
{
  SetPoint(t_x, t_y, Character{t_character, t_color_pair});
}

void Frame::Setwh(std::size_t t_w, std::size_t t_h) noexcept
{
  static constexpr std::size_t min_amount {1};
  const std::size_t max_amount_w {m_matrix.at(0).max_size()},
                    max_amount_h {m_matrix.max_size()};
		    
  //size should be atleast 1x1
  if(t_h < min_amount) t_h = min_amount;
  if(t_w < min_amount) t_w = min_amount;
		    
  if(t_h > max_amount_h) t_h = max_amount_h-1;
  if(t_w > max_amount_w) t_w = max_amount_w-1;
    
  m_matrix.resize(t_h);
  std::for_each(m_matrix.begin(), m_matrix.end(),
		[t_width = t_w](auto& t_row){t_row.resize(t_width);});
    
}

//TODO make this so it never throws an out of range exception
auto Frame::Getwh() const ->std::tuple<std::size_t, std::size_t> 
{
  return {m_matrix.front().size(), m_matrix.size()};
}

std::vector<Character>& Frame::operator[](unsigned t_index)
{
    return m_matrix[t_index];
}

void Frame::DrawLine(const std::vector<Character>& t_line, std::size_t t_screen_w, std::size_t t_offset_x) const
{
  for(std::size_t x_pos {0}; x_pos < t_line.size(); x_pos++)
    {
      	Movex(x_pos);
	const auto& point = t_line[t_offset_x + x_pos];
	
      try{

	attribute_on(COLOR_PAIR(point.second));
	
	if(point.first != 0)
	  addch(point.first);
	else
	  addch(' ');
	
	attribute_off(COLOR_PAIR(point.second));
	
      }catch(InitExcept& catched){
	catched += " Frame::DrawLine()";
	throw catched;
      }
    }
}

void Frame::DrawFrame(std::size_t t_screen_w, std::size_t t_screen_h, std::size_t t_offset_x, std::size_t t_offset_y) const
{
  for(std::size_t y_pos {0}; y_pos < m_matrix.size(); y_pos++)
    {
      try{
	Movey(y_pos);
      
	DrawLine(m_matrix[t_offset_y + y_pos], t_screen_w, t_offset_x);
	Movey(y_pos); //change this for later allow to specify the DrawFrame window* param TODO

   }catch(InitExcept& catched){
	catched += " Frame::DrawFrame()";
	throw catched;
      }
    }
}
