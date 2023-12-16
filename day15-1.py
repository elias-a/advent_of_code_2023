

with open("input15.txt", "rt") as f:
    steps = f.readlines()[0].strip("\n").split(",")

    result_sum = 0
    for step in steps:
        value = 0

        for c in step:
            value += ord(c)
            value *= 17
            value = value % 256

        result_sum += value

    print(result_sum)
