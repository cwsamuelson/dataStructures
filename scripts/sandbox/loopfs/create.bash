#!/usr/bin/env bash

# sparse files to reduce actual file size usage?

FSFILE=${1:-fs-file}
FSSIZE=${2:-100M}

if [[ ! -f "$FSFILE" ]]; then
  echo No such file: $FSFILE
  exit 1
fi

# touch
# dd
#dd -if=/dev/zero -of=$FSFILE -bs=1M
# truncate
truncate -s $FSSIZE $FSFILE
# fallocate
