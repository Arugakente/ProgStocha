# -*- coding: utf-8 -*-

import math

class Point(object):

	def __init__(self, id, x, y):
		self.id=int(id)
		self.x=float(x)
		self.y=float(y)

	def distance(self, point):
		return math.sqrt((point.x - self.x)**2 + (point.y - self.y)**2)
