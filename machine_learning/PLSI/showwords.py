#!/usr/bin/python

vocabulary = dict ()
toprint = 20
with open ('vocafile.txt') as vf:
    for line in vf:
        pair = line.split ()
        vocabulary[pair[1]] = pair[0]
with open ('w_z.txt') as wzf:
    topic = 0
    for line in wzf:
        weight = line.split ()
        ids = list (range (len(weight)))
        ids.sort (key = lambda i : weight[i], reverse = True)
        """print ids[:toprint]
        for i in ids[:toprint]:
            print weight[i],
        print
        """
        print "topic", topic, ":"
        for i in ids[:toprint]:
            print vocabulary[str(i)] + ":", weight[i]
        #representer = [vocabulary[str(i)] for i in ids[:toprint]]
        #print ' '.join (representer)
        topic += 1
	print
