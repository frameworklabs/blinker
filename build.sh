#!/bin/sh

set -e

# BUILD
[ -d build ] || mkdir build

cd build
blechc -sp ../src ../src/blinker.blc
cd ..

cd src
cc -I .  -I ../build main.c blinker_env.c -lcurses -o ../build/blinker
cd ..

# RUN
build/blinker
