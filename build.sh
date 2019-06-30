#!/bin/bash

usage() {
  echo "LinPwn build script"
  echo "--default   Compile with defaut options."
  echo "--dev       Compile with developer options enabled."
  echo "--debug     Compile with debug optionstons enabled."
} 


if [ $# -eq 0 ]; then
    echo "No arguments supplied"
    usage
    exit
fi

if [ $1 == "--default" ]; then
  g++ LinPwn.cc -o LinPwn;
  echo "Done."
elif [ $1 == "--dev" ]; then
  g++ -Wall -Wextra LinPwn.cc -o LinPwn;
  cpplint LinPwn.cc;
  echo "Done."
elif [ $1 == "--debug" ]; then
  g++ --no-pie -ggdb -static -fPIC LinPwn.cc -o LinPwn;
  echo "Done."
else
  usage;
fi
