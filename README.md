# Forensic tools

A project to contribute to the sector of ITEP-RN.

This repository contains programs to explore memory from a HDD with a specific HikVision FileSystem. Therefore, if you do not want apply to this model, it can support to understand a workflow.

It has some program that may be run in certain sequence or if you do not need to use in a sequence, you can skip some runs. Below it has a brief describe what each one does.

### Extract_first_frame

A script that will wander through a directory and extract the first frame of all video (with format .dd) that was inside its.

### Extract_address

This script will wander through a binary data, in specific a stream of video, that it is irregular with some pattern, searching a string passed by argument and copy that slice to new file.

### Separate_sign

With a slice that contains all the signatures (or strings), it will separate the content between them to do some analysis.

### Check_time

The first analysis is check some pattern of timestamps in phrases marked by a signature.

Look this is a sequence of steps.

In future, I will discuss the uses of each program in more detail, as some are designed to ensure some suspicious of what information is contained in each file. So, to guide the readers (and even me sometimes :D) I will review all codes and create a better flow. Any question, fell free to ask me (even you Julio).