#!/usr/bin/env python3

import sys
import os
import shutil
from math import log10
from PIL import Image


def print_brief_usage(exit_code):
    print("""
Usage: [python3 SimAnim.py | ./SimAnim.py] [-f framerate] [-t begin:end] [-l length] <input_directory>
    """)
    sys.exit(exit_code)


def create_animation(input_dir, framerate, t_range, length):

    anim_dir = os.path.join(input_dir, "anim")
    tmp_dir = os.path.join(anim_dir, "tmp")
    with open(os.path.join(input_dir, "time.txt"), "r") as file:
        times = [float(x) for x in file.read().split("\n")[:-1]]

    if t_range[0] < 0:
        t_range[0] = times[0]
    if t_range[1] < 0:
        t_range[1] = times[-1]

    image_count = int(length*framerate) + 1
    step = (t_range[1] - t_range[0])/(image_count - 1)
    i = 0
    t = t_range[0]
    image_indices = list()
    for _ in range(image_count):
        while i < len(times) - 1 and abs(times[i+1] - t) <= abs(times[i] - t):
            i += 1
        image_indices.append(i)
        t += step

    digit_count = int(log10(image_count)) + 1
    for i, index in enumerate(image_indices):
        output_path = os.path.join(tmp_dir, "0"*(digit_count - len(str(i))) + str(i) + ".png")
        input_path = os.path.join(input_dir, "frame" + str(index) + ".txt")
        create_image(input_path, output_path)

    command = "ffmpeg -r " + str(framerate)
    command += " -i " + os.path.join(tmp_dir, "%0" + str(digit_count) + "d.png")
    command += " -c:v libx264 -crf 10 -c:a aac -strict -2 " + os.path.join(anim_dir, "anim.mp4")
    os.system(command)


def create_image(input_filename, output_filename):

    with open(input_filename, "r") as file:
        mat = [[float(x) for x in line.split(" ")] for line in file.read().split("\n")[:-1]]

    min_x, max_x = -75, 75
    img = Image.new("RGB", (len(mat[0]), len(mat)))
    for l, line in enumerate(mat):
        for r, x in enumerate(line):
            x = int(max(min((x - min_x)/(max_x - min_x), 1), 0)*255)
            img.putpixel((l, r), (x, x, x))

    img.save(output_filename)


def main(args):

    framerate = 24.0
    t_range = [-1.0, -1.0]
    length = 10.0
    input_dir = str()

    a = 1
    while a < len(args):
        arg = args[a]

        if arg in ["-f"]:
            a += 1
            if a < len(args):
                arg = args[a]
                try:
                    framerate = float(arg)
                except ValueError:
                    print("Unrecognized framerate (must be a number): " + arg + ".")
                    print_brief_usage(1)
        elif arg in ["-t"]:
            a += 1
            if a < len(args):
                arg = args[a]
                try:
                    arg = arg.split(":")
                    assert len(arg) == 2
                    t_range = [float(x) for x in arg]
                except (ValueError, AssertionError):
                    print("Unrecognized time range: " + arg + ".")
                    print_brief_usage(1)
        elif arg in ["-l"]:
            a += 1
            if a < len(args):
                arg = args[a]
                try:
                    length = float(arg)
                except ValueError:
                    print("Unrecognized animation length: " + arg + ".")
                    print_brief_usage(1)
        elif input_dir == str():
            input_dir = arg
        else:
            print("Unrecognized argument: " + arg + ".")
            print_brief_usage(1)
        a += 1

    if input_dir == str():
        print("Missing input and output directories.")
        print_brief_usage(1)

    anim_dir = os.path.join(input_dir, "anim")
    tmp_dir = os.path.join(anim_dir, "tmp")

    if "anim" in os.listdir(input_dir):
        shutil.rmtree(anim_dir)

    os.mkdir(anim_dir)
    os.mkdir(tmp_dir)
    create_animation(input_dir, framerate, t_range, length)


if __name__ == "__main__":
    main(sys.argv)
