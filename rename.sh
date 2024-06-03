#!/bin/bash

directory=$1
destine=$2

i=1861
echo $block
echo $i
for a in $(seq 1861 -1 1276); do
	mv $destine/"seq"$(printf %06d $a).dd $destine/"seq"$(printf %06d $(($a+1))).dd
done
