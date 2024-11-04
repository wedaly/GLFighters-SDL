#!/usr/bin/env python

import sys
import re

STATE_INIT = 0
STATE_TEX = 1
STATE_NORM = 2
STATE_VERT = 3
STATE_DONE = 4

target = sys.argv[1]
state = STATE_INIT
data = []

TWO_RE = re.compile(r"\(([0-9.-]+), ([0-9.-]+)\)")
THREE_RE = re.compile(r"\(([0-9.-]+), ([0-9.-]+), ([0-9.-]+)\)")

def append2ToData(line):
    m = TWO_RE.search(line)
    data.extend(m.groups(1))

def append3ToData(line):
    m = THREE_RE.search(line)
    data.extend(m.groups(1))


with open("models.cpp", "r") as f:
    for line in f:
        if state == STATE_INIT:
            if target in line:
                state = STATE_TEX
        elif state == STATE_TEX:
            if "glTexCoord2" in line:
                append2ToData(line)
                state = STATE_NORM
            elif line.startswith("}"):
                state = STATE_DONE
                break
        elif state == STATE_NORM:
            if "glNormal3" in line:
                append3ToData(line)
                state = STATE_VERT
        elif state == STATE_VERT:
            if "glVertex3" in line:
                append3ToData(line)
                state = STATE_TEX

if state != STATE_DONE:
    print("ERROR: state={}".format(state))

# output
print("{")
i = 0
while i < len(data):
    print("{},{},{},{},{},{},{},{},".format(data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6], data[i+7]))
    i += 8
print("}")
