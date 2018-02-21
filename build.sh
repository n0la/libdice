#!/bin/sh

set -e
set -x

cd "$(dirname "$0")"

./autogen.sh
./configure "$@"
make
