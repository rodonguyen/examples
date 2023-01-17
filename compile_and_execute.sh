#!/bin/bash
file='mnist_cnn'
# g++ ${file}.cpp -o ${file} -larmadillo -pg #  For profiling
g++ ${file}.cpp -o ${file}_ds500_e3 -larmadillo # For measuring memory usage
# ./${file}_shortDataset


# PNG
# gprof2dot ./mnist_cnn/callgrind_ds1000_e1.out.73887 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o ./mnist_cnn/callgrind_ds1000_e1.png