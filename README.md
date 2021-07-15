# kollang

This is an academic attempt to create an interpreter for a new programming language called "kol".
The end goal is for kol to be similar to python, with possibly a few differences which I haven't
decided the details on yet.

### Current State

Kol is currently a glorified calculator with a limited capacity for variable assignment.

### Usage

Generate a `kol` executable by running `make`.

Run against one of the files in the `tests` directory by running `./kol tests/test1.kol`.

Run interactive mode by running `./kol` with no arguments.

Disable debug mode (excessive logging) by changing `#define DEBUG 1` to `#define DEBUG 0` in `KolMain.h`.
