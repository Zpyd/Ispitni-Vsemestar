import sys

if len(sys.argv)<4:
    print("brodie vnesi zbor flag filename glup")
    exit(1)

if sys.argv[2] not in ["w", "l", "f"]:
    print("imas samo w, l, f flag opcii sine")
    exit(1) 

with open(sys.argv[3]) as f:
    lines=f.readlines()
    for line in lines:
        line=line.strip()

word=sys.argv[1]
record={word:[]}
#l treba da se isprintat br na liniite kaj so e proonajden brojo
if sys.argv[2] == "l":
    i=0
    for line in lines:
        i+=1
        if word in line:
            record[word].append(i)


#w vraka kolku zbora bile pronajdeni pred zborot da se pronajde (pretpostavuvam prvata instanca)
if sys.argv[2] == "w":
    record.clear()
    occurance=1
    j=0
    for line in lines:
        # print(line)
        if word in line:
            words_line=line.split()
            # print(words_line)
            # print(len(words_line))
            for word_l in words_line:
                if word != word_l:
                    j+=1
                else:
                    key =f"occurance {occurance}"
                    record[key]=j
                    occurance+=1
       
#fnum of zbor 
if sys.argv[2]=="f":
    i=0
    for line in lines:
        if word in line:
            words_line=line.split()
            record[word].append(words_line.count(word))
 
print(record)
