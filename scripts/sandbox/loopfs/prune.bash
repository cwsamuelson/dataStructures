#!/usr/bin/env bash

FSFILE=${1:-fs-file}
MOUNTDIR=${2:-fs-mount}

./umount.bash $MOUNTDIR

rm $FSFILE
