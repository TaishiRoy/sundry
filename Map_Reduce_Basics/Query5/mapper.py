#!/usr/bin/env python3
"""mapper.py"""
import gzip
import sys

record1 = []
record2 = []
record2count = []
finalRecord = []
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
	if justPrice > 2 :
		ind = line.find("asin': ")
		itemId = line[ind + 7 : ]
		justItem = itemId[ : itemId.find(',')].strip("'")
		print('(item:',justItem , ') 1')

fp2=gzip.open("reviews.json.gz")
for line in fp2:
	line=str(line,'utf-8')
	line = line.strip().strip('\n')
	words = line.split('"')
	res = filter(lambda x : x != ': ', words)
	res = filter(lambda x : x != ', ', res)
	res = filter(lambda x : x != '{', res)
	res = list(res)
	for i in range(0, len(res)):
		if res[i] == "asin":
			reviewItem = res[i+1]

		if res[i] == "overall" :
			if int((res[i+1]).strip(': ').split('.',1)[0]) == 5 :
				print('(5star:', reviewItem, ') 1')
