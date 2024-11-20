naredbi_path=$(find /home -type f -name "naderbi.txt")
vlez_path=$(find /home -type f -name "vlez.txt")

if [ -n $naredbi_path ] && [ -n $vlez_path ];then
    cp $naredbi_path .
    cp $vlez_path .
else
    echo "sorry bro trazime sekade ne mozeme da najdeme fajl"

resultat=$(python3 zad2.py naredbi.txt vlez.txt)

for command in $resultat
do $command
done