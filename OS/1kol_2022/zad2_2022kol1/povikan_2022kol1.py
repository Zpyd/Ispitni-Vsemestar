import os
import sys

# 1) so sys.argv[1] zboro pretrazi go u for sys.argv[2:] num datoteki

word=sys.argv[1].lower()

# 2) cuvaj counter za sekoja datoteka kolku pati ke se vrate
statistics={"Vkupno":0}

for file in sys.argv[2:]:
    
    if not os.path.isfile(file):
        continue
    
    else:
        statistics[file]=0
        with open(file, "r") as f:
            f_data=f.readlines()

        for f_line in f_data:
            f_words=f_line.split()
            for f_word in f_words:
                if word == f_word.lower():
                    statistics[file]+=1
                    statistics["Vkupno"]+=1
      
        else:
            continue

#shell gi zacuvuva kako return samo printovite
for file, count in statistics.items():
    print(f"{file}: {count}")

