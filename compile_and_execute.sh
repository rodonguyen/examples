#!/bin/bash


#####################################################

# echo 'Compile and run 1-load'

# g++ 'mnist_cnn_bbb_before.cpp' -o 'mnist_cnn_bbb_before' -larmadillo
# sleep 10s  # Pause to refresh memory, maybe
# ./mnist_cnn_bbb_before  # 1 load


# mylist=(2 4 8 16 32 64 96 128)
mylist=(128)

# # multi-load
# # Loop through the list
# for i in "${mylist[@]}"; do
#    file='mnist_cnn_bbb_after_'$i
#    echo 'Compiling' $file
#    g++ $file'.cpp' -o $file -larmadillo
#    echo 'Done'
# done

# sleep 6s  # Pause to refresh memory, maybe

for i in "${mylist[@]}"; do
   sleep 2s  # Pause to refresh memory, maybe
   file='mnist_cnn_bbb_after_'$i
   echo 'Running' $file
   ./$file
   echo 'Done' $i
done


#####################################################

# for (( i=96; i<=96; i+=2 )); do
#    file='mnist_cnn_bbb_after_'$i
#    echo 'Compiling' $file
#    g++ $file'.cpp' -o $file -larmadillo
#    echo 'Done'
# done


# sleep 10s  # Pause to refresh memory, maybe

# for (( i=96; i<=96; i+=2 )); do
#    file='mnist_cnn_bbb_after_'$i
#    echo 'Running' $file
#    ./$file
#    echo 'Done' $i
# done




#####################################################

# file01='mnist_cnn/mnist_cnn_1convo_1'
# file02='mnist_cnn/mnist_cnn_1convo_2'
# file03='mnist_cnn/mnist_cnn_1convo_3'
# file04='mnist_cnn/mnist_cnn_1convo_4'
# file05='mnist_cnn/mnist_cnn_1convo_5'
# file06='mnist_cnn/mnist_cnn_1convo_6'
# file01='mnist_cnn_1convo_1'
# file02='mnist_cnn_1convo_2'
# file03='mnist_cnn_1convo_3'
# file04='mnist_cnn_1convo_4'
# file05='mnist_cnn_1convo_5'
# file06='mnist_cnn_1convo_6'

# file='mnist_cnn_ds1000_1convo'
# output=${file}
# g++ ${file}.cpp -o ${output} -larmadillo
# ./${output}
# ./${output} > console_output.txt


# echo 'Run file with Valgrind...'
# valgrind --tool=callgrind ./${output}

# GENERATE CALL GRAPH
# gprof2dot ./callgrind.out.118168 -f callgrind -n 0.1 -e 0.02 -s | dot -Tpng -o ./mnist_cnn_train_only_02.png

# gprof2dot ./callgrind.out.118168 -f callgrind -n 0.1 -e 0.02 -s | dot -Tpng -o ./callgraph01.png
# htop --delay=1 --pid=
# g++ ${file}.cpp -o ${file} -larmadillo -pg #  For profiling

g++ 'mnist_cnn_bbb_after_8.cpp' -o 'mnist_cnn_bbb_after_8_q' -larmadillo