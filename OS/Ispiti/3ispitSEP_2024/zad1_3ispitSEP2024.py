import os
import sys

if(len(sys.argv)<2):
    print("bratce premalku arg od cmdl")
    exit(1)

meni={}
if os.path.exists(sys.argv[1]):
    with open(sys.argv[1], "r") as f1:
        if(sys.argv[2]):
            kategorija=sys.argv[2]
            while (jadenja:=f1.readline().strip().split(" ")):
                if(jadenja[2]==kategorija):
                    meni[f"{jadenja[0]}"] = {
                        "ime": f"{jadenja[2]}",  
                        "kat": f"{jadenja[3]}", 
                        "cena": f"{jadenja[4]}"
                    }
        else:
            for line in f1.readlines:
                jadenja= line.strip().split()
                meni[jadenja[0]] = {
                        "ime": f"{jadenja[2]}",  
                        "kat": f"{jadenja[3]}", 
                        "cena": f"{jadenja[4]}"
                    }        
    for key in meni.keys():
        print(f"ind: {key}", end=" ")
        print(f"ime: {meni[key]['ime']}:", end=" ")
        print(f"kategprija: {meni[key]['kat']}:", end=" ")
        print(f"cena: {meni[key]['cena']}:")
        print("------------------")

    num_jadenja= input("kolku jadenja ke zimas bak")
    print(f"vnesi {num_jadenja} ind na jadenjata")

    order=[]
    cena=0
    indeksi=meni.keys()
    for i in range(num_jadenja):
        order[i]= input("Vnesi ind na jadenje: ")
        if not order[i] in indeksi:
            print("nema go taj ind na jadenje baki")
            i-=1

    for i in range(num_jadenja):
        print(f"{meni[order[i]['ime']]}: {meni[order[i]]["cena"]}")
        cena+=meni[order[i]]["cena"]
    print("------------------")
    print(f"vkupno : {cena}")
else:
    print("ne postoe taa datoteka baki")