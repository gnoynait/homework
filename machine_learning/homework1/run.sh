#!/bin/sh
echo preprocessing.
python preprocess.py dataset/hockey dataset/baseball stop_words.txt > data_set
echo compiling.
g++ perceptron.cc -o perc
g++ -o ann -O2 ann.cc
echo training and evaluating.
cat data_set | ./perc
cat data_set | ./ann 
echo everything is done.

