#include <chrono>
#include <format>
#include <iostream>
#include <print>
#include <thread>
#include <unistd.h>

// Control Sequence docs:
// https://invisible-island.net/xterm/ctlseqs/ctlseqs.html

constexpr static size_t lines = 31;
constexpr static size_t columns = 99;

void color() {
}

// Color Codes (ANSI Escape Sequences)
constexpr static size_t fg_gray       = 30;
constexpr static size_t fg_red        = 31;
constexpr static size_t fg_green      = 32;
constexpr static size_t fg_yellow     = 33;
constexpr static size_t fg_blue       = 34;
constexpr static size_t fg_purple     = 35;
constexpr static size_t fg_turquoise  = 36;
constexpr static size_t fg_light_gray = 37;

template <typename CharT>
std::basic_ostream<CharT>& bright_grey(std::basic_ostream<CharT>& stream) {
  return stream << "\033[90m";
}

template <typename CharT>
std::basic_ostream<CharT>& bright_red(std::basic_ostream<CharT>& stream) {
  return stream << "\033[91m";
}

template <typename CharT>
std::basic_ostream<CharT>& bright_green(std::basic_ostream<CharT>& stream) {
  return stream << "\033[92m";
}

template <typename CharT>
std::basic_ostream<CharT>& bright_yellow(std::basic_ostream<CharT>& stream) {
  return stream << "\033[93m";
}

template <typename CharT>
std::basic_ostream<CharT>& bright_blue(std::basic_ostream<CharT>& stream) {
  return stream << "\033[94m";
}

template <typename CharT>
std::basic_ostream<CharT>& bright_magenta(std::basic_ostream<CharT>& stream) {
  return stream << "\033[95m";
}

template <typename CharT>
std::basic_ostream<CharT>& bright_cyan(std::basic_ostream<CharT>& stream) {
  return stream << "\033[96m";
}

template <typename CharT>
std::basic_ostream<CharT>& bright_white(std::basic_ostream<CharT>& stream) {
  return stream << "\033[97m";
}

constexpr static size_t bg_dark_gray  = 40;
constexpr static size_t bg_red        = 41;
constexpr static size_t bg_green      = 42;
constexpr static size_t bg_yellow     = 43;
constexpr static size_t bg_blue       = 44;
constexpr static size_t bg_purple     = 45;
constexpr static size_t bg_turquoise  = 46;
constexpr static size_t bg_light_gray = 47;

constexpr static size_t regular_value = 0;
constexpr static size_t bold_value = 1;

template <typename CharT>
std::basic_ostream<CharT>& bold(std::basic_ostream<CharT>& stream) {
  return stream << "\033[1m";
}

template <typename CharT>
std::basic_ostream<CharT>& dark(std::basic_ostream<CharT>& stream) {
  return stream << "\033[2m";
}

template <typename CharT>
std::basic_ostream<CharT>& italic(std::basic_ostream<CharT>& stream) {
  return stream << "\033[3m";
}

template <typename CharT>
std::basic_ostream<CharT>& underline(std::basic_ostream<CharT>& stream) {
  return stream << "\033[4m";
}

template <typename CharT>
std::basic_ostream<CharT>& blink(std::basic_ostream<CharT>& stream) {
  return stream << "\033[5m";
}

template <typename CharT>
std::basic_ostream<CharT>& reverse(std::basic_ostream<CharT>& stream) {
  return stream << "\033[7m";
}

template <typename CharT>
std::basic_ostream<CharT>& concealed(std::basic_ostream<CharT>& stream) {
    return stream << "\033[8m";
}

template <typename CharT>
std::basic_ostream<CharT>& crossed(std::basic_ostream<CharT>& stream) {
  return stream << "\033[9m";
}

/*
```bash
progress-bar() {
  local current=$1
  local total=$2
  local prefix=${3:-""}

  local fill_char='#'
  local empty_char=' '

  local percent_complete=$((current * 100 / total))

  local suffix="$buffer $current/$total ($percent_complete%)"

  local width=${COLUMNS:-80}
  width=$((width - ${#suffix} - 2))
  local fill_count=$((percent_complete * width / 100))

  local i
  local buffer='['
  for ((i = 0; i < fill_count; i++)); do
    buffer+=$fill_char
  done
  for ((i = fill_count; i < width; i++)); do
    buffer+=$empty_char
  done
  buffer+=']'
  buffer+=$suffix

  printf '\e7' # save the cursor location
  printf '\e[%d;%dH' $LINES 0 # move cursor to the bottom line
  printf '\e[0K' # clear the line
  printf '%s' "$buffer" # print the progress bar
  printf '\e8' # restore the cursor location
}
```
*/

