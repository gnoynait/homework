from stemmer import PorterStemmer
import sys
stemmer = PorterStemmer ()
vocabulary = dict ()
doc = 0
def prosses_line (line):
    line = line.lower ()
    words = line.split ()
    data = []
    for w in words:
        w = stemmer.stem (w, 0, len(w) - 1)
        if w not in vocabulary:
            vocabulary[w] = len(vocabulary)
        data.append (str(vocabulary[w]) + ":1")
    return data

def preprosess (inputfile, datafile, vacfile):
    global doc
    for line in inputfile:
        data = prosses_line (line)
        print >>datafile, " ".join(data) 
        doc += 1
    for k, v in vocabulary.items():
        print >>vacfile, k, v

if __name__ == "__main__":
    datafile = open(sys.argv[1], "w")
    vocfile = open (sys.argv[2], "w")
    preprosess (sys.stdin, datafile, vocfile)
    print >>sys.stderr, len (vocabulary),  doc
