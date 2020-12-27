#!/usr/bin/env python3
import sys
from operator import itemgetter

current_word = None
current_count = 1
item = []
viewed = []
indexPos =0
countView = []
finalRecord = []
word = None
for line in sys.stdin :
	line = line.strip()
	word, count = line.split(') ', 1)
	thisType = word.split(': ')
	if thisType[0] == "(item" :
		if thisType[1] == current_word:
			continue
		else:
			if thisType[1] not in item :
				item.append(thisType[1])
				current_word = thisType[1]


	if thisType[0] == "(alsoViewed" :
		if thisType[1] == current_word:
			current_count += 1
			continue
		else:
			countView.append(current_count)
			current_count = 1
			viewed.append(current_word)
			current_word = thisType[1]


for el in countView:
	if el >=5 and viewed[countView.index(el)] in item :
		print(viewed[countView.index(el)])


'''if thisType[0] == "(item" :
	if thisType[1] not in item :
		item.append(thisType[1])

indexPos += 1
print(indexPos)
if indexPos > 17150:
	break
if thisType[0] == "(alsoViewed" :
	if thisType[1] not in viewed :
		viewed.append(thisType[1])
		countView.append(1)
	else :
		countView[viewed.index(thisType[1])] += 1

for el in range(0, len(countView)) :
	try :
		if countView[el] >= 5 :
			finalRecord.append(viewed[el])
	except IndexError:
		print("here")
		continue
resList = [value for value in finalRecord if value in item] 
print(resList)'''


