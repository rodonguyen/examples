#!/bin/bash

# file01='mnist_cnn/mnist_cnn_1convo_1'
# file02='mnist_cnn/mnist_cnn_1convo_2'
# file03='mnist_cnn/mnist_cnn_1convo_3'
# file04='mnist_cnn/mnist_cnn_1convo_4'
# file05='mnist_cnn/mnist_cnn_1convo_5'
# file06='mnist_cnn/mnist_cnn_1convo_6'
file01='mnist_cnn_1convo_1'
file02='mnist_cnn_1convo_2'
file03='mnist_cnn_1convo_3'
file04='mnist_cnn_1convo_4'
file05='mnist_cnn_1convo_5'
file06='mnist_cnn_1convo_6'

# echo '1'
# g++ ${file01}.cpp -o ${file01} -larmadillo
# echo '2'
# g++ ${file02}.cpp -o ${file02} -larmadillo
# echo '3'
# g++ ${file03}.cpp -o ${file03} -larmadillo
# echo '4'
# g++ ${file04}.cpp -o ${file04} -larmadillo
# echo '5'
# g++ ${file05}.cpp -o ${file05} -larmadillo
# echo '6'
# g++ ${file06}.cpp -o ${file06} -larmadillo

# echo '1'
# valgrind --tool=callgrind ./${file01}
# echo '2'
# valgrind --tool=callgrind ./${file02}
# echo '3'
# valgrind --tool=callgrind ./${file03}
# echo '4'
# valgrind --tool=callgrind ./${file04}
# echo '5'
# valgrind --tool=callgrind ./${file05}
# echo '6'
# valgrind --tool=callgrind ./${file06}

echo '1'
./${file01}
echo '2'
./${file02}
echo '3'
./${file03}
echo '4'
./${file04}
echo '5'
./${file05}
echo '6'
./${file06}

# output=${file}'_ds500_01'
# g++ ${file}.cpp -o ${output} -larmadillo
# ./${output}


# echo 'Run file with Valgrind...'
# valgrind --tool=callgrind ./${output}


# g++ ${file}.cpp -o ${file} -larmadillo -pg #  For profiling