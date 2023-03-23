#!/bin/bash

cd .. && rm -r ./build/*
cd build && cmake .. && make && cd ../csp
./csp
