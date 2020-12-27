#!/usr/bin/env python3
"""reducer.py"""
import sys
from operator import itemgetter

current_word = None
current_count = 0
item = []
rated = []
countRating = []
finalRecord = []
word = None
for line in sys.stdin :	
	line = line.strip()
	word, count = line.split(' ) ', 1)

	thisType = word.split(': ')
	if thisType[0] == "(item" :
		if thisType[1] not in item :
			item.append(thisType[1])

	if thisType[0] == "(5star" :
		if thisType[1] not in rated :
			rated.append(thisType[1])
			countRating.append(1)
		else :
			countRating[rated.index(thisType[1])] += 1

for el in range(0, len(countRating)) :
	try :
		if countRating[el] >= 5 :
			finalRecord.append(rated[el])
	except IndexError:
		continue
resList = [value for value in finalRecord if value in item] 
print(resList)


