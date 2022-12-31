#!/usr/bin/python3

import sys
import os

print("Hello World")

if len(sys.argv) < 2:
    print("Not enough arguments", file=sys.stderr)
    print("Usage: GenerateSong.py <Song file.ogg>", file=sys.stderr)
    exit(1)

name = sys.argv[1]
size = os.path.getsize(name)

print(f"The song file \"{name}\" is {size} ({hex(size)}) bytes big")

print("Opening file Song.hpp")
file = open("Song.hpp", "w")
read = open(name, 'rb')

print("Writing header")
file.write("#ifndef PC_SONG_HPP\n#define PC_SONG_HPP\n\n") #Header guard
file.write("#include <array>\n\n") #Include
file.write("namespace PortalCredits {\n\n") # Namespace start
file.write(f"    static const std::array<unsigned char, {hex(size)}> stillAlive = ")
file.write("{\n") #Array start

# Begin hexdump
print("Writing contents")
toCopy = 16
rest = size
index = 0
b = 0
while toCopy > 0:
    file.write("        ")
    for i in range(toCopy):
        file.write(f"0x{read.read(1).hex()}, ")
    file.write("\n")
    index += toCopy
    rest -= toCopy
    if rest >= 16:
        toCopy = 16
    else:
        toCopy = rest

read.close()

print("Writing footer")
file.write("    };\n") #Array end
file.write("}\n") #Namespace end
file.write("#endif //PC_SONG_HPP") # Header guard end

file.close()