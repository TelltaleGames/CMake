#!/bin/bash
mkdir -p Build
cd Build
#GEN="Visual Studio 14 2015 Win64"
GEN="Visual Studio 14 2015"
cmake -Wno-dev -G "${GEN}" ..
