#!/bin/bash

set -e

EXENAME="dupe_find"
CFLAGS="-Wall -ansi -std=c99"
# CFLAGS+=" -DUSE_GETLINE"
OPTCFLAGS="${CFLAGS} -O2"
DBGCFLAGS="${CFLAGS} -ggdb3 -DDEBUG"

rm -f *.exe *.dbg

gcc ${OPTCFLAGS} main.c xxhash.c process_xxh.c xxfile.c -lqlibc -o ${EXENAME}.exe
gcc ${DBGCFLAGS} main.c xxhash.c process_xxh.c xxfile.c -lqlibc -o ${EXENAME}.dbg

SLDIR=${SLDIR:-/usr/lib64}
if [ ${SLDIR}/libqlibc.a ]; then
  gcc ${OPTCFLAGS} -static main.c xxhash.c process_xxh.c xxfile.c ${SLDIR}/libqlibc.a -o ${EXENAME}.static.exe
fi

strip *.exe
