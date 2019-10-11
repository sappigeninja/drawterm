#include "Cursor.hpp"

int g_max_x {getmaxx(stdscr)};
int g_max_y {getmaxy(stdscr)-2};

int g_cursor_x {getcurx(stdscr)};
int g_cursor_y {getcury(stdscr)};

short g_pair_pos {1};
char  g_character {'0'};

void Update() noexcept
{
    g_max_x = getmaxx(stdscr);
    g_max_y = getmaxy(stdscr)-2;

    g_cursor_x = getcurx(stdscr);
    g_cursor_y = getcury(stdscr);
}

int GetCurx() noexcept
{
    return g_cursor_x;
}

int GetCury() noexcept
{
    return g_cursor_y;
}

auto GetCurxy() noexcept ->std::tuple<int, int>
{
    return {g_cursor_x, g_cursor_y};
}

int GetMaxx() noexcept
{
    return g_max_x;
}

int GetMaxy() noexcept
{
    return g_max_y;
}

auto GetMaxxy() noexcept ->std::tuple<int, int>
{
    return {g_max_x, g_max_y};
}

int GetPrompty() noexcept
{
    return g_max_y+1;
}

int Boundsx(int t_cursor_x) noexcept
{
    if(t_cursor_x < 0) t_cursor_x = 0;
    else if(t_cursor_x >= g_max_x) t_cursor_x = g_max_x-1;

    return t_cursor_x;
}

int Boundsy(int t_cursor_y) noexcept
{
    if(t_cursor_y < 0) t_cursor_y = 0;
    else if(t_cursor_y >= g_max_y) t_cursor_y = g_max_y-1;

    return t_cursor_y;
}

bool SetPair_Pos(short t_pair_pos) noexcept
{
  if(t_pair_pos > int{COLOR_PAIRS - 1} || t_pair_pos < 0) return false;
  
  g_pair_pos = t_pair_pos;

  return true;
}

short GetPair_Pos() noexcept
{
  return g_pair_pos;
}

void SetCharacter(char t_character) noexcept
{
  g_character = t_character;
}

char GetCharacter() noexcept
{
  return g_character;
}

void Movex(WINDOW* t_win, int t_cursor_x) noexcept
{
    g_cursor_x = Boundsx(t_cursor_x);
    wmove(t_win, g_cursor_y, g_cursor_x);
}

void Movey(WINDOW* t_win, int t_cursor_y) noexcept
{
    g_cursor_y = Boundsy(t_cursor_y);
    wmove(t_win, g_cursor_y, g_cursor_x);
}

void Move(WINDOW* t_win, int t_cursor_x, int t_cursor_y) noexcept
{
    g_cursor_x = Boundsx(t_cursor_x);
    g_cursor_y = Boundsy(t_cursor_y);

    wmove(t_win, g_cursor_y, g_cursor_x);
}

void MoveLeft(WINDOW* t_win, int t_amount) noexcept
{
    Movex(t_win, g_cursor_x-t_amount);
}

void MoveRight(WINDOW* t_win, int t_amount) noexcept
{
    Movex(t_win, g_cursor_x+t_amount);
}

void MoveUp(WINDOW* t_win, int t_amount) noexcept
{
    Movey(t_win, g_cursor_y-t_amount);
}

void MoveDown(WINDOW* t_win, int t_amount) noexcept
{
    Movey(t_win, g_cursor_y+t_amount);
}

void MovePrompt(WINDOW* t_win, int t_cursor_x) noexcept
//goes to the prompt area what is normally out of bounds
{
  g_cursor_x = t_cursor_x;
  g_cursor_y = g_max_y+1;
  
  wmove(t_win, g_cursor_y, g_cursor_x);
}

void MoveBrush(WINDOW* t_win, int t_cursor_x) noexcept
//goes from right to left
{
  ++t_cursor_x;
  g_cursor_x = g_max_x - t_cursor_x;
  g_cursor_y = g_max_y+1;
  
  wmove(t_win, g_cursor_y, g_cursor_x);
}
  
void MovePromptLine(WINDOW* t_win)
//goes one place up the prompt are to draw the line normally out of bounds
{
    g_cursor_x = 0;
    g_cursor_y = g_max_y;

    wmove(t_win, g_max_y, g_cursor_x);
}