void save_cursor() {
  std::print("\e7");
}

void restore_cursor() {
  std::print("\e8");
}

void move_up(const size_t count) {
  std::print("\e[{}A", count);
}

void move_down(const size_t count) {
  std::print("\e[{}B", count);
}

void move_forward(const size_t count) {
  std::print("\e[{}C", count);
}

void move_backward(const size_t count) {
  std::print("\e[{}D", count);
}

void move_cursor(const auto x, const auto y) {
  std::print("\e[{};{}H", y, x);
}

template<typename ...Args>
auto at_position(const auto x, const auto y, const std::string& fmt, Args&& ...args) {
  return std::format("\e7\e[{};{}H{}\e8", y, x, std::vformat(fmt, std::make_format_args(args...)));
}

template<typename ...Args>
constexpr
auto color(const size_t color, const std::string& fmt, Args&& ...args) {
  return std::format("\e[0;{}m{}\e[0m", color, std::vformat(fmt, std::make_format_args(args...)));
  // bold:
  // return std::format("\e[1;{}m{}\e[0m", color, std::vformat(fmt, std::make_format_args(args...)));
}

void rgb(const uint8_t r, const uint8_t g, const uint8_t b) {
  std::print("\e[38;2;{};{};{}m", r, g, b);
}

void push_palette() {
  std::print("\e[#P");
}

void pop_palette() {
  std::print("\e[#Q");
}

void clear_line() {
  // \e{}K erases the line, and has 3 modes
  // 0 -> right
  // 1 -> left
  // 2 -> all
  std::print("\e[2K");
}

void set_scroll_region(const auto width, const auto height) {
  // # set the scrollable region
  // printf '\e[%d;%dr' 0 "$((LINES - 1))"
  std::print("\e[{};{}r", width, height);
}

// void fg_dark_grey() {
//   std::print("\e[0;30m");
// }
// 
// void fg_bold_dark_grey() {
//   std::print("\e[1;30m");
// }
// 
// void fg_red() {
//   std::print("\e[0;31m");
// }

// template<typename ...Args>
// constexpr
// auto fg_red(const std::string& fmt, Args&& ...args) {
//   return std::format("\e[0;31m{}\e[0m", std::vformat(fmt, std::make_format_args(args...)));
// }

// void fg_bold_red() {
//   std::print("\e[1;31m");
// }
// 
// void fg_green() {
//   std::print("\e[0;32m");
// }
// 
// void fg_bold_green() {
//   std::print("\e[1;32m");
// }
// 
// void fg_yellow() {
//   std::print("\e[0;33m");
// }
// 
// void fg_bold_yellow() {
//   std::print("\e[1;33m");
// }
// 
// void fg_blue() {
//   std::print("\e[0;34m");
// }
// 
// void fg_bold_blue() {
//   std::print("\e[1;34m");
// }
// 
// void fg_purple() {
//   std::print("\e[0;35m");
// }
// 
// void fg_bold_purple() {
//   std::print("\e[1;35m");
// }
// 
// void fg_turquoise() {
//   std::print("\e[0;36m");
// }
// 
// void fg_bold_turquoise() {
//   std::print("\e[1;36m");
// }
// 
// void fg_gray() {
//   std::print("\e[0;37m");
// }
// 
// void fg_bold_gray() {
//   std::print("\e[1;37m");
// }

void reset_color() {
  std::print("\e[0m");
}

void progress_bar(const float normalized) {
  const size_t progress_ticks = normalized * columns;
  const char tick = '#';
  const char empty = ' ';
  std::print("{}", at_position(0, 31, "[{}{}]", std::string(progress_ticks, tick), std::string(columns - progress_ticks, empty)));
}

template<std::unsigned_integral UInteger>
void progress_bar(const UInteger progress, const UInteger total) {
  progress_bar(static_cast<float>(progress) / total);
}

struct TermInit {
  TermInit() {
  }

  ~TermInit() {
    reset_color();
    set_scroll_region(0, 31);
  }
};

int main() {
  TermInit _;

  std::print("ABCD{}IJKL", at_position(0, 31, "{}", color(fg_red, "EF{}GH", 42)));

  set_scroll_region(0, 30);
  for (size_t i = 0; i < 40; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    std::print("@\n");
  }

  std::print("{}", at_position(0, 29, "MNO"));

  set_scroll_region(0, 31);
  std::println("PQRSTUV");
}
