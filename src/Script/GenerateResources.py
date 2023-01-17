#!/usr/bin/python3

import sys
import os
from pathlib import Path

startMusicDirectly = 0.0
startMusicDelayed = 7.593
readLyrics = []
readCredits = []
symbolNames = [
    "ApertureLogo",
    "Radioactive",
    "Atom",
    "HeartBroken",
    "Fire",
    "Check",
    "Explosion",
    "BlackMesa",
    "Cake",
    "Turret"
]

def hexdumpSong(filepath: str, logPrefix: str = ""):
    size = os.path.getsize(filepath)

    print(f"{logPrefix} The song file \"{os.path.basename(filepath)}\" is {size} ({hex(size)}) bytes big")

    print(logPrefix, "Opening file Song.cpp")
    file = open("../Generated/Song.cpp", "w")
    read = open(filepath, 'rb')

    print(logPrefix, "Writing header")
    file.write("//This file was automatically generated by src/Script/GenerateResources.py\n\n")
    file.write("#include \"PortalCredits/Resources.hpp\"\n\n") #Include
    file.write(f"unsigned char data[{hex(size)}] = {{\n") #Array start

    # Begin hexdump
    print(logPrefix, "Writing contents")
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

    print(logPrefix, "Writing footer")

    file.write("};\n\n") #Array end

    file.write("namespace PortalCredits {\n\n") # Namespace start
    file.write(f"    const BinaryData Resources::stillAlive = {{data, {hex(size)}}};\n\n") #Data for Resource class
    file.write("}\n") #Namespace end

    file.close()

def writeCredits(fileOut):
    global readCredits
    fileOut.write("    const std::vector<std::string> Resources::credits = {\n")

    fileIn = open("../../res/Credits.txt", 'r')

    for line in fileIn:
        temp = str(line).replace("\n", "").replace("\\", "\\\\")
        readCredits.append(temp)
        fileOut.write(f"        \"{temp}\",\n")
    
    fileOut.write("    };\n\n")
    fileIn.close()

def writeLyrics(fileOut):
    global readLyrics
    fileOut.write("    const std::vector<std::vector<std::string>> Resources::lyrics = {\n")
    fileOut.write("        {\n")

    fileIn = open("../../res/Lyrics.txt", 'r')
    tempArray = []

    for line in fileIn:
        if line.startswith("#"):
            fileOut.write("        },\n\n")
            fileOut.write("        {\n")
            readLyrics.append(tempArray)
            tempArray = []
        else:
            temp = str(line).replace("\n", "").replace("\\", "\\\\")
            tempArray.append(temp)
            fileOut.write(f"            \"{temp}\",\n")
    
    readLyrics.append(tempArray)
    
    fileOut.write("        }\n")
    fileOut.write("    };\n\n")
    fileIn.close()

def generateLyricsHeader(logPrefix: str = ""):
    print(logPrefix, "Opening file Lyrics.cpp")

    file = open("../Generated/Lyrics.cpp", 'w')

    #Write comment
    print(logPrefix, "Writing header")
    file.write("//This file was automatically generated by src/Script/GenerateResources.py\n\n")

    #Write include
    file.write("#include \"PortalCredits/Resources.hpp\"\n\n")

    #Write namespace
    file.write("namespace PortalCredits {\n\n")

    print(logPrefix, "Writing contents")

    #Write Lyrics
    writeLyrics(file)

    #Write Credits
    writeCredits(file)

    #Namespace end
    print(logPrefix, "Writing footer")
    file.write("}\n")

    file.close()

def generateTimingFile(musicStart: float, logPrefix: str = ""):
    global readLyrics
    global readCredits
    global symbolNames

    print(logPrefix, "Opening file Timings.cpp")

    fileOut = open("../Generated/Timing.cpp", 'w')

    #Write comment
    print(logPrefix, "Writing header")
    fileOut.write("//This file was automatically generated by src/Script/GenerateResources.py\n\n")

    #Write include
    fileOut.write("#include \"PortalCredits/Resources.hpp\"\n\n")

    #Write namespace
    fileOut.write("namespace PortalCredits {\n\n")

    #Write music start
    fileOut.write(f"    const double Resources::audioStartTime = {musicStart};\n\n")

    #Write lyrics start
    fileOut.write("    const std::vector<TimeInfo> Resources::timingLyrics = {\n")

    #Write lyrics
    print(logPrefix, "Writing contents")
    fileIn = open("../../res/Timing.txt", 'r')
    readMode = 0 #Lyrics
    comps = []
    lineIndex = 0

    pageIndex = 0
    stringIndex = 0
    startPos = 0
    endPos = 0
    startTime = 0.0
    endTime = 0.0
    text = ""

    for line in fileIn:
        lineIndex += 1
        if len(line) < 2 or line.startswith("//"): #If line is empty or commented out
            continue

        if line.startswith("#Credits"): #Switch to Credits
            fileOut.write("    };\n\n")
            fileOut.write("    const std::vector<TimeInfo> Resources::timingCredits = {\n")
            readMode = 1 #Credits
            continue
        elif line.startswith("#Logos"): #Switch to Logos
            fileOut.write("    };\n\n")
            fileOut.write("    const std::vector<TimeInfo> Resources::timingLogos = {\n")
            readMode = 2 #Logos
            continue

        comps = line.split()
        if len(comps) < 6:
            print(logPrefix, f"The value in line {lineIndex} has less than 6 components: \"{line}\"", file=sys.stderr)
            continue

        pageIndex = int(comps[0])
        stringIndex = int(comps[1])
        startPos = int(comps[2])
        endPos = int(comps[3])
        startTime = float(comps[4])
        endTime = float(comps[5])

        #Determine text
        if readMode == 0:
            text = str(readLyrics[pageIndex][stringIndex])
        elif readMode == 1:
            text = str(readCredits[stringIndex])
        else:
            text = symbolNames[pageIndex]
        
        if endPos == -1:
            endPos = len(text) - 1
        
        if readMode != 2:
            text = text[startPos:endPos + 1:1]

        #Write entry
        fileOut.write(f"        {{{pageIndex}, {stringIndex}, {startPos}, {endPos}, {startTime}, {endTime}}}, //\"{text}\"\n")
    
    #Credits end
    print(logPrefix, "Writing footer")
    fileOut.write("    };\n")
    
    #Namespace end
    fileOut.write("}\n")

    fileIn.close()
    fileOut.close()


# Main code
if len(sys.argv) < 2:
    print("Not enough arguments", file=sys.stderr)
    print("Usage: GenerateResources.py <Song file.ogg> [-game]", file=sys.stderr)
    exit(1)

if len(sys.argv) == 2 and sys.argv[1] == "-game":
    print("No song file given", file=sys.stderr)
    print("Usage: GenerateResources.py <Song file.ogg> [-game]", file=sys.stderr)
    exit(1)

if len(sys.argv) > 2 and sys.argv[2] == "-game":
    start = startMusicDirectly
else:
    start = startMusicDelayed

dir = Path("../Generated")
if not dir.exists():
    print("Generating directory")
    dir.mkdir()

print("Generating Song")
hexdumpSong(sys.argv[1], "   ")

print()
print("Generating Lyrics")
generateLyricsHeader("   ")

print()
print("Generating Timings")
generateTimingFile(start, "   ")