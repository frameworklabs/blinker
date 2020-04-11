#!/bin/sh

set -e

# BUILD
[ -d build ] || mkdir build

blechc -od build -sp src src/test/control/blinker_lever_test.blc

cc -I src -I dep -I build src/test/shell/main_test.c src/env/blinker_env.c build/blech/test/control/blinker_lever_test.c -lcurses -o build/blinker_lever_test

# RUN
build/blinker_lever_test
