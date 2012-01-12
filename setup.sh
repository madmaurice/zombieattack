#!/bin/bash

export SFML_DIR=$HOME/dev/lib/SFML-1.6
export SFML_LIB_DIR=$SFML_DIR/lib
export SFML_INC_DIR=$SFML_DIR/include

#For testing
export LD_LIBRARY_PATH=$SFML_LIB_DIR:$LD_LIBRARY_PATH
