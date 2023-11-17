#!/bin/bash

sudo apt-get update

_libs_=(
    "g++" 
    "cmake"
)

for _lib_ in "${_libs_[@]}"; do
    sudo apt-get install -y "$_lib_"
done