#!/usr/bin/env bash

FSFILE=${1:-fs-file}
FSTYPE=${2:-ext4}

if [[ ! -f "$FSFILE" ]]; then
  echo No suche file: $FSFILE
  exit 1
fi

mkfs -t $FSTYPE $FSFILE
