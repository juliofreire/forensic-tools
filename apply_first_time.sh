#!/bin/bash


## TODO: DESCRIBE AND ADD DETAILS TO THIS SCRIPT
source_dir=$1

if [ $# -ne 1 ]
then
	echo "Usage: $0: <dir_souce>" 
	exit 1
fi

for seq in $source_dir*.dd
do
	
	echo $seq
	./first_time.o $seq .

done
