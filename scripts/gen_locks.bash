#! /usr/bin/env bash

ROOT=${DEVBOX_PROJECT_ROOT:-"."}

for filename in $ROOT/profiles/*; do
    s="${filename##*/}"
    s="${s%.*}"
    echo $ROOT/lockfiles/conan-$s.lock
    conan lock create -pr:a $filename --lockfile-out $ROOT/lockfiles/$s.lock $ROOT/conanfile.py
done

