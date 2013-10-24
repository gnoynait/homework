1. how to extract features
  Firstly split every doc into words and we get a word set for each doc. Then
  we count how many sets in which every words exists. We use the top 2000 words
  as our feature words. For a doc, if word i exists in its word set, then its
  feature i is 1, otherwise it's 0. We output the result with format:
  class_number feature_1 feature_2 ... feature_2000.
  Every line represents a doc.

2. commands
  1) preprocessing:
  $ python preprocess.py pos_dir neg_dir stop_words_file > data_set
  pos_dir is the directory for the postive docs and neg_dir for negative.
  stop_words_file is a file containning stop words, each line for a stop word.
  the data_set is the result file.
  trainning 
  2) compile perceptron program:
  $ g++ perceptron.cc -o perc
  3) training & testing & evaluate
  $ cat data_set | ./perc > result
  The perc program tests 5 times internally so don't output the test results.
  result is output file containing the evaluate result (precision, recall, F1).
  4) to put it together, use the script run.sh to do all of work above.
  $ ./run.sh

3. evaluation result
  test	precision	recall  	f1
  1	0.950000	0.950000	0.950000
  2	1.000000	0.994975	0.997481
  3	0.995000	1.000000	0.997494
  4	1.000000	1.000000	1.000000
  5	1.000000	1.000000	1.000000
  ave   0.989           0.989           0.989  
