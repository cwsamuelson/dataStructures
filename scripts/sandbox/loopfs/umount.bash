#!/usr/bin/env bash

MOUNTDIR=${1:-fs-mount}

if [[ -z "$(mount | awk '{ print $3 }' | grep $MOUNTDIR)" ]]; then
  echo Nothing mounted to $MOUNTDIR!
  exit 1
fi

sudo umount $MOUNTDIR

rmdir $MOUNTDIR
