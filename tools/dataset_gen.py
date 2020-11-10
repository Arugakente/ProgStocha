# -*- coding: utf-8 -*-

import sys
import os
import random as rd

min_pos = -100
max_pos = 100

if len(sys.argv) < 3:
    print("Usage : " + str(sys.argv[0]) + " <nb_points> <output_filename>")
    sys.exit(1)
    
rd.seed(os.urandom(4))
    
dim = int(sys.argv[1])
filename = str(sys.argv[2])

ofile = open("../data/rawData/" + filename, "w")

print("NAME : " + filename.split()[0], file=ofile)
print("DIMENSION : " + str(dim), file=ofile)
print("NODE_COORD_SECTION", file=ofile)

for i in range(dim):
    x = rd.uniform(min_pos, max_pos)
    y = rd.uniform(min_pos, max_pos)
    print(str(i+1) + " " + str(x) + " " + str(y), file=ofile)

print("EOF", file=ofile)

ofile.close()
