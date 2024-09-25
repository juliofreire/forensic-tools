#!/bin/bash

if [ $# != 2 ];
then
    echo "Usage" $0 ": pass 2 arguments <directory of inputs> <name of output>"
fi

if [ -d $1 ];
then
    echo "Wait for extract all dates."
else
    echo "The argument is not a directory to explore."
    exit 1;
fi

echo "Channel,Date,Timestamp" > "$2.csv"

find $1 -type f | while read -r arquivo;
do
    ./extract_date.o "$arquivo" "$2.csv"
done