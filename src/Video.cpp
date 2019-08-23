#include "Video.hpp"

//the current position in the video
std::size_t g_video_pos {0};

//the offset of the rendering if youre canvas is bigger than the terminal dimensions
std::size_t g_offset_x {0}, g_offset_y {0};

//the video is just a range of frames
std::vector<Frame> g_video;

//if anything is changed then redraw the current frame else dont change the drawing
bool g_changed {false};

void GotoFrame(std::size_t t_pos) noexcept
{ 
  std::size_t video_max_range {g_video.size()-1};

  g_video_pos = (t_pos > video_max_range) ?
    video_max_range :
    t_pos ;

  g_changed = true;
}

void NextFrame(std::size_t t_amount) noexcept
{
  g_video_pos += t_amount;

  if(g_video_pos >= g_video.size())
    g_video_pos = 0;

  g_changed = true;
}

void PreviousFrame(std::size_t t_amount) noexcept
{
  std::size_t video_max_range {g_video.size()-1};

  g_video_pos -= t_amount;

  if(g_video_pos > video_max_range)
    g_video_pos = video_max_range;
  
  g_changed = true;
}

//Frame& GetFrame()

void SetVideoLength(std::size_t t_length)
{
  static constexpr short min_amount {1};
  auto max_amount {g_video.max_size()};
  
  if(t_length < min_amount) t_length = min_amount;
  if(t_length > max_amount) t_length = max_amount;
  
  g_video.resize(t_length);
}

std::size_t GetVideoLength() noexcept
{
  return g_video.size();
}

std::size_t GetMaxVideoLength() noexcept
{
  return g_video.max_size();
}

void Setwh(std::size_t t_w, std::size_t t_h)
{
  std::for_each(begin(g_video), end(g_video),
		[&](Frame& t_frame)
		{
		  t_frame.Setwh(t_w, t_h);
		});
}

void SetCurrentFramePoint(char t_character, int t_color_pair)
{
  auto[x, y] = GetCurxy();
  
  g_video[g_video_pos].SetPoint(x, y, t_character, t_color_pair);

  g_changed = true;
}

void DrawCurrentFrame(int t_screen_w, int t_screen_h)
{
  if(g_changed)
    g_video[g_video_pos].DrawFrame(t_screen_w, t_screen_h, g_offset_x, g_offset_y);
}

