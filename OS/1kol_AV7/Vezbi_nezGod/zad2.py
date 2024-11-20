import sys
import os

if len(sys.argv)<3:
    print("sorry bro vnesi 2 iminja na datotoeki")
    sys.exit()

if not os.path.isfile(sys.argv[1]):
    print("ne e toa fajl jimmy")
else:
    with open(sys.argv[1], "r") as f1:
        comands=f1.read().splitlines()
        comands.strip()

if not os.path.isfile(sys.argv[2]):
    print("ne e toa fajl jimmy")
else:
     with open(sys.argv[2],'r') as f2:
         data=f2.read()
         data.strip()
         flag=False
         fullcommand=[]
         for word in data.split():
            if word in comands:
                 if flag:
                    print(" ".join(fullcommand))
                    fullcommand.clear
                    fullcommand.append(word)
                    
            else:
                fullcommand.append(word) 
                flag=1                  
                   

         print(" ".join(fullcommand))