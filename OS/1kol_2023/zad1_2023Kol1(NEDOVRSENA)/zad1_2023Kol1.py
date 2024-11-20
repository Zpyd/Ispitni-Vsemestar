import sys

if len(sys.argv)>2:
    with open(sys.argv[1], "r") as f:
        lines=f.readlines()
        lines.strip

    for line in lines:
        words=line.split
        for word in words:
            if len(word.split("."))==4:
                adress=word.split(".")
                print(f"{adress}")
            if  len(word.split(":"))==4:
                maska=word.split("")

                for i in range(4):
                    if adress[i]==maska[i]:
                        continue
                    else:
                        
                
                    
                