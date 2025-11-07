#!/usr/bin/env bash

save-cursor() {
  printf '\e7'
}

restore-cursor() {
  printf '\e8'
}

move-cursor() {
  # move-cursor x y
  printf '\e[%d;%dH' $2 $1
}

clear-line() {
  printf '\e[0K'
}

set-scroll-region() {
  printf '\e[%d;%dr' $1 $2
}
