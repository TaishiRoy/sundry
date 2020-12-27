#!/usr/bin/env python3
"""mapper.py"""
import gzip
import sys

record1 = []
record2 = []
record2count = []
finalRecord = []
indexPos = 0
fp=gzip.open("items.json.gz")
for line in fp:
	# review=eval(line)
	line=str(line,'utf-8')
	line = line.strip().strip('\n')
	ind = line.find("price': ")
	price = line[ind + 8 : ]
	justPrice = price[ : price.find(',')]
	try:
		justPrice = float(justPrice)
	except ValueError:
		continue
	if justPrice >= 3 :
		ind = line.find("asin': ")
		itemId = line[ind + 7 : ]
		justItem = itemId[ : itemId.find(',')].strip("'")
		print('(item:',justItem , ') 1')
	indexPos  += 1
	ind = line.find("also_viewed': [")
	alsoV = line[ind + 15 : ]
	if indexPos > 171000:
		break
	ind = alsoV.find("], ")
	allV = alsoV[ : ind + 3 ]
	listV = allV.split("'")
	res = list(filter(lambda x : x.find(" ") == -1, listV))
	res = list(filter(lambda x : x != "", res))
	res = list(filter(lambda x : x != ", ", res))
	res = list(filter(lambda x : x != ", ", res))
	res = list(filter(lambda x : x != "], ", res))
	res = list(filter(lambda x : len(x) <= 10, res))
	res = list(filter(lambda x : len(x) > 8, res))
	for item in res :
		print('(alsoViewed:',item, ') 1' )