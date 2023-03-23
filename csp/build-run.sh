#!/bin/bash

cd ../build && cmake .. && make && cd ../csp
./csp
