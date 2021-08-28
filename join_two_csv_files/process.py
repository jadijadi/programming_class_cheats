#!/usr/bin/python

import csv

f2data = {}
with open('f2.csv') as f2:
    f2reader = csv.reader(f2)
    for row in f2reader:
        f2data[row[0]] = [row[1], row[2]]

with open('f1.csv') as f1:
    f1reader = csv.reader(f1)
    for row in f1reader:
        this_name = row[1]
        if this_name in f2data:
            print (','.join(row + f2data[this_name]))
        else:
            print (','.join(row + ['-', '-']))


