#!/usr/bin/env bash

FSFILE=${1:-fs-file}
MOUNTDIR=${2:-fs-mount}
FSSIZE=${3}

if [[ -z "$FSSIZE" ]]; then
  echo Amount to resize file system by is required
  exit 1
fi

echo This hasn\'t been implemented yet, sorry
exit 1

./umount.bash $MOUNTDIR

truncate -s $FSSIZE $FSFILE

#resize2fs
