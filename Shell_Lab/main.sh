#!/usr/bin/env bash

mkdir $1
cd $1
for ((i = 1; i<=$2; i++))
do 
    touch "output"$i".out"
    echo $i > "output"$i".out"
done

cd ..
cat input/input1.txt | ./studentSub > output/output1.txt
diff output/output1.txt ref/ref1.txt
