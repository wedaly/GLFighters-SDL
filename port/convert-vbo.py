#!/usr/bin/env python

import sys
import re
import struct

STATE_INIT = 0
STATE_COLLECT = 1
STATE_DONE = 2

target = sys.argv[1]
state = STATE_INIT
data = []

TWO_RE = re.compile(r"\(([0-9.-]+), ([0-9.-]+)\)")
THREE_RE = re.compile(r"\(([0-9.-]+), ([0-9.-]+), ([0-9.-]+)\)")

def appendToData(line):
    m = TWO_RE.search(line)
    if m is not None:
        data.extend(m.groups(1))
        return

    m = THREE_RE.search(line)
    if m is not None:
        data.extend(m.groups(1))

with open("models.cpp", "r") as f:
    for line in f:
        if state == STATE_INIT:
            if target in line:
                state = STATE_COLLECT
        elif state == STATE_COLLECT:
            if "glTexCoord2" in line or "glNormal3" in line or "glVertex3" in line:
                appendToData(line)
            elif line.startswith("}"):
                state = STATE_DONE
                break

if state != STATE_DONE:
    print("ERROR: state={}".format(state))
    sys.exit(1)

hastexture = len(data) % 8 == 0
floatspervertex = 8 if hastexture else 5

outpath = "data/models/" + target
print("Writing len(data)={}, with floatspervertex={}, values to {}".format(len(data), floatspervertex, outpath))
with open(outpath, "wb") as f:
    numVertices = len(data) // floatspervertex
    f.write(struct.pack(">I", numVertices)) # big endian unsigned int
    f.write(struct.pack(">I", floatspervertex))
    for v in data:
        f.write(struct.pack(">f", float(v))) # big endian IEEE floating point
