from stemmer import PorterStemmer
import sys
stemmer = PorterStemmer ()
vocabulary = dict ()
stopwords = set ()
doc = 0
def prosses_line (line):
    line = line.lower ()
    line = line.replace ('-', ' ')
    words = line.split ()
    data = []
    for w in words:
        if w in stopwords:
            continue
        if w.strip ('0123456789') == '':
            continue
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
    data = open ("data.txt")
    datafile = open("datafile.txt", "w")
    vocfile = open ("vocafile.txt", "w")
    stopwordsfile = open ("stopwords.txt")
    for w in stopwordsfile:
        stopwords.add (w.strip ())
    preprosess (data, datafile, vocfile)
    print >>sys.stderr, len (vocabulary),  doc
