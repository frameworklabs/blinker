# blinker
A simple demo for the Blech programming language.

## Overview

[Blech](http://blech-lang.org) is an exciting new programming language for the realtime domain with the potential to substantially boost productivity and quality of safety- and realtime-critical applications.

Blech builds on the **synchronous model of computation** (MoC) where time progresses in logical steps and all computations happen logically simultaneously and instantaneously at these steps.
The advantage is that the compiler can check for causal dependencies in the program and generate a lock-free and statically scheduled translation.   

This demo **simulates the blinker of a car**. When shifting the blinker lever up or down the right or left blinker lamp will start blinking. When the wheel is turned some degrees in the opposite direction, the blinker lever will go back to the center position and the blinker lights will stop. Toggling the warning lights on or off will result in the left and right blinkers as well as a red warning indicator to start and stop blinking at the same time.

The demo shows how simple and clean problems like these can be implemented with the Blech programming language.

## How to build

With the Blech compiler installed ([see instructions](https://www.blech-lang.org/docs/getting-started/blechc/)) call `make` to build and run the demo.
