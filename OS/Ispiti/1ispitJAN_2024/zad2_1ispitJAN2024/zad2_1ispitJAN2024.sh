results=$(find . -type f -name "*.py3")

for filepath in $results;do
    filename=$(basename "$filepath")
    fnco=$(find . -type f -name "${filename%.py3}.co")
    if [ -n fnco ];then
        fnco=$(basename "$fnco")
        python3 prva.py3 $filename $fnco
    done