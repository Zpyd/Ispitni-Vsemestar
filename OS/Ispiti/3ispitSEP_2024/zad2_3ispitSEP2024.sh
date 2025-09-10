#!/bin/bash

zbor=$1
#moze i pronajdeni= $(find . -type f -name "*.txt" -exec grep -l "$zbor" {} \;)
txt_files= $(find . -type f -name "*.txt")

if [ -z "$txt_files" ];then
    echo "nema teks files u tek dir i pod dir"
    exit 1

else
    pronajdeni=""
    for txt_file in $txt_files; do
        if grep -q "$zbor" "$txt_file"; then
            pronajdeni+="$txt_file "
        fi
    done
    for pronajden in pronajdeni; do
        echo "$(python3 prva.py3 "$zbor" "$pronajden")"
    done
    






