#!/bin/bash
#
## This program extract the offset address that contains the first line with a specific string passed by arguments
#
#
# Create variables to manipulate the data
#
directory=$1
string=$2
destine=$3/headers

# Create a directory to store the output
mkdir -p $destine

i=1
for block in $directory*.dd
do

	echo "Examinating block number $i"
	echo "Searching the $string in the data"
	address=$(strings -t d $block | grep "$string" | head -1 | cut -d " " -f 1)

	echo "$string was found in address: $address"
	skip_blocks=$(($address / 2048))
	echo "The dd comand must skip $skip_blocks blocks"
	dd if=$block of=$destine/"seq"$i.dd bs=2048 skip=$skip_blocks
	echo "Finish block number $i"
	i=$(($i+1))
done

echo "Finish all files"
