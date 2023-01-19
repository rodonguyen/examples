#!/bin/bash

file01='mnist_cnn_1convo_1'
file02='mnist_cnn_1convo_2'
file03='mnist_cnn_1convo_3'
file04='mnist_cnn_1convo_4'
file05='mnist_cnn_1convo_5'
file06='mnist_cnn_1convo_6'

# PNG
gprof2dot callgrind.out.172471 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o callgrind_${file01}.png
gprof2dot callgrind.out.172538 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o callgrind_${file02}.png
gprof2dot callgrind.out.172650 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o callgrind_${file03}.png
gprof2dot callgrind.out.172746 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o callgrind_${file04}.png
gprof2dot callgrind.out.172854 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o callgrind_${file05}.png
gprof2dot callgrind.out.172958 -f callgrind -n 0.1 -e 0.02 -s  | dot -Tpng -o callgrind_${file06}.png
