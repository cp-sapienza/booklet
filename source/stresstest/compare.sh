#!/usr/bin/env bash

for ((testNum=0;testNum<$4;testNum++))
do
    ./$3 > input
    ./$2 < input > out2
    ./$1 < input > out1
    echo $testNum
    if !(cmp -s "out1" "out2")
    then
        echo "Error found!"
        echo "Input:"
        cat input
        echo $1 output:
        cat out1
        echo $2 output:
        cat out2
        rm input out1 out2
        exit
    fi
done
echo ""
echo Passed $4 tests
rm input out1 out2
