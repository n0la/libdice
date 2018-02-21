#!/bin/sh

set -e
set -x

cd "$(dirname "$0")"

PATH=$PATH:/usr/local/bin

aclocal $AC_SEARCH_OPTS
autoconf
autoheader
automake --copy --add-missing
