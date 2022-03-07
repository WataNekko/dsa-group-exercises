# Benchmark and compare Insertion sort, Merge sort and Quicksort

### Benchmarking

The C++ code in [./src](./src/) is the main program for benchmarking.

The built program can be run with no argument (will log the result to the console) or with one argument which is the path to the file to which the result will be output **(in csv format)**.

### Plotting

The Python script [plot.py](./src/plot/plot.py) in [./src/plot](./src/plot/) is used to plot the result (requires [matplotlib](https://matplotlib.org/stable/users/installing/index.html)).

The script can generate the plot statically, can watch the input file for changes and update the plot dynamically and can save the figure to a file. See its usage with the command `python plot.py -h`.

## Usage

The benchmarking program can be built with:

```sh
cd src/
g++ \*.cpp -o benchmark -Wall
```

Then the following command can be used to run and _then_ plot it

```sh
./benchmark ../benchmark_result.csv && python ./plot/plot.py ../benchmark_result.csv -O ./plot/plot_options.json
```

or use the following to run and plot the result simultaneously with the -w/--watch flag (to have sort of an animation (-ish) for the plot. See [plot.py](./src/plot/plot.py)'s usage with `python plot.py -h` for help.)

```sh
python ./plot/plot.py --watch ../benchmark_result.csv -O ./plot/plot_options.json & ./benchmark ../benchmark_result.csv
```

**_Our generated result can be viewed at [benchmark_result.csv](benchmark_result.csv) and [benchmark_result.png](benchmark_result.png)_**
