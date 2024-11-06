#!/usr/bin/env python
import sys

target = sys.argv[1]

STATE_INIT = 0
STATE_COLLECT = 1
STATE_DONE = 2
state = STATE_INIT
func_lines = []

with open("models.cpp", "r") as f:
    for line in f:
        if state == STATE_INIT:
            if "void {}(".format(target) in line:
                state = STATE_COLLECT
        elif state == STATE_COLLECT:
            if line.startswith("}"):
                state = STATE_DONE
                break
            else:
                func_lines.append(line)

if state != STATE_DONE:
    print("ERROR state={}".format(state))

modified_lines = []
for line in func_lines:
    if "glNormal" in line:
        modified_lines.append("  glTexCoord2f(0.2, 0.2);")
    modified_lines.append(line.rstrip())

for l in modified_lines:
    print(l)
