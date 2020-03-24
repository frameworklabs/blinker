#!/bin/sh

set -e

# CONFIGURATION

# Edit this if needed
BLECH_INCLUDE_PATH=$(dirname `which blechc`)/../../../../../include

# BUILD
[ -d build ] || mkdir build

pushd build
blechc -sp ../src ../src/blinker.blc
popd

pushd src
cc -I .  -I ../build -I $BLECH_INCLUDE_PATH main.c blinker_env.c -lcurses -o ../build/blinker
popd

# RUN
build/blinker
