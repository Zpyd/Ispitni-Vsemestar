import sys
import os

if len(sys.argv)<2:
    print("nema vneseno datoteka")
elif not os.path.isfile(sys.argv[1]):
    print("nepostoe taa datoteka")

with open(sys.argv[1],"r") as f:
    lines=f.readlines()
    for line in lines[1:]:
        words= line.split(" ")

        if words[-1][-2] == "c":
            print("gcc " + words[-1].strip() + " -o " + words[-1][:-3])
            print("./" + words[-1][:-3])

        elif ".sh" in words[-1]:
            print()
            if words[0][-1] == "x":
                print("./" + words[-1])
            else:
                print("chmod +x " + words[-1])