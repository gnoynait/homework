#!/bin/sh
echo preprocessing.
python preprocess.py dataset/hockey dataset/baseball stop_words.txt > data_set
echo compiling.
g++ perceptron.cc -o perc
echo training and evaluating.
cat data_set | ./perc > result
echo done.

