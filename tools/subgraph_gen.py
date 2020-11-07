# -*- coding: utf-8 -*-

import sys
import os
import numpy as np
from classes.point import Point

ifile = open("../data/rawData/" + sys.argv[1] + ".tsp", "r")

dim = 0
points = []
labels = []
all_path = []
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
	labels.append(points[i].id)

	for j in range(i,dim):
		if(i == j):
			matrix[(i,i)] = 0
		else:
			distance = points[i].distance(points[j])
			matrix[(i,j)] = distance
			matrix[(j,i)] = distance

ofile = open("../data/" + sys.argv[1] + ".dat", "w")
ofile2 = open("../data/" + sys.argv[1] + "_covMatrix.dat", "w")
print("nbVertex = " + str(dim) + ";", file=ofile, end=os.linesep)
print("c = [", file=ofile)
print("V = [", file=ofile2)

for i in range(dim):
	ofile.write("\t[")
	ofile2.write("\t[")

	for j in range(dim):
		ofile.write(str(matrix[(i,j)]))
		ofile2.write(str((matrix[(i,j)]*0.1)*(matrix[(i,j)]*0.1)))

		if(j<dim-1):
			ofile.write(", ")
			ofile2.write(", ")

	if(i<dim-1):
		print("],", file=ofile)
		print("],", file=ofile2)
	else:
		print("]", file=ofile)
		print("]", file=ofile2)

print("];", file=ofile)
print("];", file=ofile2)
ofile.close()
ofile2.close()

for i in range(1 << dim):
	all_path.append([labels[j] for j in range(dim) if (i & (1 << j))])

ofile = open("../data/" + sys.argv[1] + "_subtours.dat", "w")
print("Subtours = {", file=ofile)

for i in range(1,len(all_path)-1):
	ls = ""

	for pt in all_path[i]:
		ls += " " + str(pt)

	print("  <  " + str(len(all_path[i])) + "   {" + ls + "} >", file=ofile)

print("};", file=ofile)
ofile.close()
