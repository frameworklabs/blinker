#!/bin/sh

set -e

# BUILD
[ -d build ] || mkdir build

blechc -od build -sp src src/app/control/blinker.blc

cc -I src -I dep -I build src/app/shell/main.c src/env/blinker_env.c build/blech/app/control/blinker.c -lcurses -o build/blinker

# RUN
build/blinker
