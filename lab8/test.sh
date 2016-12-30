#!/bin/bash

if [ 1 -ne $# ]
then
    echo "Usage: ${0} <count>"
    exit
fi

if [ ! -f ./main ]
then
    echo "Trying to make project…"
    make clean
    make
    status=$?
    if [ $status -ne 0 ]
    then
        echo "Cannot build project!"
        exit $status
    fi
fi

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
    print "Total user time:", sum
    print "Average user time:", sum/n
}' ./time
rm time
