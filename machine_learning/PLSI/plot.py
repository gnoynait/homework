#!/usr/bin/python
from matplotlib.pyplot import *
import numpy as np
data = np.loadtxt (sys.argv[1])
plot (data)
show ()
