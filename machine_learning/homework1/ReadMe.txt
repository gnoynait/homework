                          PERCEPTRON AND ANN TEXT CLASSIFICATION
1. how to extract features
    Firstly split every doc into words and we get a word set for each doc. Then
    we count how many sets in which every words exists. We use the top 2000 words
    as our feature words. For a doc, if word i exists in its word set, then its
    feature i is 1, otherwise it's 0. We output the result with format:
     class_label feature_1 feature_2 ... feature_2000.
    Every line represents a doc.

2. commands
 1) preprocessing:
     $ python preprocess.py pos_dir neg_dir stop_words_file > data_set
    pos_dir is the directory for the postive docs and neg_dir for negative.
    stop_words_file is a file containning stop words, each line for a stop word.
    the data_set is the result file.
    trainning 
 2) compile programs:
    to compile perceptron program:
     $ g++ perceptron.cc -o perc
    to compile artificial neural networks program:
     $ g++ -O2 -o ann ann.cc
 3) training & testing & evaluate
    use perceptron:
     $ cat data_set | ./perc
    use ann:
     $ cat data_set | ./ann
    Both programs test internally for 5 times and output the statistics result (including 
    precision, recall and F1).
 4) to put it together, use the script run.sh to do all of the work above.
     $ ./run.sh

3. results
 1) perceptron test
   id	precision	recall  	f1
   1	0.950000	0.950000	0.950000
   2	0.974359	0.954774	0.964467
   3	0.956311	0.989950	0.972840
   4	0.979695	0.969849	0.974747
   5	0.938095	0.989950	0.963325
average	0.959692	0.970905	0.965076

 2) ann test
   id	precision	recall  	f1
   1	0.994709	0.940000	0.966581
   2	1.000000	0.934673	0.966234
   3	0.994764	0.954774	0.974359
   4	0.989691	0.964824	0.977099
   5	0.980000	0.984925	0.982456
average	0.991833	0.955839	0.973346
