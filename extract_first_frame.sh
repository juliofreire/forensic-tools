#!/bin/bash

#This code extracts the first frame of a collection of videos in a source directory and save all of them with a especific image format at destine directory.

#It's need 2 arguments:
#<argument 1>: the path of your series of videos
#<argument 2>: the path where you want to send the frames


if [ $# -ne 2 ]
then
	echo "Usage $0: <source> <destine>"
	exit 1
fi

# Setting some enviroments variables
source_dir=$1
destine_dir=$2
frames_dir=$destine_dir/frames

IFS="
"

# Creating a directory if there isn't

mkdir "$frames_dir"


for dd in $source_dir*.dd
do
	#echo "$dd"
	#taking the name of each dd file and replacing .dd to .jpg
	#remember %%.dd take all sufix
	filename=$(basename ${dd%.dd}.jpg)
	filename1=$(basename $dd | sed "s/dd$/jpg/")
	echo $filename
	ffmpeg -i $dd -vframes 1 -q:v 2 $frames_dir/$filename
done

