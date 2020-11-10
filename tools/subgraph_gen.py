# -*- coding: utf-8 -*-

import sys
import os
import numpy as np
from classes.point import Point

with_subtours = False

if len(sys.argv) < 2:
    print("Usage : " + str(sys.argv[0]) + " <input_filename> <with_subtours>")
    sys.exit(1)
elif len(sys.argv) == 3 and int(sys.argv[2]) == 1:
    with_subtours = True

ifile = open("../data/rawData/" + sys.argv[1] + ".tsp", "r")

dim = 0
points = []
labels = []
all_path = []
is_data_section = False

print("Parsing file...")
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

print("Generating distance matrix...")
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
print("nbVertex = " + str(dim) + ";", file=ofile, end=os.linesep)
print("c = [", file=ofile)

for i in range(dim):
	ofile.write("\t[")

	for j in range(dim):
		ofile.write(str(matrix[(i,j)]))

		if(j<dim-1):
			ofile.write(", ")

	if(i<dim-1):
		print("],", file=ofile)
	else:
		print("]", file=ofile)

print("];", file=ofile)
ofile.close()

if with_subtours:
    print("Generating subtours...")

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

print("Done")
