#!/bin/bash

if [ -n "$1" ]; then
    dir="$1"
else
    dir="$PWD"

if [ ! -d "$dir" ];then
     echo "nema takov dir"
     exit 1
else
    ls -al "dir" > rez.txt
    naredbi=$(python3 zad1_ispit2025.py rez.txt)

    while read -r naredba; 
    do
        if [[ *"gcc"* == "$naredba" ]]; then 
            rez=$(naredba)
            if[ ! -z rez ];then
                echo "greska pri kompajliranje na $naredba"
                exit 1  #ili read -r _
                        #    continue ako treba da se skokne taa naredba
            fi
                
        fi
    done <<< "$naredbi"
