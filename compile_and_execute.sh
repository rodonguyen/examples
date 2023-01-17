#!/bin/bash
file='mnist_cnn'
output=${file}'_ds1000_e1_convo1'
# g++ ${file}.cpp -o ${file} -larmadillo -pg #  For profiling
g++ ${file}.cpp -o ${output} -larmadillo # For measuring memory usage

echo 'Run file with Valgrind...'
valgrind --tool=callgrind ./${output}


# PNG
# gprof2dot ./mnist_cnn/callgrind_ds1000_e1.out.73887 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o ./mnist_cnn/callgrind_ds1000_e1.png