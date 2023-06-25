#!/bin/bash
rm -rf output
cd src/cpp/build
cmake ..
make
cd ../../../
src/cpp/build/image_narrator
source image_narrator/bin/activate
python3 src/python/analyze.py