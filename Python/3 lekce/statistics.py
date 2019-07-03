import collections
import math

Statistics = collections.namedtuple("Statistics",
                                    "mean mode median std_dev")

def main():
    numbers = []
    frequencies = collections.defaultdict(int)
    filename = "C:\\Users\\Aleš\\Documents\\GitHub\\SchoolUP\\Python\\data\\statistics.dat"
    read_data(filename, numbers, frequencies)
    if numbers:
        statistics = calculate_statistics(numbers, frequencies)
        print_results(len(numbers), statistics)
    else:
        print("nebyla nalezena zadna cisla")

def read_data(filename, numbers, frequencies):
    for lino, line in enumerate(open(filename, encoding="ascii"), start=1):
        for x in line.split():
            try:
                number = float(x)
                numbers.append(number)
                frequencies[number] += 1
            except ValueError as err:
                print("{filename}:{lino}: skipping {x}: {err}".format(**locals()))

def calculate_statistics(numbers, frequencies):
    mean = sum(numbers) / len(numbers)
    mode = calculate_mode(frequencies, 3)
    median = calculate_median(numbers)
    std_dev = calculate_std_dev(numbers, mean)
    return Statistics(mean, mode, median, std_dev)

def calculate_mode(frequencies, maximum_modes):
    highest_freq = max(frequencies.values())
    mode = [number for number, frequency in frequencies.items() if frequency == highest_freq]
    if not (1 <= len(mode) <= maximum_modes):
        mode = None
    else:
        mode.sort()
    return mode

def calculate_median(numbers):
    numbers = sorted(numbers)
    middle = len(numbers) // 2
    median = numbers[middle]
    if len(numbers) % 2 == 0:
        median = (median + numbers[middle - 1]) / 2
    return median

def calculate_std_dev(numbers, mean):
    total = 0
    for number in numbers:
        total += ((number - mean) ** 2)
    variance = total / (len(numbers) - 1)
    return math.sqrt(variance)

def print_results(count, statistics):
    real = "9.2f"

    if statistics.mode is None:
        modeline = ""
    elif len(statistics.mode) == 1:
        modeline = "modus      = {0:{fmt}}\n".format(
                statistics.mode[0], fmt=real)
    else:
        modeline = ("modus      = [" +
                    ", ".join(["{0:.2f}".format(m)
                    for m in statistics.mode]) + "]\n")

    print("""\
počet      = {0:6}
střed      = {mean:{fmt}}
medián     = {median:{fmt}}
{1}\
sm. odch.  = {std_dev:{fmt}}""".format(
    count, modeline, fmt=real, **statistics._asdict()))

main()