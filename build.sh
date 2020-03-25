#!/bin/sh

set -e

# CONFIGURATION

# Edit this if needed
BLECH_INCLUDE_PATH=$(dirname `which blechc`)/../../../../../include

# BUILD
[ -d build ] || mkdir build

cd build
blechc -sp ../src ../src/blinker.blc
cd ..

cd src
cc -I .  -I ../build -I $BLECH_INCLUDE_PATH main.c blinker_env.c -lcurses -o ../build/blinker
cd ..

# RUN
build/blinker
