#!/bin/bash

echo "" > time

for i in `seq $1`
do
    bash -c 'time -p ./main' 2>> time
done
awk '
BEGIN {
    sum=0
    n=0
}
/user/ {
    sum += $2
    n++
} 
END {
    print "Tests count:", n
    print "Average user time:", sum/n
}' ./time
rm time
