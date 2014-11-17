#!/bin/bash
emcc -O3 -s EXPORTED_FUNCTIONS="['_paint']" test.cpp
