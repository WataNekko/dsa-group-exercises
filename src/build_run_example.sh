#!/usr/bin/env bash

cd $(dirname $(realpath $0))

g++ *.cpp -o benchmark -Wall && (
py ./plot/plot.py -w ../benchmark_result.csv -O ./plot/plot_options.json &
./benchmark ../benchmark_result.csv
)