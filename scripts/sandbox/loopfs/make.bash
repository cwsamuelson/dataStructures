#!/usr/bin/env bash

set -e

FSFILE=${1:-fs-file}
FSSIZE=${2:-100M}
FSTYPE=${3:-ext4}
MOUNTDIR=${4:-fs-mount}

if [[ ! -f $FSFILE ]]; then
  ./create.bash $FSFILE $FSSIZE

  ./mkfs.bash $FSFILE $FSTYPE
fi

./mount.bash $FSFILE $MOUNTDIR
