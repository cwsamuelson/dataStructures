#!/usr/bin/env bash

# https://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
# http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html

# TODO emit bmp file
#
# - Header - 14 bytes
#   - Signature - 2 bytes
#   - file size - 4 bytes
#   - reserved - 4 bytes
#   - data offset - 4 bytes
# - info header - 40 bytes
# ...

u32le() {
  local n=$1
  local out

  # break number into bytes
  # 0x12345678
  # 0x12
  # 0x34
  # 0x56
  # 0x78
  local octet1=$(( (n >> 24) & 0xFF))
  local octet2=$(( (n >> 16) & 0xFF))
  local octet3=$(( (n >>  8) & 0xFF))
  local octet4=$(( (n >>  0) & 0xFF))

  printf -v out '\\x%02x\\x%02x\\x%02x\\x%02x' \
    "$octet4" \
    "$octet3" \
    "$octet2" \
    "$octet1"
  printf '%b' "$out"
}

u16le() {
  local n=$1
  local out

  # break number into bytes
  # 0x1234
  # 0x12
  # 0x34
  local octet1=$(( (n >>  8) & 0xFF))
  local octet2=$(( (n >>  0) & 0xFF))

  printf -v out '\\x%02x\\x%02x' \
    "$octet2" \
    "$octet1"
  printf '%b' "$out"
}

rgb() {
  local r=$1
  local g=$1
  local b=$1
  local out

  printf -v out '\\x%02x\\x%02x\\x%02x' \
    "$b" \
    "$g" \
    "$r"
  printf '%b' "$out"
}

bmp-header() {
  local width="$1"
  local height="$2"
  local bits_per_pixel=24
  local bytes_per_pixel=$(( bits_per_pixel / 8 ))
  local row_size=$((width * bytes_per_pixel))

  local padding=0
  # must be aligned to 4 byte boundary
  while ((row_size % 4 != 0)); do
    ((padding++))
    ((row_size++))
  done

  local pixel_data_size=$((row_size * height))
  local pixel_data_offset=$((14 + 40))
  local file_size=$((pixel_data_size + pixel_data_offset))

  # echo "width $width" >&2
  # echo "height $height" >&2
  # echo "bpp $bits_per_pixel" >&2
  # echo "Bpp $bytes_per_pixel" >&2
  # echo "row size $row_size" >&2
  # echo "padding $padding" >&2
  # echo "px data size $pixel_data_size" >&2
  # echo "px data offset $pixel_data_offset" >&2
  # echo "file size $file_size" >&2

  # Header
  ## Signature
  printf 'BM'
  ## File size
  u32le "$file_size"
  # echo "file size $file_size" >&2
  ## reserved
  u32le 0
  ## Data offset
  u32le "$pixel_data_offset"
  # echo "data offset $pixel_data_offset" >&2

  # Info Header
  ## Size
  u32le 40
  ## Width
  u32le "$width"
  # echo "width $width" >&2
  ## Height
  u32le "$height"
  # echo "height $height" >&2
  ## Planes
  u16le 1
  ## BitCount
  u16le "$bits_per_pixel"
  # echo "bit count $bits_per_pixel" >&2
  ## Compression
  u32le 0
  ## ImageSize
  u32le 0
  ## XPixelsPerM
  u32le 0
  ## YPixelsPerM
  u32le 0
  ## ColorsUsed (palette)
  u32le 0
  ## ColorsImportant
  u32le 0

  REPLY="$padding"
}

bmp-pad() {
  local padding=$1

  local i
  for ((i = 0; i < padding; i++)); do
    printf '\0'
  done
}
