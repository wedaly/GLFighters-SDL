#!/usr/bin/env python

import sys
import re
import struct

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

outpath = "data/models/" + target
print("Writing len(data)={} values to {}".format(len(data), outpath))
with open(outpath, "wb") as f:
    numVertices = len(data) // 8
    f.write(struct.pack(">I", numVertices)) # big endian unsigned int
    for v in data:
        f.write(struct.pack(">f", float(v))) # big endian IEEE floating point
