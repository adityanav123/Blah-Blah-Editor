#!/bin/bash

# get file name from cli
filename=$1
filename_without_extensions="${filename%%.*}"

# echo "$filename_without_extensions"

compile_command="g++ $filename -o $filename_without_extensions"

execute_command="./$filename_without_extensions"

$compile_command

$execute_command

# clearing out the output file for non cluttering
rm -rf "$filename_without_extensions"
