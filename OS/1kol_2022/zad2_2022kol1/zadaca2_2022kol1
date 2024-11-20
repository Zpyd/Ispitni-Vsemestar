#! /bin/bash

ime=$1

if[[ $ime == *.py]]
then
    pathway_to_file=$(find . -type f -name "$ime")
    if [ -n "pathway_to_file" ];then  
        result=$(python3 $pathway_to_file $2 ${@:2})
        echo "$result"
    else
        echo "file not found"
        exit 1
    fi

else
    $ime="prva.py"
     pathway_to_file=$(find . -type f -name "$ime")
    if [ -n "pathway_to_file" ];then  
        result=$(python3 $pathway_to_file $2 ${@:2})
        echo "$result"
    else
        echo "file not found"
        exit 1
    fi


fi

