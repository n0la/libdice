#!/bin/sh

set -e
set -x

if [ $(uname) = "OpenBSD" ]; then
    export AUTOMAKE_VERSION=1.15
    export AUTOCONF_VERSION=2.69
fi

cd "$(dirname "$0")"

PATH=$PATH:/usr/local/bin

aclocal $AC_SEARCH_OPTS
autoconf
autoreconf --install
autoheader
automake --copy --add-missing
