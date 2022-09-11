#!/usr/bin/env python3

"""
- Remove includes
- Remove pragmas
- Trim lines and remove empty ones
"""

import sys

def usage(argv0):
    print(f"Usage: {argv0} <input_file_name.cpp>")
    sys.exit(1)

def parse_file(source_name):
    with open(source_name) as fin:
        lines = [x.rstrip() for x in fin.readlines()]

    # Remove all includes and pragmas, unless guarded by "// keep-line"
    out_lines = []
    keep = False
    for line in lines:
        # Allow for spaces
        if line.replace(' ','').startswith('//keep-line'):
            keep = True
        else:
            maybe_remove = False
            if line.replace(' ','').startswith('#include'):
                maybe_remove = True
            if line.replace(' ','').startswith('#pragma'):
                maybe_remove = True

            if keep or not maybe_remove:
                out_lines.append(line)
            keep = False

    lines = out_lines

    # Remove empty lines at start and end of file
    while len(lines) > 0 and len(lines[0].strip()) == 0:
        lines.pop(0)
    while len(lines) > 0 and len(lines[-1].strip()) == 0:
        lines.pop()

    return lines

def generate(source_name):
    lines = parse_file(source_name)

    print("\\begin{lstlisting}")
    for line in lines:
        print(line)
    print("\\end{lstlisting}")

if __name__ == '__main__':
    if len(sys.argv) < 2:
        usage()

    source_name = sys.argv[1]
    generate(source_name)

