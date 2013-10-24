import os
import sys
import string
from collections import Counter

stop_words = set ()
word_list = []        #feature words

def load_stop_words (stopfile):
    if not stopfile:
        return
    with open (stopfile) as f:
        for w in f:
            stop_words.add (w.strip())

def extract_words (content):
    """extract words from content, return a set whitch contains
     words existing in content."""
    ls = content.lower ().split ()
    words = set ()
    for w in ls:
        w = w.strip (string.punctuation + string.digits)
        if w and w not in stop_words:
            words.add (w)
    return words 

def read_class (dir_name):
    """process documents which come from the same class and exist
    in the same dir. return a list of each doc's words set and 
    the number of doc in which each word exists for the class.""" 
    aticles = []
    class_counter = Counter ()
    for fname in os.listdir (dir_name):
        with open (os.path.join(dir_name, fname)) as f:
            words = extract_words(f.read ())
            aticles.append (words)
            for w in words:
                class_counter[w] += 1
    return aticles, class_counter

def output_class (class_set, class_number):
    """ output the preprocessing result. each doc a line. the first
    number is the class, the remaining is binary feature."""
    for aticle in class_set:
        print class_number,
        for w in word_list:
            if w in aticle:
                print 1,
            else:
                print 0,
        print

 
def preprocess (pos_dir_name, neg_dir_name):
    global word_list
    # preprocess each class
    positive, pos_counter = read_class (pos_dir_name)
    negative, neg_counter = read_class (neg_dir_name)

    # use the top 2000 words as features.
    most_common = (pos_counter + neg_counter).most_common (2000)
    word_list = [w for w, c in most_common]

    output_class (positive, 1)
    output_class (negative, -1)

def main ():
    pos_dir_name = sys.argv[1]   # positive class dir
    neg_dir_name = sys.argv[2]   # negative class dir
    stop_word_name = sys.argv[3] # stop words file

    load_stop_words (stop_word_name)
    preprocess (pos_dir_name, neg_dir_name)

if __name__ == '__main__':
    main ()
