#!/bin/sh

if [ -v $1 ];
then
    echo "Provide an '.profile' file as an argument..."
    elif [ -e $1 ];
    then
        grep -v "^-" $1 | awk '{sum += $2} END {print "Total time:", sum}'
    else
        echo "Requires an existing '.profile' file as an argument...";
fi
