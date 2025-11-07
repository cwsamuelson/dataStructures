#!/usr/bin/env bash

# +++ 0

Main0() {
  string=${1:-Hello, World!}
  regex=${2:-"\w\*"}

  if [[ "$string" =~ $regex ]]; then
    echo Match!
  else
    echo No match.
  fi
}

# --- 0

# +++ 1

Main1() {
  while read -e -r -p "Enter search text: " input && [[ -z $input ]]; do
    echo "Empty search input is not valid"
  done

  if [[ -z $input ]]; then
    echo "<EOF>"
    return 1
  fi

  while read -e -r -p "Enter regex: " regex && [[ -z $regex ]]; do
    echo "Empty regex is not valid"
  done

  if [[ -z $input ]]; then
    echo "<EOF>"
    return 1
  fi

  #do-search "$(PATH= ulimit -f 0; eval "echo $input")" "$regex"
  do-search "$(ulimit -f 0; eval "echo $input")" "$regex"
}

do-search() {
  string=$1
  regex=$2

  if [[ "$string" =~ "$regex" ]]; then
    echo Match!
  else
    echo No match.
  fi
}

# --- 1

Main() {
  Main1 $@
  return $?
}

set -o pipefail
set -o errexit
set -o nounset
set -o noclobber

Main $@
result=$?

# Reset terminal cursor position
echo -ne "\r"

unset Main
unset Main0
unset Main1
exit $result
