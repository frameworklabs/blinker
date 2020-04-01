#!/bin/sh

set -e

# CONFIGURATION

# Edit this if needed
# BLECH_INCLUDE_PATH=$(dirname `which blechc`)/../../../../../include

# BUILD
[ -d build ] || mkdir build

cd build
blechc -sp ../src ../src/blinker_lever_test.blc
cd ..

cd src
cc -I .  -I ../build main_test.c blinker_env.c -lcurses -o ../build/blinker_lever_test
cd ..

# RUN
build/blinker_lever_test
