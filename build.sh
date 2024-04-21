#!/bin/bash

# Make build dir
mkdir -p bin

# Build and clean
(cd ./src; make; make clean)

# Copy to bin
mv ./src/keypad ./bin


