vocabulary = dict ()
toprint = 100
with open ('vocfile') as vf:
    for line in vf:
        pair = line.split ()
        vocabulary[pair[1]] = pair[0]
with open ('w_z') as wzf:
    for line in wzf:
        weight = line.split ()
        ids = list (range (len(weight)))
        ids.sort (key = lambda i : weight[i], reverse = True)
        """print ids[:toprint]
        for i in ids[:toprint]:
            print weight[i],
        print
        """
        representer = [vocabulary[str(i)] for i in ids[:toprint]]
        print ' '.join (representer)

