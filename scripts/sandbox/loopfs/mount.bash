#!/usr/bin/env bash

FSFILE=${1:-fs-file}
MOUNTDIR=${2:-fs-mount}
FSTYPE=${3:-ext4}

# if available loop doesn't exist, create one?
# mknod

#! @TODO partitions

if [[ `losetup -j $FSFILE -O NAME -n | wc -l` != 0 ]]; then
  echo $FSFILE is already mounted!
  exit 1
fi

if [[ ! -f $FSFILE ]]; then
  echo No such file: $FSFILE
  exit 1
fi

mkdir -p $MOUNTDIR

sudo mount -t $FSTYPE -o loop $FSFILE $MOUNTDIR

sudo chown $(id -nu):$(id -ng) $MOUNTDIR
#chmod 777 $MOUNTDIR
