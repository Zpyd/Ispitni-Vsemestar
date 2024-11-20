#! /bin/bash


listaFiles= $(find /home/x/Desktop/V_semestar/Github/Ispitni-Vsemestar/ -type f -name "*.java")
for file in $listFiles; do
    IPadresi = $(python3 $file)
    for IP in $adresi;do
        if ping -c 1 $IP > /dev/null 2>$1;
            access="accesable"
        else 
            access="unaccesable"
        fi
        echo "$IP e $access"
    done
done

