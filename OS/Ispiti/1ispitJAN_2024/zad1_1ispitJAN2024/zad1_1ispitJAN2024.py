#!/usr/bin/python3

import sys
import os

if(len(sys.argv)<3):
    print("bratce nemas dovolno argumenti")
    exit(1)

if not os.path.exists(sys.argv[2]) or not os.path.exists(sys.argv[3]):
    print("nema takov file kako od cmdl")
    exit(1)

with open(sys.argv[2],"r") as f1: 
    with open(sys.argv[3],"r") as f2:
        brlinija=0
        spoeno=[]
        kod=f1.readlines()
        kom=f2.readlines()

        for line in kod:
            flag=1
            for komentar in kom:
                if(int(komentar[0])==brlinija):
                    komentar[0],komentar[1]=""
                    spoeno.append(line+" " +komentar)
                    flag=0
                    brlinija+=1
            if flag:
                spoeno.append(line)
                brlinija+=1

with open(sys.argv[2],"w") as f1:
    for line in spoeno:
        f1.write(line)
        print(line)