#!/bin/bash

cd src

# Verificar se a pasta "build" existe
if [ -d "build" ]; then
    echo "dir 'build' exists."
    rm -rf .vscode
    rm -rf build
# else
#     echo "A pasta 'build' não existe."
fi

# compile

mkdir build
cd build
cmake ..
make

# # execute
./main

# back directory
cd ../../