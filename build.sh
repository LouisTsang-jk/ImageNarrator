#!/bin/bash
rm -rf output
cd src/cpp/build
cmake ..
make
cd ../../../
src/cpp/build/image_narrator
python3 src/python/analyze.py