#!/bin/bash
file='mnist_cnn'
g++ ${file}.cpp -o ${file} -larmadillo -pg
./${file}