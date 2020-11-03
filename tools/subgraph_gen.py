# -*- coding: utf-8 -*-

import sys
import os
import numpy as np
from classes.point import Point

ifile = open("../data/rawData/d493.tsp", "r")

dim = 0
points = []
is_data_section = False

for line in ifile:
	if 'NODE_COORD_SECTION' in line:
		is_data_section = True
		continue
	elif 'DIMENSION' in line:
                dim = int(line.split()[-1])
                continue
	elif 'EOF' in line:
		is_data_section = False
		break

	if is_data_section:
		d = line.split()
		points.append(Point(d[0], d[1], d[2]))

ifile.close()

matrix = np.empty([dim,dim])

for i in range(dim):
	for j in range(i,dim):
		if(i == j):
			matrix[(i,i)] = 0
		else:
			distance = points[i].distance(points[j])
			matrix[(i,j)] = distance
			matrix[(j,i)] = distance

ofile = open("../data/export.dat", "w")
print("nbVertex = " + str(dim) + ";", file=ofile, end=os.linesep)
print("c = [", file=ofile, end=os.linesep)

for i in range(dim):
        ofile.write("\t[")

        for j in range(dim):
                ofile.write(str(matrix[(i,j)]))

                if(j<dim-1):
                        ofile.write(", ")

        if(i<dim-1):
                print("],", file=ofile, end=os.linesep)
        else:
                print("]", file=ofile, end=os.linesep)

print("];", file=ofile, end=os.linesep)
ofile.close()
