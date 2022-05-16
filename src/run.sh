#!/usr/bin/env bash

cd $(dirname $(realpath $0))

g++ -std=c++17 -Wall -o main main.cpp dsa/*.cpp && ./main
