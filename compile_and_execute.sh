#!/bin/bash
file='mnist_cnn'
# g++ ${file}.cpp -o ${file} -larmadillo -pg #  For profiling
g++ ${file}.cpp -o ${file}_shortDataset -larmadillo # For measuring memory usage
./${file}_shortDataset