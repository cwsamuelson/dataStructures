#!/usr/bin/env bash

# Derived from YSAP progress bar tutorial
# https://github.com/bahamas10/ysap/tree/main/code/2025-08-21-progress-bar
# https://github.com/bahamas10/ysap/tree/main/code/2025-09-03-progress-bar-2

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

init-term() {
  # auto deinit on shutdown
  trap deinit-term exit
  # re-init on resize
  trap init-term winch

  # ensure we have space for the scrollbar
  printf '\n'
  # save the cursor location
  printf '\e7'
  # set the scrollable region
  printf '\e[%d;%dr' 0 "$((LINES - 1))"
  # restore the cursor location
  printf '\e8'
  # move cursor up
  printf '\e[1A'
}

deinit-term() {
  # save the cursor location
  printf '\e7'
  # reset the scrollable region
  printf '\e[%d;%dr' 0 "$LINES"
  # move cursor to the bottom line
  printf '\e[%d;%dH' "$LINES" 0
  # clear the line
  printf '\e[0K'
  # reset the cursor location
  printf '\e8'
}
