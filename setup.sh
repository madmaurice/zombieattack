#!/bin/bash

export PROJECT_ROOT=$PWD
export SFML_DIR=$PWD/sfml
export SFML_LIB_DIR=$SFML_DIR/lib
export SFML_INC_DIR=$SFML_DIR/include

#For testing
export LD_LIBRARY_PATH=$SFML_LIB_DIR:$LD_LIBRARY_PATH
