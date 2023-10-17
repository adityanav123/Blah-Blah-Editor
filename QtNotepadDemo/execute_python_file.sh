#!/bin/bash

# get file name from cli
filename=$1

execute_command="python $filename"

$execute_command
