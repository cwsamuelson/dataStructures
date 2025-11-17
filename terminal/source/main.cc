#include <chrono>
#include <iostream>
#include <print>
#include <thread>
#include <unistd.h>

/*
```bash
set-scroll-region() {
  printf '\e[%d;%dr' $1 $2
}

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

  # move cursor up
  printf '\e[1A'

```
*/

void save_cursor() {
  std::print("\e7");
}

void restore_cursor() {
  std::print("\e8");
}

void move_cursor(const auto x, const auto y) {
  std::print("\e[{};{}H", y, x);
}

void clear_line() {
  // clear entire line
  // \e[0K seems to clear the line forward of the cursor
  // \r first resets the cursor to beginning of the line
  // so we reset to front of line, then clear the whole line from the front
  std::print("\r\e[0K");
}

void set_scroll_region(const auto width, const auto height) {
  // # set the scrollable region
  // printf '\e[%d;%dr' 0 "$((LINES - 1))"
  std::print("\e[{};{}r", width, height);
}

constexpr static size_t lines = 31;
constexpr static size_t columns = 99;

int main() {
  std::print("ABCD");
  save_cursor();
  move_cursor(0, 31);
  std::print("EFGH");
  restore_cursor();
  std::print("IJKL");
  set_scroll_region(0, 30);
  for (size_t i = 0; i < 40; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    std::print("@\n");
  }

  save_cursor();
  move_cursor(0, 31);
  std::print("MNO");
  restore_cursor();

  set_scroll_region(0, 31);
  std::println("PQRSTUV");
}
