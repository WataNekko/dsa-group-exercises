#!/usr/bin/python3
import argparse
import csv
import os


# cli arguments parsing
parser = argparse.ArgumentParser(
    description="Plot the data generated from the sorting algorithms benchmark program",
    allow_abbrev=False,
)

parser.add_argument(
    "filename", metavar="PATH", help="the path to the file to read from"
)
group = parser.add_mutually_exclusive_group()
group.add_argument(
    "-w",
    "--watch",
    action="store_true",
    help="watch the file and update the plot when changes occur",
)
group.add_argument(
    "-o",
    "--output",
    metavar="FILE",
    help="output the plot to FILE instead of showing in a window",
)
parser.add_argument("-s", "--style", help="set the style of the figure")
parser.add_argument(
    "-O",
    "--plot-options",
    metavar="JSON",
    help="set the plotting options with an array of options in json format "
    "(JSON can be a json string or a json file name)",
)

args = parser.parse_args()

# plot data
try:
    import matplotlib.pyplot as plt
    from matplotlib.animation import FuncAnimation
except ModuleNotFoundError:
    raise SystemExit(
        "This script requires matplotlib to run.\n"
        "Run the 'pip install matplotlib' command to install it."
    )

try:
    with open(args.filename) as file:
        # set figure style
        if args.style:
            try:
                plt.style.use(args.style)
            except OSError as ex:
                raise SystemExit(
                    f"Error: {ex}\n\nstyle.available=\n\t{plt.style.available}"
                )

        # parse plotting options
        if args.plot_options:
            import json
            from json.decoder import JSONDecodeError

            plot_options: list[dict]
            try:
                plot_options = json.loads(args.plot_options)
            except JSONDecodeError:
                try:
                    with open(args.plot_options) as f:
                        plot_options = json.load(f)
                except (FileNotFoundError, OSError, JSONDecodeError):
                    parser.error(
                        "argument -O/--plot-options: invalid JSON or file name"
                    )

            if (
                not isinstance(plot_options, list)
                or not plot_options
                or not all(isinstance(option, dict) for option in plot_options)
            ):
                parser.error("argument -O/--plot-options: invalid options array")

        def update_plot():
            """Main function to draw the plot"""
            file.seek(0)  # re-read the file from the start

            # get data
            try:
                reader = csv.DictReader(file, quoting=csv.QUOTE_NONNUMERIC)
                rows = tuple(reader)
            except ValueError:
                raise SystemExit(f"Error: Cannot read the format of '{args.filename}'")

            # convert tuple of dicts to dict of tuples
            data = {key: tuple(row[key] for row in rows) for key in reader.fieldnames}

            # update the plot with new data
            if args.plot_options:

                def next_options():
                    try:
                        return next(next_options.iter)
                    except StopIteration:
                        next_options.iter = iter(plot_options)  # roll over
                        return next(next_options.iter)

                next_options.iter = iter(plot_options)
            else:
                no_opt = {}
                next_options = lambda: no_opt

            plt.cla()

            xlabel = reader.fieldnames[0]
            for label in data:
                if label != xlabel:
                    plt.plot(
                        data[xlabel],
                        data[label],
                        label=label,
                        **next_options(),
                    )

            plt.xlabel(xlabel)
            plt.ylabel("Time (ms)")
            plt.title("Sorting algorithms comparison")
            plt.grid(True)
            plt.legend(loc="upper left")
            plt.tight_layout()

        if not args.watch:
            update_plot()

            if args.output:
                plt.savefig(args.output)
                print(f"Saved plot to '{args.output}'")
            else:
                plt.show()
        else:
            # watch file for changes

            def poll_change(on_change):
                """Poll the input file's modified time to check for changes."""
                mtime = os.stat(args.filename).st_mtime
                if mtime != poll_change.cached_mtime:
                    poll_change.cached_mtime = mtime
                    on_change()

            # init mtime to None so that on_change is always called on the first poll
            poll_change.cached_mtime = None

            def animate(_):
                poll_change(update_plot)

            ani = FuncAnimation(plt.gcf(), animate, interval=10)
            print(f"[Watching '{args.filename}' for changes...]")
            plt.show()

except FileNotFoundError as ex:
    raise SystemExit(f"Error: Cannot find the file: '{ex.filename}'")
