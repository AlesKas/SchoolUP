#!/bin/bash

number=$((1 + $RANDOM % 100))

while true 
do
    echo "Zadej cislo:"
    read input
    if [ $input -gt $number ]
    then 
        echo "Zadane cislo je vetsi"
    fi
    if [ $input -lt $number ]
    then
        echo "Zadane cislo je mensi"
    fi
    if [ $input -eq $number ]
    then
        echo "Uhadnuto"
        exit 0
    fi
    echo
done